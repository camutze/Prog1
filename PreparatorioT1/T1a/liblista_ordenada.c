#include "liblista_ordenada.h"
#include <stdlib.h>
#include <stdio.h>
lista_t *lista_cria()
{
    lista_t *nova_lista;
    if (!(nova_lista = malloc(sizeof(lista_t))))
        return 0;

    nova_lista->ini = NULL;

    return nova_lista;
}

void lista_destroi(lista_t **l)
{
    nodo_t *aux;

    while ((*l)->ini)
    {
        aux = (*l)->ini;
        (*l)->ini = (*l)->ini->prox;
        free(aux);
    }
    free(*l);
    aux = NULL;
    *l = NULL;
}

int lista_insere_ordenado(lista_t *l, elemento_t *elemento)
{
    nodo_t *novo_nodo;
    nodo_t *aux;

    if (!(novo_nodo = malloc(sizeof(nodo_t))))
        return 0;

    novo_nodo->elemento = elemento;

    if (l->ini == NULL)
    {
        novo_nodo->prox = NULL;
        l->ini = novo_nodo;
    }

    else if (l->ini->elemento->chave > elemento->chave)
    {
        novo_nodo->prox = l->ini->prox;
        l->ini->prox = novo_nodo;
    }
    else
    {
        aux = l->ini->prox;
        while (aux->prox != NULL && aux->prox->elemento->chave < elemento->chave)
        {
            aux = aux->prox;
        }

        novo_nodo->prox = aux->prox;
        aux->prox = novo_nodo;
    }

    return 1;
}

int lista_remove_ordenado(lista_t *l, elemento_t *elemento)
{
    if (l->ini == NULL)
    {
        return 0;
        printf("lista ja vazia\n");
    }

    nodo_t *aux;
    nodo_t *tmp;

    if (l->ini->elemento->chave == elemento->chave)
    {
        aux = l->ini;
        l->ini = l->ini->prox;
        free(aux);
    }
    else
    {
        aux = l->ini->prox;
        while (aux->prox != NULL)
        {
            if (aux->prox->elemento->chave == elemento->chave)
            {
                break;
            }
            aux = aux->prox;
        }
        if (!aux)
            return 0;

        tmp = aux->prox;
        aux->prox = tmp->prox;
        free(tmp);
    }
    return 1;
}
