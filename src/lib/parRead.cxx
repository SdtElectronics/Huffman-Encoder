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

std::string parReader::stRead(){	
	size_t fSize = std::filesystem::file_size(std::filesystem::path(file_path));
	std::string ret(fSize + 1, '\0');
	offsetRd(0, fSize, &ret[0]);
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
