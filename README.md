# Probe the clock

All runs: 1,000,000 iterations, two `steady_clock::now()` calls per iteration.

| Build | Run | Total (ms) | Smallest non-zero difference (ns) | Average difference (ns) | Largest difference (ns) |
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
