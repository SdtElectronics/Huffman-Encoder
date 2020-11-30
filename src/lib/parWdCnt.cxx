/* 
  Copyright (C) 2020 SdtElectronics <null@std.uestc.edu.cn>
  All Rights Reserved.
  Unauthorized copying of this file, via any medium is strictly prohibited.
*/

#include "parWdCnt.h"
#include "omp.h"

parWdCounter::parWdCounter(const std::string& input):
	//slots(input.size(), std::array<char, 127>{}),
	in(input){};

std::array<size_t, 127> parWdCounter::wdCnt(const std::string &input) const{
    std::array<size_t, 127> cnt{};
	for(char wd: input){	
		cnt[static_cast<size_t>(wd)]++;
	}
	return cnt;
}

std::array<size_t, 127> parWdCounter::operator () (){	
	//omp_set_num_threads(nThreads);
	std::array<size_t, 127> ret{};
	
	//#pragma omp parallel for
	for (size_t ind = 0; ind < in.length(); ++ind){
        ret[static_cast<size_t>(in[ind])]++;
    }
	return ret;
}
