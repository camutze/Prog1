#include <stdlib.h>
#include "liblista_circular.h"

lista_t *lista_cria()
{
    lista_t *l;
    nodo_t *sent;
    if (!(l = malloc(sizeof(lista_t))))
        return 0;

    if (!(sent = malloc(sizeof(nodo_t))))
        return 0;
    sent->elemento = NULL;
    sent->prox = sent; /*sentinela aponta para ele mesmo*/
    sent->prev = sent;
    l->ini = sent;
    return l;
}

void lista_destroi(lista_t **l)
{
    nodo_t *aux;

    while (*l != NULL)
    {
        aux = (*l)->ini;
        (*l)->ini = aux->prox;
        free(aux->elemento);
        free(aux);
    }
    free(*l);
    (*l) = NULL;
}

int lista_insere_ordenado(lista_t *l, elemento_t *elemento)
{
    nodo_t *novo;
    nodo_t *aux;

    if (!(novo = malloc(sizeof(nodo_t))))
        return 0;

    l->ini->elemento = elemento;

    aux = l->ini->prox;
    while (elemento->chave < aux->elemento->chave)
    {
        aux = aux->prox;
    }

    novo->prox = aux;
    novo->prev = aux->prev;

    aux->prox = novo;
    novo->prox->prev = novo;

    return 1;
}

int lista_remove_ordenado(lista_t *l, elemento_t *elemento)
{
    nodo_t *aux;

    aux = l->ini->prox;
    l->ini->elemento = elemento;

    while (elemento->chave != aux->elemento->chave)
    {
        aux = aux->prox;
    }

    if (l->ini->elemento->chave == aux->elemento->chave)
        return 0;

    aux->prox->prev = aux->prev;
    aux->prev->prox = aux->prox;
    free(aux->elemento);
    free(aux);

    return 1;
}
