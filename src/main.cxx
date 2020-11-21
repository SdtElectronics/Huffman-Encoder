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

#include <thread>
#include <iostream>
#include "cmdline/cmdline.h"
#include "parRead.h"
#include "parWdCnt.h"
#include "HTF.h"
#include "llogger.h"
#include "version.h"

parReader rd("./sc.fex");

int main(int argc, char* argv[]){	
	int nThreads = std::thread::hardware_concurrency();
	const std::string& ve = rd.stRead();
	/*
	for(auto str:ve){	
		std::cout<<str<<std::endl;
	}
	*/
	std::array<size_t, 256>&& ret = parWdCounter(std::move(ve))(nThreads);
	for(size_t j = 96; j != 122; ++j){	
	//	std::cout<<static_cast<char>(j)<<':'<<ret[j]<<std::endl;
	}

    HFEnc enc(ret);
    auto codes = enc();
    for (size_t j = 96; j != 122; ++j){
        std::cout << static_cast<char>(j) << ':' << codes[j] << std::endl;
    }
}
