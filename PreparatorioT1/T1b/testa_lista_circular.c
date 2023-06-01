#include <stdio.h>
#include <stdlib.h>
#include "liblista_circular.h"
void imprime_lista(lista_t *l)
{
    nodo_t *atual = l->ini;
    while (atual != NULL)
    {
        printf("%d ", atual->elemento->chave);
        atual = atual->prox;
    }
    printf("\n");
}
int main()
{
    lista_t *lista = lista_cria();

    elemento_t *elemento1 = malloc(sizeof(elemento_t));
    elemento1->chave = -1;
    elemento_t *elemento2 = malloc(sizeof(elemento_t));
    elemento2->chave = 0;
    elemento_t *elemento3 = malloc(sizeof(elemento_t));
    elemento3->chave = 1;
    elemento_t *elemento4 = malloc(sizeof(elemento_t));
    elemento4->chave = 2;

    printf("inserindo  -1 ate 2\n");
    lista_insere_ordenado(lista, elemento1);
    lista_insere_ordenado(lista, elemento2);
    lista_insere_ordenado(lista, elemento3);
    lista_insere_ordenado(lista, elemento4);

    printf("Lista após as inserções:\n");
    imprime_lista(lista);

    printf("Removendo -1 , 0 , 2 nesta ordem\n");
    lista_remove_ordenado(lista, elemento1);
    lista_remove_ordenado(lista, elemento4);
    lista_remove_ordenado(lista, elemento3);

    printf("Lista após as remoções:\n");
    imprime_lista(lista);

    printf("inserindo  3 descrecente até -1\n");
    lista_insere_ordenado(lista, elemento4);
    lista_insere_ordenado(lista, elemento3);
    lista_insere_ordenado(lista, elemento2);
    lista_insere_ordenado(lista, elemento1);

    printf("Lista após as inserções:\n");
    imprime_lista(lista);


    lista_destroi(&lista);
    free(elemento1);
    free(elemento2);
    free(elemento3);
    free(elemento4);

    return 0;
}