#include <stdio.h>
#include <stdbool.h>

#include "traverse_opp_tree.c"


void print_unreachable(bool *reachable)
{
    for (int i=0; i<900; i++)
    {
        if (!reachable[i])
        {
            printf("%d ", i+100);
        }
    }
    printf("\n");
}

int main()
{
    bool reachable[900];
    int queue[MAX_QUEUE_SIZE*6];
    int gameset[6] = {100, 75, 9, 9, 8, 3};

    bool success = traverse(reachable, queue, gameset);

    if (success)
    {
        printf("Unreachable: ");
        print_unreachable(reachable);
    } else
    {
        printf("Queue size was too small\n");

        // for (int i=0; i<MAX_QUEUE_SIZE; i++)
        // {
        //     printf("  %d %d %d %d %d %d\n\n", queue[i*6+0], queue[i*6+1], queue[i*6+2], queue[i*6+3], queue[i*6+4], queue[i*6+5]);
        // }
    }

    printf("%d calls to new node\n", nncalls);

}
