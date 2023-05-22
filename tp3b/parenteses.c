#include "libpilha.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define TAM 100

/*retorna 0 para INCORRETO e 1 caso CORRETO*/
int test_char(pilha_t *pilha, char delimitador)
{
    int dado = (int)delimitador;
    if (pilha_vazia(pilha))
        return 0;

    else if (pilha->topo->dado == dado)
    {
        if (!pop(pilha, &dado))
        {
            printf("erro de pop");
            exit(0);
        }
        return 1;
    }

    return 0;
}
int main()
{
    char *expressao;
    int i, dado;
    pilha_t *pilha;
    pilha = pilha_cria();

    if (!(expressao = malloc(TAM * sizeof(char))))
        exit(0);
    printf("Digite a expressão aritmética: ");
    scanf("%s", expressao);

    i = 0;
    while (expressao[i] != '\0')
    {
        if (expressao[i] == '{' || expressao[i] == '[' || expressao[i] == '(')
        {
            dado = (int)expressao[i];
            if (!push(pilha, dado))
                printf("erro de push");
        }

        /* Teste para remover na pilha*/
        else if (expressao[i] == '}')
        {
            if (!test_char(pilha, '{'))
            {
                printf("INCORRETO - {}");
                exit(0);
            }
        }

        else if (expressao[i] == ']')
        {
            if (!test_char(pilha, '['))
            {
                printf("INCORRETO - []");
                exit(0);
            }
        }

        else if (expressao[i] == ')')
        {
            if (!test_char(pilha, '('))
            {
                printf("INCORRETO - ()");
                exit(0);
            }
        }
        i++;
    }
    /* final*/
    if (!pilha_vazia(pilha))
    {
        printf("CORRETO");
        return 0;
    }

    printf("INCORRETO - pilha n vazia");
    return 0;
}