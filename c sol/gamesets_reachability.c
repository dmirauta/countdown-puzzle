#include <stdio.h>
#include <stdbool.h>

#include "traverse_op_tree.c"

const int MAX_GAMESETS = 13243;

void print_unreachable(bool *reachable, FILE *file)
{
    for (int i=0; i<900; i++)
    {
        if (!reachable[i])
        {
            fprintf(file, "%d ", i+100);
        }
    }
    fprintf(file, "\n");
}

int main()
{
    FILE *in_file  = fopen("../25_50_75_100.res", "r");
    FILE *out_file = fopen("25_50_75_100_unreachable.res", "w");

    bool reachable[900];
    int queue[MAX_QUEUE_SIZE*6];

    int a,b,c,d,e,f;
    for(int i=0; i<MAX_GAMESETS; i++)
    {
        fscanf(in_file, "%d %d %d %d %d %d\n", &a, &b, &c, &d, &e, &f); 
        int gameset[6] = {a,b,c,d,e,f};
        traverse(reachable, queue, gameset);
        print_unreachable(reachable, out_file);
    }

}
