#include "structs.h"
#include "traverse_opp_tree.c"

__kernel void batch_calc_reachable( __global   GameSet_t* gamesets,
                                    __global Reachable_t* reachable_arrs)
{
    int i = get_global_id(0);

    bool reachable[900];
    int _queue[MAX_QUEUE_SIZE*6];
    int gameset[6];

    for(int j=0; j<6; j++)
    {
        gameset[j] = gamesets[i][j];
    }

    traverse(reachable, _queue, gameset);

    for(int j=0; j<900; j++)
    {
        reachable_arrs[i][j] = reachable[j];
    }

}
