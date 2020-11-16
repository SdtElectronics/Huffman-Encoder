#include <utility>

std::pair<size_t, size_t> taskDiv(size_t nThreads, size_t taskSize){	
	size_t lastChunkSize = taskSize%nThreads;
	size_t chunkSize = (taskSize - lastChunkSize)/nThreads;
	return std::pair<size_t, size_t>(chunkSize, lastChunkSize + chunkSize);
}
