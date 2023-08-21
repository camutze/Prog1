#include <stdio.h>
#include <stdlib.h>
#include "racionais.h"
#define SEED 10
/* Arquivo MAIN que usa o TAD racionais */

/* coloque seus includes aqui */
int ler(int max)
{
    int numero;
    do
    {
        scanf("%d", &numero);

    } while (numero > max && numero > 0);

    return numero;
}

int main()
{
    srand(SEED);
    int n, max;
    struct racional r1, r2;

    n = ler(100);
    max = ler(30);

    for (int i = 1; i <=n; i++)
    {
        printf("%d: ", i);

        r1 = sorteia_r(max);
        r2 = sorteia_r(max);
        
        imprime_r(r1);
        imprime_r(r2);
        if (!(r1.valido) || !(r2.valido))
        {
            printf("NUMERO INVALIDO\n");
            return 1;
        }
        
        imprime_r(soma_r(r1, r2));
        imprime_r(subtrai_r(r1, r2));
        imprime_r(multiplica_r(r1, r2));

        struct racional divisao_resultado = divide_r(r1, r2);

        if (!divisao_resultado.valido)
        {
            printf("DIVISAO INVALIDA\n");
            return 1;
        }

        imprime_r(divisao_resultado);

        printf("\n");
    }

    return 0;
}
