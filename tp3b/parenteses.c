#include "libpilha.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int verifica_parenteses(const char *expressao)
{
    pilha_t *pilha = pilha_cria();
    int tamanho = strlen(expressao);
    int i;

    for (i = 0; i < tamanho; i++)
    {
        char c = expressao[i];
        if (c == '(' || c == '[' || c == '{')
        {
            push(pilha, c);
        }
        else if (c == ')' || c == ']' || c == '}')
        {
            if (pilha_vazia(pilha))
            {
                pilha_destroi(&pilha);
                return 0;
            }

            int topo;
            pilha_topo(pilha, &topo);
            if ((c == ')' && topo == '(') || (c == ']' && topo == '[') || (c == '}' && topo == '{'))
            {
                int dado;
                pop(pilha, &dado);
            }
            else
            {
                pilha_destroi(&pilha);
                return 0;
            }
        }
    }

    int vazia = pilha_vazia(pilha);
    pilha_destroi(&pilha);
    return vazia;
}

int main()
{
    char *expressao = (char *)malloc(100 * sizeof(char));
    if (expressao == NULL)
    {
        printf("Erro ao alocar memória.\n");
        return 1;
    }

    printf("Digite a expressão aritmética: ");
    fgets(expressao, 100, stdin);

    if (verifica_parenteses(expressao))
    {
        printf("CORRETA\n");
    }
    else
    {
        printf("INCORRETA\n");
    }

    free(expressao);

    return 0;
}