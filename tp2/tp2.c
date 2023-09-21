#include <stdio.h>
#include <stdlib.h>
#include "racionais.h"
#define SEED 0
#define MAX 100

int gerar_aleat(struct racional r[], int n);
void imprime_vet(struct racional r[], int n);
void sem_invalido(struct racional r[], int *n);
void soma_tudo(struct racional r[], struct racional *soma, int n);
void trocar(struct racional *a, struct racional *b);
void bolha_ord(struct racional r[], int n);

int main()
{
    int n;
    struct racional r[MAX];
    struct racional soma;

    srand(SEED);

    do
    {
        scanf("%d", &n);
    } while (n <= 0 || n > 100);

    if (!(gerar_aleat(r, n)))
        return -1;

    imprime_vet(r, n);

    sem_invalido(r, &n);
    imprime_vet(r, n);

    bolha_ord(r, n);
    imprime_vet(r, n);

    soma_tudo(r, &soma, n);
    printf("a soma de todos os elementos eh: ");
    imprime_r(soma);
    printf("\n");

    return 0;
}
/*FIM DO MAIN*/
void soma_tudo(struct racional r[], struct racional *soma, int n)
{
    *soma = r[0];
    for (int i = 1; i < n; i++)
    {
        /*!!! Overflow em alguns casos !!!*/
        if (!(soma_r(*soma, r[i], soma)))
            return;
        if (!(simplifica_r(soma)))
            return;
    }
}

void sem_invalido(struct racional r[], int *n)
{
    for (int i = 0; i < *n; i++)
    {
        if (!(r[i].valido = valido_r(r[i])))
        {
            r[i] = r[*n - 1];
            printf("n: %d", *n);
            (*n)--;
        }
    }
}

int gerar_aleat(struct racional r[], int n)
{
    for (int i = 0; i < n; i++)
    {
        r[i] = sorteia_r(n);
    }
    if (!(simplifica_r(r)))
        return 0;
    return 1;
}

void imprime_vet(struct racional r[], int n)
{
    for (int i = 0; i < n; i++)
    {
        imprime_r(r[i]);
        printf(" ");
    }
    printf("\n");

}

void trocar(struct racional *a, struct racional *b)
{
    struct racional mutz = *a;
    *a = *b;
    *b = mutz;
}

void bolha_ord(struct racional r[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (compara_r(r[j], r[j + 1]) > 0)
            {
                trocar(&r[j], &r[j + 1]);
            }
        }
    }
}
