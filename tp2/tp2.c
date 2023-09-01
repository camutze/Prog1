#include <stdio.h>
#include <stdlib.h>
#include "racionais.h"
#define SEED 0
#define MAX 100
void trocar(struct racional *a, struct racional *b);
void bolha_ord(struct racional *r, int n);
void imprime_vet(struct racional r[], int n);
void bubble_sort(struct racional *r, int n);




int main()
{
    srand(SEED);
    int n;
    struct racional r[MAX];

    do
    {
        scanf("%d", &n);

    } while (n <= 0 || n > 100);

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &r[i].num);
        scanf("%d", &r[i].den);
    }

    imprime_vet(r, n);

    for (int i = 0; i < n; i++)
    {
        if (!(r[i].valido = valido_r(r[i])))
        {
            r[i] = r[n - 1];
            n--;
        }
    }

    printf("\n");
    imprime_vet(r, n);

    bubble_sort(r, n);
    printf("\n");
    imprime_vet(r, n);

    struct racional sum;
    sum = r[0];

    for (int i = 1; i < n; i++)
    {
        soma_r(sum, r[i], &sum);
    }

    printf("\nSoma: %d / %d ", sum.num, sum.den);

    return 0;
}

void imprime_vet(struct racional r[], int n)
{
    for (int i = 0; i < n; i++)
    {
        imprime_r(r[i]);
    }
}

void bubble_sort(struct racional *r, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (compara_r(r[j], r[j + 1]) == 1)
            {
                trocar(&r[j], &r[j + 1]);
            }
        }
    }
}

void trocar(struct racional *a, struct racional *b)
{
    struct racional mutz;
    mutz = *a;
    *a = *b;
    *b = mutz;
}
