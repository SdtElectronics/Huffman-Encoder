#include <omp.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <filesystem>
#include "parRead.h"
#include "utils.h"
parReader::parReader(const std::string &&path): file_path(path){};

std::vector<std::string> parReader::read(const size_t nThreads){	
	size_t fSize = std::filesystem::file_size(std::filesystem::path(file_path));
	auto rr = taskDiv(nThreads, fSize);
	auto chunkSize = rr.first;
	auto lastChunkSize = rr.second;
	
	std::vector<std::string*> par(nThreads);
	omp_set_num_threads(nThreads);
	#pragma omp parallel 
	{	
		std::ifstream file(file_path.c_str(), std::ios::in);
		if (!file.good()) {	
			//TODO::raise an exception
		}
		size_t tid = omp_get_thread_num();	
		int pos = chunkSize*tid;
		file.seekg(pos, std::ios::beg);
		
		size_t &readLen = (tid == nThreads - 1)?lastChunkSize:chunkSize;
		std::string buf(readLen + 1, '\0');
		file.read(&buf[0], readLen);
		par[tid] = &buf;
		file.close();
	}
	std::vector<std::string> ret;
	for(auto sig: par){	
		ret.emplace_back(std::move(*sig));
	}
	return ret;
}
