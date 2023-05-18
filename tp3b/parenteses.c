#include "libpilha.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define TAM 100
int eh_igual(pilha_t *fila, char *dado1, char *dado2)
{

}
int main()
{
    char *expressao;
    int i;
    pilha_t *pilha;
    pilha = pilha_cria();

    if (!(expressao = malloc(TAM * sizeof(char))))
        exit(0);
    printf("Digite a expressão aritmética: ");
    scanf("%s", expressao);

    i = 0;
    while (expressao[i] != '\0')
    {
        if (expressao[i] == '{' || expressao[i] == '(' || expressao[i] == '[')
        {
            if (!push(pilha, expressao[i]))
                printf("erro de push");
        }
        else if (expressao[i] == '}' || expressao[i] == ')' || expressao[i] == ']')
            if (!pop(pilha, expressao[i]))
                printf("erro de pop");

        i++;
    }

    if (pilha_vazia(pilha))
    {
        printf("CORRETO");
        return 0;
    }

    printf("INCORRETO");
    return 0;
}