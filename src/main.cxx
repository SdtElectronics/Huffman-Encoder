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
#include "cmdline/cmdline.h"
#include "parRead.h"
#include "parWdCnt.h"
#include "HTF.h"
#include "codeFactory.h"
#include "llogger.h"
#include "utils.h"
#include "version.h"

template class codeFactory<HFEnc>;
template codeFactory<HFEnc>::codeFactory<std::array<double, 256>>(const std::array<double, 256> &probs);
template codeFactory<HFEnc>::codeFactory<std::array<double, 256>>(const std::array<double, 256> &probs,
                                                                  std::vector<std::array<char, 2>> filter);
template std::vector<std::string> codeFactory<HFEnc>::codeGen();
template std::vector<char> codeFactory<HFEnc>::alphabetGen();
template std::vector<char> codeFactory<HFEnc>::buildAlphabet(char beg, char end);

cmdline::parser cmd;

int main(int argc, char* argv[]){
    // add specified type of variable.
    // 1st argument is long name
    // 2nd argument is short name (no short name if '\0' specified)
    // 3rd argument is description
    // 4th argument is mandatory (optional. default is false)
    // 5th argument is default value  (optional. it used when mandatory is false)
    cmd.add<std::string>("input", 'I', "input file", true);
    cmd.add<int>("verbose", 'v', "log level", false, 3, cmdline::range(0, 4));
    //cmd.add<std::string>("filter", 'f', "character filter", false, "\0,\177");
    cmd.add<std::string>("filter", 'f', "character filter", false, "a,z; , ;A,Z");

    parReader rd(cmd.get<std::string>("input"));
    llogger logger(std::cout, static_cast<llogger::level>(cmd.get<int>("verbose")));

    std::vector<std::string> filters = split(cmd.get<std::string>("filter"), ";");
    std::vector<std::array<char, 2> > cfFilt;
    cfFilt.reserve(filters.size());
    for(std::string filter: filters){
        cfFilt.push_back(std::array<char, 2>{filter[0], filter[2]});
    }
    
    const std::string& ve = rd.stRead();
	/*
	for(auto str:ve){	
		std::cout<<str<<std::endl;
	}
	*/
	std::array<size_t, 256>&& cCnt = parWdCounter(ve)();

	for(size_t j = 96; j != 122; ++j){	
	//	std::cout<<static_cast<char>(j)<<':'<<ret[j]<<std::endl;
	}

    codeFactory<HFEnc> cf(cCnt, cfFilt);

    class std::vector<std::string> codes = cf.codeGen();
    class std::vector<char> alphabet = cf.alphabetGen();
    for (size_t j = 96; j != 122; ++j){
        std::cout << static_cast<char>(j) << ':' << codes[j] << std::endl;
    }
}
