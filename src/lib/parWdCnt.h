/* 
  Copyright (C) 2020 SdtElectronics <null@std.uestc.edu.cn>
  All Rights Reserved.
  Unauthorized copying of this file, via any medium is strictly prohibited.
*/
#pragma once
#include <vector>
#include <array>
#include <string>

class parWdCounter{	
	public:
		parWdCounter(const std::string& input);
		
		std::array<size_t, 127> operator () ();
	private:
		const std::string& in;
		//std::vector<std::array<size_t, 127>> slots;
		std::array<size_t, 127> wdCnt(const std::string& input) const;

};
