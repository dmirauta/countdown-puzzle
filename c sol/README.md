# C graphsearch solution

Not quick enough, would take `2555190*37/(3600*24)` days or roughly 3 years.

Intended for GPU execution via OpenCL, if this can get a 1000x speedup than this could be done in a day, code kept very primitive for this reason.

## Code info

Generate executable with `make`.

The executable `./csol.out` iterates through the gameset file and lists all the unreachable targets on a corresponding line in `A_B_C_D_unreachable.res`.
