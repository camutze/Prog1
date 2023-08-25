#include <stdio.h>
#include <stdlib.h>
#include "racionais.h"

int main()
{
    struct racional teste, teste1;

    printf("Digite num: \n");
    scanf("%d", &teste.num);
    fflush(stdin);
    printf("Digite den: \n");
    fflush(stdin);
    printf("\n\n\n");

    scanf("%d", &teste.den);
    teste.valido = valido_r(teste);
    if (!teste.valido)
    {
        printf("teste Inválido\n");
    }
    printf("Digite num2: \n");
    scanf("%d", &teste1.num);
    printf("Digite den2: \n");
    scanf("%d", &teste1.den);
    teste1.valido = valido_r(teste1);

    if (!teste1.valido)
    {
        printf("teste Inválido\n");
    }

    imprime_r(teste);
    imprime_r(teste1);

    teste1 = simplifica_r(teste1);
    teste = simplifica_r(teste);

    printf("Soma: \n");
    imprime_r(soma_r(teste, teste1));
    printf("\n");

    printf("subtração: \n");
    imprime_r(subtrai_r(teste, teste1));
    printf("\n");

    printf("Multiplicação: \n");
    imprime_r(multiplica_r(teste, teste1));
    printf("\n");

    struct racional divisao_resultado = divide_r(teste, teste1);

    if (!divisao_resultado.valido)
    {
        printf("DIVISAO INVALIDA\n");
        return 1;
    }

    printf("Divisão: \n");
    imprime_r(divisao_resultado);
    printf("\n");

    return 0;
}