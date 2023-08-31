#include <stdio.h>
#include <stdlib.h>
#include "racionais.h"
#define SEED 0
#define MAX 100
void trocar(struct racional *a, struct racional *b);
void bolha_ord(struct racional r[], int n);
void imprime_vet(struct racional r[], int n);

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
        r[i] = sorteia_r(n);
        imprime_r(r[i]);
    }
    printf("\n");
    imprime_vet(r, n);

    bolha_ord(r, n); // ordena

    printf("\n");
    imprime_vet(r, n);

    return 0;
}
void imprime_vet(struct racional r[], int n)
{
    for (int i = 0; i < n; i++)
    {
        if (valido_r(r[i]))
            imprime_r(r[i]);
    }
}

void bolha_ord(struct racional r[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        // Últimos i elementos já estão no lugar certo
        for (int j = 0; j < n - i - 1; j++)
        {
            // Troca se o elemento atual for maior que o próximo elemento
            if (compara_r(r[i], r[i + 1]) == 1)
            {
                trocar(&r[j], &r[j + 1]);
            }
        }
    }
}
void trocar(struct racional *a, struct racional *b)
{
    struct racional mutz = *a;
    *a = *b;
    *b = mutz;
}
