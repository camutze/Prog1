#include <stdio.h>
#include <stdlib.h>
#include "racionais.h"
#define SEED 0
#define MAX 100
void trocar(struct racional *a, struct racional *b);
void bolha_ord(struct racional *r, int n);
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

    printf("ordena aqui\n");
    imprime_vet(r, n);
    printf("\n");

    return 0;
}

void imprime_vet(struct racional r[], int n)
{
    for (int i = 0; i < n; i++)
    {
        imprime_r(r[i]);
    }
}

void bolha_ord(struct racional r[], int n)
{
    for (int i = 1; i < n; i++)
    {
        struct racional chave = r[i];
        int j = i - 1;

        while (j >= 0 && compara_r(r[j], chave) == 1)
        {
            r[j + 1] = r[j];
            j--;
        }

        r[j + 1] = chave;
    }
}

void trocar(struct racional *a, struct racional *b)
{
    struct racional mutz = *a;
    *a = *b;
    *b = mutz;
}
