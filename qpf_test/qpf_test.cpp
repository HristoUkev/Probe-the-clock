#include <Windows.h>
#include <iostream>
#include <cstdint>

int main()
{
    LARGE_INTEGER frequency;
    QueryPerformanceFrequency(&frequency);

    const double ticks_per_second = static_cast<double>(frequency.QuadPart);
    const double ns_per_tick = 1000000000.0 / ticks_per_second;

    std::cout << "Ticks per second: " << frequency.QuadPart << '\n';
    std::cout << "Nanoseconds per tick: " << ns_per_tick << '\n';
    return 0;
}
