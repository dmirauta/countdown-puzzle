# Countdown solutions enumerator

Enumerates all solvable target numbers for all possible random gamesets, given a set of large numbers. Can also be used to list solutions for given target and gameset (only in python solution currently).

## Countdown game

The generalised game is to pick up to 4 from a set of 4 "Large" (11-100) and remaining from small (1-10) to make six, where smalls can be duplicated once

13243 possible games sets (per set of 4 large nums), arranged as:

* 0 Large:

  * a a b b c c

  * a a b b c d

  * a a b c d e

  * a b c d e f

* 1 Large:

  * A a a b b c

  * A a a b c d

  * A a b c d e

* 2 Large:

  * A B a a b b

  * A B a a b c

  * A B a b c d

* 3 Large:

  * A B C a a b

  * A B C a b c

* 4 Large:

  * A B C D a a

  * A B C D a b

## Code info

Currently, `gamesets.py` generates all gamesets and stores them to a file called `A_B_C_D.res` where A,B,C,D is the large set. Then `game_reachability.c` iterates through these and lists all the unreachable targets on a corresponding line in `A_B_C_D_unreachable.res`.
