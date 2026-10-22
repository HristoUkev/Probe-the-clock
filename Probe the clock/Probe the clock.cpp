// Probe the clock.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <cstdint>
#include <chrono>


//smallest gap would be 100ns

//in release the average gap is gonna be higher but the total lower (so the total was lower but the average was lower as well unlike what I predicted)
int main()
{
	std::chrono::steady_clock::time_point t0 = std::chrono::steady_clock::now();
	std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();
	std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();

	std::chrono::duration<std::int64_t, std::nano> d_ns = t2 - t1;
	std::chrono::duration<std::int64_t, std::nano> min_ns = std::chrono::duration<std::int64_t, std::nano>::max();
	std::chrono::duration<std::int64_t, std::nano> max_ns = std::chrono::duration<std::int64_t, std::nano>::min();
	std::chrono::duration<std::int64_t, std::nano> avg_ns = std::chrono::duration<std::int64_t, std::nano>(0);

	for (std::int64_t i = 0; i < 1000000; i++)
	{
		t1 = std::chrono::steady_clock::now();
		t2 = std::chrono::steady_clock::now();
		
		d_ns = t2 - t1;

		avg_ns = (avg_ns + d_ns);
		//if the current gap is smaller than the previous smallest gap and not a zero, update the smallest gap 
		if (((d_ns < min_ns)  != 0) && d_ns != std::chrono::duration<std::int64_t, std::nano>(0))
		{
		
						min_ns = d_ns;
		}
		if (d_ns > max_ns)
		{
			max_ns = d_ns;
		}
	}
	avg_ns = avg_ns / 1000000;

	std::cout << "Time taken for 1 million iterations: " << std::chrono::duration<std::int64_t, std::nano>(std::chrono::steady_clock::now() - t0).count() << " ns" << '\n';
	std::cout << "Smallest gap measured: " << min_ns << '\n';
	std::cout << "Average gap measured: " << avg_ns << '\n';
	std::cout << "Largest gap measured: " << max_ns << '\n';
    
}

