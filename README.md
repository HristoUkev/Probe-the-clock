# Probe the clock

On this machine, steady_clock advances in steps of 100 ns, so it can't distinguish
anything shorter; one call to now() costs about 22–46 ns on average depending on
the build, and the largest single difference in a million readings ranged from
10,000 to 177,500 ns.

## What this measures
1,000,000 iterations, two `steady_clock::now()` calls per iteration. A *difference* is the
time between two consecutive readings of the clock, in nanoseconds.
Source: [Probe the clock.cpp](Probe%20the%20clock/Probe%20the%20clock.cpp)

## Results
| Build | Run | Total (ms) | Smallest non-zero difference (ns) | Mean difference (ns) | Largest difference (ns) |
|---|---|---|---|---|---|
| VS Debug | 1 | 206.0 | 100 | 46 | 34,900 |
| VS Debug | 2 | 194.4 | 100 | 31 | 45,400 |
| VS Debug | 3 | 206.0 | 100 | 40 | 22,700 |
| VS Debug | 4 | 207.1 | 100 | 40 | 177,500 |
| VS Debug | 5 | 201.5 | 100 | 33 | 161,600 |
| VS Release | 1 | 60.7 | 100 | 24 | 77,900 |
| VS Release | 2 | 59.0 | 100 | 24 | 29,500 |
| VS Release | 3 | 58.5 | 100 | 24 | 10,000 |
| VS Release | 4 | 59.1 | 100 | 24 | 125,500 |
| VS Release | 5 | 58.7 | 100 | 22 | 29,500 |
| GCC -O2 | 1 | 90.1 | 100 | 43 | 36,300 |
| GCC -O2 | 2 | 90.6 | 100 | 44 | 106,100 |
| GCC -O2 | 3 | 89.7 | 100 | 43 | 160,900 |
| GCC -O2 | 4 | 89.9 | 100 | 44 | 145,900 |
| GCC -O2 | 5 | 85.6 | 100 | 41 | 27,200 |


## Predictions vs results
| Prediction | Result |
|---|---|
| Smallest non-zero difference: 100 ns | 100 ns in all 15 runs |
| Release total time lower than Debug | Yes: 58.5–60.7 ms vs 194–207 ms |
| Release mean difference higher than Debug | No: 22–24 ns vs 31–46 ns |

## Findings
1. **The smallest non-zero difference is 100 ns in every run.**
   - **Observation:**  In all 15 runs (5 per build, 3 builds) the smallest non-zero difference
was exactly 100 ns. The largest difference in each run was always a multiple of 100 ns.
An earlier version of the program that counted zero differences reported a smallest
difference of 0 ns. 
   - **Explanation:** The clock's counter moves in steps of 100 ns. Two readings taken inside the same
step give a difference of 0. One-boundary pairs give 100 ns, pairs that cross
     several give 200 ns, 300 ns and so on.
So the smallest non-zero difference the program can ever report is 100, even though
the real time between the two calls is only about 22-46 ns which is an estimate from the mean difference.
- **Status:** tested for the Windows performance counter (`QueryPerformanceFrequency`
     = 10,000,000 ticks/s = 100 ns per tick). That `steady_clock` reads this counter in
     both libraries is likely, but I did not check it.
- **Test:** [qpf_test.cpp](qpf_test/qpf_test.cpp)
                     
















   
