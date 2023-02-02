#include <stdio.h>
#include <stdbool.h>

#include "traverse_opp_tree.c"

void gen_no_large(int *large, int *gamesets, int *k)
{
    int K = *k;
    for (int a=1; a<=10; a++)
    {
        for (int b=a+1; b<=10; b++)
        {
            for (int c=b+1; c<=10; c++)
            {
                gamesets[(*k)*6+0] = a;
                gamesets[(*k)*6+1] = a;
                gamesets[(*k)*6+2] = b;
                gamesets[(*k)*6+3] = b;
                gamesets[(*k)*6+4] = c;
                gamesets[(*k)*6+5] = c; 
                (*k)++;
            }
        }
    }
    printf("%d\n", (*k)-K);

    K = *k;
    for (int a=1; a<=10; a++)
    {
        for (int b=a+1; b<=10; b++)
        {
            for (int c=1; c<=10; c++)
            {
                for (int d=c+1; d<=10; d++)
                {
                    if (c!=a && c!=b && d!=a && d!=b)
                    {
                        gamesets[(*k)*6+0] = a;
                        gamesets[(*k)*6+1] = a;
                        gamesets[(*k)*6+2] = b;
                        gamesets[(*k)*6+3] = b;
                        gamesets[(*k)*6+4] = c;
                        gamesets[(*k)*6+5] = d; 
                        (*k)++;
                    }

                }
            }
        }
    }
    printf("%d\n", (*k)-K);

    K = *k;
    for (int a=1; a<=10; a++)
    {
        for (int b=1; b<=10; b++)
        {
            for (int c=b+1; c<=10; c++)
            {
                for (int d=c+1; d<=10; d++)
                {
                    for (int e=d+1; e<=10; e++)
                    {
                        if (b!=a && c!=a && d!=a && e!=a)
                        {
                            gamesets[(*k)*6+0] = a;
                            gamesets[(*k)*6+1] = a;
                            gamesets[(*k)*6+2] = b;
                            gamesets[(*k)*6+3] = c;
                            gamesets[(*k)*6+4] = d;
                            gamesets[(*k)*6+5] = e; 
                            (*k)++;
                        }
                    }
                }
            }
        }
    }
    printf("%d\n", (*k)-K);

    K = *k;
    for (int a=1; a<=10; a++)
    {
        for (int b=a+1; b<=10; b++)
        {
            for (int c=b+1; c<=10; c++)
            {
                for (int d=c+1; d<=10; d++)
                {
                    for (int e=d+1; e<=10; e++)
                    {
                        for (int f=e+1; f<=10; f++)
                        {
                            gamesets[(*k)*6+0] = a;
                            gamesets[(*k)*6+1] = b;
                            gamesets[(*k)*6+2] = c;
                            gamesets[(*k)*6+3] = d;
                            gamesets[(*k)*6+4] = e;
                            gamesets[(*k)*6+5] = f;
                            (*k)++;
                        }
                    }
                }
            }
        }
    }
    printf("%d\n", (*k)-K);

}

void gen_one_large(int *large, int *gamesets, int *k)
{

    int K = *k;
    for (int A=0; A<4; A++)
    {
        for (int a=1; a<=10; a++)
        {
            for (int b=a+1; b<=10; b++)
            {
                for (int c=1; c<=10; c++)
                {
                    if (c!=a && c!=b)
                    {
                        gamesets[(*k)*6+0] = large[A];
                        gamesets[(*k)*6+1] = a;
                        gamesets[(*k)*6+2] = a;
                        gamesets[(*k)*6+3] = b;
                        gamesets[(*k)*6+4] = b;
                        gamesets[(*k)*6+5] = c; 
                        (*k)++;
                    }

                }
            }
        }
    }
    printf("%d\n", (*k)-K);

    K = *k;
    for (int A=0; A<4; A++)
    {
        for (int a=1; a<=10; a++)
        {
            for (int b=1; b<=10; b++)
            {
                for (int c=b+1; c<=10; c++)
                {
                    for (int d=c+1; d<=10; d++)
                    {
                        if (b!=a && c!=a && d!=a)
                        {
                            gamesets[(*k)*6+0] = large[A];
                            gamesets[(*k)*6+1] = a;
                            gamesets[(*k)*6+2] = a;
                            gamesets[(*k)*6+3] = b;
                            gamesets[(*k)*6+4] = c;
                            gamesets[(*k)*6+5] = d; 
                            (*k)++;
                        }
                    }
                }
            }
        }
    }
    printf("%d\n", (*k)-K);

    K = *k;
    for (int A=0; A<4; A++)
    {
        for (int a=1; a<=10; a++)
        {
            for (int b=a+1; b<=10; b++)
            {
                for (int c=b+1; c<=10; c++)
                {
                    for (int d=c+1; d<=10; d++)
                    {
                        for (int e=d+1; e<=10; e++)
                        {
                            gamesets[(*k)*6+0] = large[A];
                            gamesets[(*k)*6+1] = a;
                            gamesets[(*k)*6+2] = b;
                            gamesets[(*k)*6+3] = c;
                            gamesets[(*k)*6+4] = d;
                            gamesets[(*k)*6+5] = e; 
                            (*k)++;
                        }
                    }
                }
            }
        }
    }
    printf("%d\n", (*k)-K);

}

const int MAX_GAMESETS = 14000;

int main()
{
    bool _reachable[900];
    int queue[MAX_QUEUE_SIZE*6];

    int gamesets[MAX_GAMESETS*6];
    bool reachable[MAX_GAMESETS*900];

    int large[4] = {100, 75, 50, 25};

    int k=0;
    gen_no_large(large, gamesets, &k);
    printf("\n%d\n\n", k);
    int K1=k;

    gen_one_large(large, gamesets, &k);
    printf("\n%d\n\n", k-K1);
    int K2=k;

    // int gameset[6];
    // for(int i=0; i<k; i++)
    // {
    //     for(int j=0; j<6; j++)
    //     {
    //         gameset[j] = gamesets[i*6 + j];
    //     }
    //     traverse(_reachable, queue, gameset);
    // }

}