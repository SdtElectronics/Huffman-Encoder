/*
  Copyright (C) 2020 SdtElectronics <null@std.uestc.edu.cn>
  All rights reserved.
  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:
  * Redistributions of source code must retain the above copyright
  notice, this list of conditions and the following disclaimer.
  * Redistributions in binary form must reproduce the above copyright
  notice, this list of conditions and the following disclaimer in the
  documentation and/or other materials provided with the distribution.
  * Neither the name of the copyright holder nor the
  names of its contributors may be used to endorse or promote products
  derived from this software without specific prior written permission.
  THIS SOFTWARE IS PROVIDED BY  COPYRIGHT HOLDERS AND CONTRIBUTORS ''AS IS'' 
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
  ARE DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE 
  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL 
  DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, 
  OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <array>
#include <thread>
#include <iostream>
#include <fstream>
#include <sstream>
#include "cmdline/cmdline.h"
#include "parRead.h"
#include "parWdCnt.h"
#include "HTF.h"
#include "codeFactory.h"
#include "llogger.h"
#include "utils.h"
#include "version.h"
#include "CODEC.h"

cmdline::parser cmd;

int main(int argc, char* argv[]){
    // add specified type of variable.
    // 1st argument is long name
    // 2nd argument is short name (no short name if '\0' specified)
    // 3rd argument is description
    // 4th argument is mandatory (optional. default is false)
    // 5th argument is default value  (optional. it used when mandatory is false)
    cmd.add<std::string>("input", 'i', "input file", false, "");
    cmd.add<std::string>("output", 'o', "out compressed file", false, "");
    cmd.add<std::string>("dict", 'd', "dictionary file", false, "");
    
    cmd.add<int>("verbose", 'v', "log level", false, 3, cmdline::range(0, 5));
    cmd.add<std::string>("filter", 'f', "character filter", false, "\1,\176");
    cmd.add("version", 'V', "show version information");
    //cmd.add<std::string>("filter", 'f', "character filter", false, "a,z; , ;A,Z");

	cmd.parse_check(argc, argv);

	llogger logger(std::cout, static_cast<llogger::level>(cmd.get<int>("verbose")));

    if (cmd.exist("version")){
		std::cout<<info.c_str();

        return 0;
    }

	std::string inP = cmd.get<std::string>("input");
	if (inP.length() == 0) {
		logger<<llogger::level::error<<"No input file specified";
		return 1;
	}
    parReader rd(inP);
    

    std::vector<std::string> filters = split(cmd.get<std::string>("filter"), ";");
    std::vector<std::array<char, 2> > cfFilt;
    cfFilt.reserve(filters.size());
    for(std::string filter: filters){
        cfFilt.push_back(std::array<char, 2>{filter[0], filter[2]});
    }
    
    const std::string& fileStr = rd.stRead();
	/*
	for(auto str:fileStr){	
		std::cout<<str;
	}
	std::cout << std::endl;
	*/
	const std::array<size_t, 127>& cCnt = parWdCounter(fileStr)();
	/*
	for(size_t j = 96; j != 122; ++j){	
		std::cout<<static_cast<char>(j)<<':'<< cCnt[j]<<std::endl;
	}
	*/
    codeFactory cf(cCnt, cfFilt);

    logger<<llogger::level::verbose<<[&cf](){
        std::vector<char> alphabet = cf.alphabetGen();
        std::vector<double> probs = cf.getProbs();
        std::stringstream logs;
        logs<<"========Character count========\n";
        size_t ind = 0;
        for(char sym: alphabet){
            logs<<sym<<' '<<probs[ind++]<<'\n';
        }
		logs<<'\n';
        return logs.str();
    };

    std::vector<std::vector<bool> > codes = cf.codeGen<HFEnc>();

    logger<<llogger::level::info<<[&cf, codes](){
        std::vector<char> alphabet = cf.alphabetGen();
        std::stringstream logs;
        logs<<"========Character encoding========\n";
        size_t ind = 0;
        for(char sym: alphabet){
            logs<<sym<<' '<<codeFactory::printCode(codes[ind++])<<'\n';
        }
		logs << '\n';
        return logs.str();
    };

    std::string ofp = cmd.get<std::string>("output");
    if(ofp.size() > 0){
        std::ofstream outCompressed(ofp, std::ios_base::out);
        encoder fenc(codeFactory::buildAlphabet(0, 127), std::vector<double>(cCnt.begin(), cCnt.end()));
        fenc.writeCompressed(outCompressed, fileStr);
		outCompressed.close();
		std::string ofd = cmd.get<std::string>("dict"); 
		if (ofd.size() > 0) {
			std::ofstream outDict(ofd, std::ios_base::out);
			fenc.writeDict(outDict);
		}else{
			logger<<llogger::level::warning<<"No dictionary output path specified.\n";
		}

    }
        
}
