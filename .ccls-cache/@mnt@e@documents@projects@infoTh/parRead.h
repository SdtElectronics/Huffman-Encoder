#include <string>
#include <vector>


class parReader{	
	public:
		parReader(const std::string &&path);
		std::vector<std::string> read(const int nThreads);

	private:
		const std::string file_path;
};
