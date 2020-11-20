#include <thread>
#include <iostream>
#include "parRead.h"
#include "parWdCnt.h"
#include "HTF.h"
#include "llogger.h"

parReader rd("./sc.fex");

int main(int argc, char* argv[]){	
	int nThreads = std::thread::hardware_concurrency();
	const std::string& ve = rd.read(nThreads);
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
