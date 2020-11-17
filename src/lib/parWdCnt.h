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
