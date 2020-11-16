#include <string>
#include <vector>


class parReader{	
	public:
		parReader(const std::string &&path);
		std::string read(const size_t nThreads);
		std::string  stRead();

		const std::string file_path;
	private:
		void offsetRd(size_t offset, size_t len, char* dst);
};
