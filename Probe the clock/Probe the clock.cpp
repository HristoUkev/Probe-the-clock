// Probe the clock.cpp : This file contains the 'main' function. Program execution begins and ends there.
#define NOMINMAX
#include <windows.h> // for SetThreadPriority and SetThreadAffinityMask
#include <iostream> 
#include <cstdint>  // for std::int64_t
#include <chrono> // for std::chrono
#include <string_view> // for std::string_view

//number of gaps over 1us will be aroud 30-40 in release and a bit more in debug and the ones over 10us are gonna range from 0-5 in release maybe more in debug but not with much. 
//The mean is gonna be around 20-30ns in release and around 30-45ns in debug.
//The smallest gap is gonna be 100ns in release and debug because the system clock resolution is limited.
//The largest gap is gonna be around 1us in release. The time taken for 1,000,000 iterations is gonna be around 50-70ms in release.
//Pinning would hopefully reduce the number of gaps over 1us and 10us and reduce the mean and largest gap.
//Raising the priority should also reduce the number of gaps over 1us and 10us and reduce the mean and largest gap.
//Both pinning and raising the priority should make the run time faster with samller gaps.

int main(int argc, char* argv[])
{
	std::string_view condition;

	constexpr int pinned_cpu = 4;

	constexpr std::int64_t iterations = 1'000'000;   

	// step 1: check the number of arguments
	if (argc == 1)
	{
		condition = "baseline";
	}
	else if (argc == 2)
	{
		// step 2: check the keyword in the first argument
		std::string_view first_arg = argv[1];
		if (first_arg == "pin")
		{
			condition = "pin";
		}
		else if (first_arg == "priority")
		{
			condition = "priority";
		}
		else if (first_arg == "both")
		{
			condition = "both";
		}
		else
		{
			// step 3: invalid argument
			std::cout << "Invalid argument. Please provide either 'pin' or 'priority' or 'both' as an argument." << std::endl;
			return 1;
		}
	}
	else 
	{
		// step 3: too many arguments
		std::cout << "Too many arguments." << std::endl;
		return 1;
	}

	std::cout << "condition: " << condition << '\n';

	// step 4: apply the condition
	if (condition == "pin" || condition == "both")
	{
		// pinning code + check the return value
		DWORD_PTR mask = 1ull << pinned_cpu;

		DWORD_PTR previous = SetThreadAffinityMask(GetCurrentThread(), mask);

		if (previous == 0)                       // <- new: did Windows refuse?
		{
			std::cerr << "Pinning to processor " << pinned_cpu << " failed.\n";
			return 1;
		}
		std::cout << "pinned to processor " << pinned_cpu << '\n';

	}
	if (condition == "priority" || condition == "both")
	{
		// priority code + check the return value
		BOOL ok = SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS);

		if (ok == 0)                                  // 0 means Windows refused
		{
			std::cerr << "Raising priority failed.\n";
			return 1;
		}
		std::cout << "priority class: " << GetPriorityClass(GetCurrentProcess()) << '\n';
	}


	

	std::chrono::steady_clock::time_point t0 = std::chrono::steady_clock::now();
	std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();
	std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();

	std::chrono::duration<std::int64_t, std::nano> d_ns = t2 - t1;
	std::chrono::duration<std::int64_t, std::nano> min_ns = std::chrono::duration<std::int64_t, std::nano>::max();
	std::chrono::duration<std::int64_t, std::nano> max_ns = std::chrono::duration<std::int64_t, std::nano>::min();
	std::chrono::duration<std::int64_t, std::nano> avg_ns = std::chrono::duration<std::int64_t, std::nano>(0);

	std::int64_t over_1us = 0;
	std::int64_t over_10us = 0;


	for (std::int64_t i = 0; i < iterations; i++)
	{
		t1 = std::chrono::steady_clock::now();
		t2 = std::chrono::steady_clock::now();
		
		d_ns = t2 - t1;

		avg_ns = (avg_ns + d_ns);
		//if the current gap is smaller than the previous smallest gap and not a zero, update the smallest gap 
		if ((d_ns < min_ns) && d_ns != std::chrono::duration<std::int64_t, std::nano>(0))
		{
		
			min_ns = d_ns;

			
			
		}
		if (d_ns > std::chrono::microseconds{ 1 }) 
		{
			over_1us++; 
		}
		if (d_ns > std::chrono::microseconds{ 10 }) 
		{
			over_10us++; 
		}
		if (d_ns > max_ns)
		{
			max_ns = d_ns;
		}
	}
	avg_ns = avg_ns / iterations;

	std::cout << "Time taken for " << iterations << " iterations: " << std::chrono::duration<std::int64_t, std::nano>(std::chrono::steady_clock::now() - t0).count() << " ns" << '\n';
	std::cout << "Smallest gap measured: " << min_ns << '\n';
	std::cout << "Average gap measured: " << avg_ns << '\n';
	std::cout << "Largest gap measured: " << max_ns << '\n';
	std::cout << "Number of gaps over 1us: " << over_1us << '\n';
	std::cout << "Number of gaps over 10us: " << over_10us << '\n';
}

