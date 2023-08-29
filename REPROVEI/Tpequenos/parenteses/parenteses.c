#include "libpilha.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define TAM 100

/* Retorna 0 caso Não existe no topo da fila o complementar,
    Retorna 1 caso contrario */
int test_char(pilha_t *pilha, char delimitador)
{
    int dado = (int)delimitador;
    if (pilha_vazia(pilha))
        return 0;
    else if (pilha->topo->dado == dado)
    {
        int valor;
        if (!pop(pilha, &valor))
        {
            printf("Erro ao desempilhar\n");
            exit(0);
        }
        return 1;
    }

    return 0;
}


int main()
{
    char *expressao;
    int i;
    pilha_t *pilha;
    pilha = pilha_cria();

    if (!(expressao = malloc(TAM * sizeof(char))))
        return 0;

    printf("Digite a expressão aritmética: ");
    scanf("%[^\n]", expressao);

    for (i = 0; expressao[i] != '\0'; i++)
    {
        if (expressao[i] == '{' || expressao[i] == '[' || expressao[i] == '(')
        {
            int dado = (int)expressao[i];
            if (!push(pilha, dado))
            {
                printf("Erro ao empilhar");
                exit(0);
            }
        }
        else if (expressao[i] == '}')
        {
            if (!test_char(pilha, '{'))
            {
                printf("INCORRETA\n");
                exit(0);
            }
        }
        else if (expressao[i] == ']')
        {
            if (!test_char(pilha, '['))
            {
                printf("INCORRETA\n");
                exit(0);
            }
        }
        else if (expressao[i] == ')')
        {
            if (!test_char(pilha, '('))
            {
                printf("INCORRETA\n");
                exit(0);
            }
        }
    }

    if (!pilha_vazia(pilha))
    {
        printf("INCORRETA\n");
        exit(0);
    }
    pilha_destroi(&pilha);
    printf("CORRETA\n");
    free(expressao);
    return 0;
}
