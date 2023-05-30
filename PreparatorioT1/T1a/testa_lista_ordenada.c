#include <stdio.h>
#include <stdlib.h>
#include "liblista_ordenada.h"

void imprimir_lista(lista_t *lista) {
    printf("Lista: ");
    nodo_t *atual = lista->ini;
    while (atual != NULL) {
        printf("%d ", atual->elemento->chave);
        atual = atual->prox;
    }
    printf("\n");
}

int main()
{
    lista_t *lista = lista_cria();

    int opcao;
    int chave;
    elemento_t *elemento;

    while (1)
    {
        printf("=== MENU ===\n");
        printf("1. Inserir elemento\n");
        printf("2. Remover elemento\n");
        printf("0. Sair\n");
        printf("Opção: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            printf("Digite a chave do elemento: ");
            scanf("%d", &chave);
            elemento = (elemento_t *)malloc(sizeof(elemento_t));
            elemento->chave = chave;
            if (lista_insere_ordenado(lista, elemento))
            {
                printf("Elemento inserido com sucesso.\n");
            }
            else
            {
                printf("Falha ao inserir o elemento.\n");
                free(elemento);
            }
            imprimir_lista(lista);
            break;

        case 2:
            printf("Digite a chave do elemento a ser removido: ");
            scanf("%d", &chave);
            elemento = (elemento_t *)malloc(sizeof(elemento_t));
            elemento->chave = chave;
            if (lista_remove_ordenado(lista, elemento))
            {
                printf("Elemento removido com sucesso.\n");
                free(elemento);
            }
            else
                printf("Elemento não encontrado na lista.\n");
                
            free(elemento);
            imprimir_lista(lista);
            break;

        case 0:
            lista_destroi(&lista);
            return 0;

        default:
            printf("Opção inválida. Tente novamente.\n");
        }

        printf("\n");
    }
}
