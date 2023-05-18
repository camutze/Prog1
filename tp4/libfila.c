#include "libfila.h"
#include <stdlib.h>
#include <stdio.h>

fila_t *fila_cria()
{
    fila_t *new_fila;
    if (!(new_fila = malloc(sizeof(fila_t))))
        return 0;

    new_fila->cabeca = NULL;
    new_fila->cauda = NULL;
    new_fila->tamanho = 0;

    return new_fila;
}

void fila_destroi(fila_t **fila)
{
    if (!(*fila)) // se tiver  : ! ele testa for igual a zero/NULL
        return;

    int dado;
    while (dequeue(*fila, &dado))
    {
        // Continua removendo elementos até que a fila esteja vazia
    }

    free(*fila);
    *fila = NULL;
}
int enqueue(fila_t *fila, int dado)
{
    if (!fila)
        return 0;

    nodo_t *novo_nodo;
    if (!(novo_nodo = malloc(sizeof(nodo_t))))
        return 0;

    novo_nodo->dado = dado;
    novo_nodo->prox = fila->cauda;
    fila->cauda = novo_nodo;
    fila->tamanho++;
    return 1;
}

int dequeue(fila_t *fila, int *dado)
{
    printf("chegou no decui\n\n\n");
    if (fila_vazia(fila))
        return 0;

    *dado = fila->cabeca->dado;

    nodo_t *aux_prox;
    aux_prox = fila->cabeca;

    fila->cabeca = fila->cabeca->prox;
    if (!fila->tamanho)
        fila->cauda = NULL;

    free(aux_prox);

    fila->tamanho--;
    aux_prox = NULL;
    return 1;
}

int fila_tamanho(fila_t *fila)
{
    if (!fila)
        return 0;

    return fila->tamanho;
}

int fila_vazia(fila_t *fila)
{
    if (fila->cabeca && fila->cauda)
        return 0;
    return 1;
}