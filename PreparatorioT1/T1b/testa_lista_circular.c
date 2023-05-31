#include <stdio.h>
#include <stdlib.h>
#include "liblista_circular.h"

int main() {
    lista_t *lista = lista_cria();

    elemento_t *elemento1 = (elemento_t *)malloc(sizeof(elemento_t));
    elemento1->chave = 10;

    elemento_t *elemento2 = (elemento_t *)malloc(sizeof(elemento_t));
    elemento2->chave = 5;

    elemento_t *elemento3 = (elemento_t *)malloc(sizeof(elemento_t));
    elemento3->chave = 8;

    elemento_t *elemento4 = (elemento_t *)malloc(sizeof(elemento_t));
    elemento4->chave = 12;

    lista_insere_ordenado(lista, elemento1); 
    lista_insere_ordenado(lista, elemento2); 
    lista_insere_ordenado(lista, elemento3); 
    lista_insere_ordenado(lista, elemento4); 

    printf("Lista após as inserções:\n");
    nodo_t *atual = lista->ini;
    while (atual != NULL) {
        printf("%d ", atual->elemento->chave);
        atual = atual->prox;
    }
    printf("\n");

    lista_remove_ordenado(lista, elemento1);
    lista_remove_ordenado(lista, elemento4); 
    lista_remove_ordenado(lista, elemento3);

    printf("Lista após as remoções:\n");
    atual = lista->ini;
    while (atual != NULL) {
        printf("%d ", atual->elemento->chave);
        atual = atual->prox;
    }
    printf("\n");

    lista_destroi(&lista);
    free(elemento1);
    free(elemento2);
    free(elemento3);
    free(elemento4);

    return 0;
}
