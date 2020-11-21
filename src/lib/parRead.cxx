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

#include <omp.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <filesystem>
#include "parRead.h"
#include "utils.h"

parReader::parReader(const std::string& path): file_path(path){};

std::string parReader::read(const size_t nThreads){	
	size_t fSize = std::filesystem::file_size(std::filesystem::path(file_path));
	auto rr = taskDiv(nThreads, fSize);
	auto chunkSize = rr.first;
	auto lastChunkSize = rr.second;
	
	std::string par(fSize+1, '\0');
	omp_set_num_threads(nThreads);
	#pragma omp parallel 
	{	
		size_t tid = omp_get_thread_num();	
		int pos = chunkSize*tid;
		size_t &readLen = (tid == nThreads - 1)?lastChunkSize:chunkSize;
		offsetRd(pos, readLen, &par[0] + tid*chunkSize);
	}
	return par;	
}

std::string parReader::stRead(std::optional<size_t> len, size_t offset){
    size_t fSize = len.has_value() ? 
                    len.value()    :
                    std::filesystem::file_size(std::filesystem::path(file_path));
    std::string ret(fSize + 1, '\0');
    offsetRd(offset, fSize, &ret[0]);
    return ret;
}

void parReader::offsetRd(size_t offset, size_t len, char* dst){	
	std::ifstream file(file_path.c_str(), std::ios::in);
	if (!file.good()) {	
	//TODO::raise an exception
	}

	file.seekg(offset, std::ios::beg);
	file.read(dst, len);
	file.close();		
}
