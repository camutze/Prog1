#include <stdio.h>
#include <stdlib.h>
#include "racionais.h"

aleat(int min, int max)
{
    if (max < min)
    {
        printf("Erro: max deve ser maior do que min.\n");
        exit(1);
    }

    return min + (rand() % (max - min + 1));
}

int mdc(int a, int b)
{
    if (b == 0)
        return a;
    return mdc(b, a % b);
}

int mmc(int a, int b)
{
    return ((a * b) / mdc(a, b));
}

struct racional simplifica_r(struct racional r)
{
    if (r.den == 0)
    {
        printf("ERRO. Fração indefinida\n");
        exit(1);
    }
}