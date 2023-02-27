# C graphsearch solution

Not quick enough, would take `2555190*37/(3600*24)` or roughly 1000 days (around 3 years) to evaluate for all sets.

Intended for GPU execution via OpenCL, if this can get a 1000x speedup than this could be done in a day, code kept very primitive for this reason.

## Code info

Generate executable with `gcc "c sol/gamesets_reachability.c" -o calc_reachable -O3`.

The executable `./calc_reachable` iterates through the gameset file and lists all the unreachable targets on a corresponding line in `A_B_C_D_unreachable.res`.
