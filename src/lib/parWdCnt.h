#include <vector>
#include <array>
#include <string>

class parWdCounter{	
	public:
		parWdCounter(std::string&& input);
		
		std::array<size_t, 256> operator () (size_t nThreads);
	private:
		std::string in;
		//std::vector<std::array<size_t, 256>> slots;
		std::array<size_t, 256> wdCnt(std::string input);

};
