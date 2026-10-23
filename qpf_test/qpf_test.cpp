#include <Windows.h>
#include <iostream>
#include <cstdint>

int main()
{
	LARGE_INTEGER frequency;
	LARGE_INTEGER t1, t2;
	double elapsedTime;
	// Get the frequency of the high-resolution performance counter
	QueryPerformanceFrequency(&frequency);
	
	
	std::int64_t ns_pt = frequency.QuadPart / 1000000000.0;
	std::cout << "Elapsed time: " << frequency.QuadPart << " nanoseconds" << std::endl;
	return 0;
}
