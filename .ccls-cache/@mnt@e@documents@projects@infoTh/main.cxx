#include <thread>

int main(int argc, char* argv[]){	
	
	int nThreads = std::thread::hardware_concurrency();
}
