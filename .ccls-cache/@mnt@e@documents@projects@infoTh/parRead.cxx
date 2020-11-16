#include <omp.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <parRead.h>

parReader::parReader(const std::string &&path): parReader::file_path(path){};
std::vector<std::string> parReader::read(const int nThreads){	
	
}
