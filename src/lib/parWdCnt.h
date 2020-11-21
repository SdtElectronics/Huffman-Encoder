/* 
  Copyright (C) 2020 SdtElectronics <null@std.uestc.edu.cn>
  All Rights Reserved.
  Unauthorized copying of this file, via any medium is strictly prohibited.
*/

#include <vector>
#include <array>
#include <string>

class parWdCounter{	
	public:
		parWdCounter(const std::string& input);
		
		std::array<size_t, 256> operator () (size_t nThreads);
	private:
		const std::string& in;
		//std::vector<std::array<size_t, 256>> slots;
		std::array<size_t, 256> wdCnt(const std::string& input) const;

};
