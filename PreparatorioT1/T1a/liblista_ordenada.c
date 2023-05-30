#include <stdio.h>
#include <stdlib.h>
#include "liblista_ordenada.h"

lista_t *lista_cria()
{
    lista_t *l = (lista_t *)malloc(sizeof(lista_t));
    if (l != NULL)
    {
        l->ini = NULL;
    }
    return l;
}

void lista_destroi(lista_t **l)
{
    if (l != NULL && *l != NULL)
    {
        nodo_t *atual = (*l)->ini;
        while (atual != NULL)
        {
            nodo_t *prox = atual->prox;
            free(atual->elemento);
            free(atual);
            atual = prox;
        }
        free(*l);
        *l = NULL;
    }
}

int lista_insere_ordenado(lista_t *l, elemento_t *elemento)
{
    if (l == NULL || elemento == NULL)
    {
        return 0;
    }

    nodo_t *novo = (nodo_t *)malloc(sizeof(nodo_t));
    if (novo == NULL)
    {
        return 0;
    }
    novo->elemento = elemento;

    if (l->ini == NULL || elemento->chave < l->ini->elemento->chave)
    {
        novo->prox = l->ini;
        l->ini = novo;
        return 1;
    }

    nodo_t *atual = l->ini;
    while (atual->prox != NULL && atual->prox->elemento->chave < elemento->chave)
    {
        atual = atual->prox;
    }

    novo->prox = atual->prox;
    atual->prox = novo;
    return 1;
}

int lista_remove_ordenado(lista_t *l, elemento_t *elemento)
{
    nodo_t *aux, *temp;

    if (l->ini)
        return 0;

    else if (l->ini->elemento->chave == elemento->chave)
    {
        aux = l->ini;
        l->ini = aux->prox;
        free(aux);
        return 1;
    }
    aux = l->ini;
    while (aux->prox != NULL && aux->prox->elemento->chave < elemento->chave)
        aux = aux->prox;

    if (elemento->chave == aux->prox->elemento->chave)
    {
        temp = aux->prox;
        aux->prox = temp->prox;
        free(temp);
        return 1;
    }
    else
        return 0;
}
