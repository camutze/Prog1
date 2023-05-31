#include <stdlib.h>
#include "liblista_circular.h"

lista_t *lista_cria() {
    lista_t *l = (lista_t *)malloc(sizeof(lista_t));
    l->ini = NULL;
    return l;
}

void lista_destroi(lista_t **l) {
    if (l == NULL || *l == NULL)
        return;

    nodo_t *atual = (*l)->ini;
    nodo_t *primeiro = atual;

    while (atual != NULL) {
        nodo_t *prox = atual->prox;
        free(atual);
        atual = prox;

        if (atual == primeiro)
            break;
    }

    free(*l);
    *l = NULL;
}

int lista_insere_ordenado(lista_t *l, elemento_t *elemento) {
    nodo_t *novo = (nodo_t *)malloc(sizeof(nodo_t));
    novo->elemento = elemento;
    novo->prox = NULL;
    novo->prev = NULL;

    if (l->ini == NULL) {
        l->ini = novo;
        novo->prox = novo;
        novo->prev = novo;
        return 1;
    }

    nodo_t *atual = l->ini;
    nodo_t *anterior = NULL;

    do {
        if (elemento->chave <= atual->elemento->chave)
            break;

        anterior = atual;
        atual = atual->prox;
    } while (atual != l->ini);

    if (anterior == NULL) {
        novo->prox = l->ini;
        novo->prev = l->ini->prev;
        l->ini->prev->prox = novo;
        l->ini->prev = novo;
        l->ini = novo;
    } else {
        anterior->prox = novo;
        novo->prev = anterior;
        novo->prox = atual;
        atual->prev = novo;
    }

    return 1;
}

int lista_remove_ordenado(lista_t *l, elemento_t *elemento) {
    if (l->ini == NULL)
        return 0;

    nodo_t *atual = l->ini;
    nodo_t *anterior = NULL;

    do {
        if (atual->elemento->chave == elemento->chave)
            break;

        anterior = atual;
        atual = atual->prox;
    } while (atual != l->ini);

    if (atual->elemento->chave != elemento->chave)
        return 0;

    if (atual == l->ini) {
        l->ini = atual->prox;
        l->ini->prev = atual->prev;
        atual->prev->prox = l->ini;
    } else {
        anterior->prox = atual->prox;
        atual->prox->prev = anterior;
    }

    free(atual);
    return 1;
}

int lista_vazia(lista_t *l) {
    return (l->ini == NULL);
}
