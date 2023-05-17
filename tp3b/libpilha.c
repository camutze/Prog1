#include "libpilha.h"
#include <stdlib.h>

pilha_t *pilha_cria()
{
    pilha_t *nova;
    if (!(nova = malloc(sizeof(pilha_t))))
        return NULL;

    nova->tamanho = 0;
    nova->topo = NULL;
    return nova;
}

void pilha_destroi(pilha_t **pilha)
{
    if (pilha && *pilha) /* se ambos não forem NULL*/
    {
        nodo_t *atual = (*pilha)->topo;
        while (atual)
        {
            nodo_t *proximo = atual->prox;
            free(atual);
            atual = proximo;
        }
        free(*pilha);
        *pilha = NULL;
    }
}

int push(pilha_t *pilha, int dado)
{
    if (!pilha)
        return 0;

    nodo_t *novo_nodo;
    if (!(novo_nodo = malloc(sizeof(nodo_t))))
        return 0;

    novo_nodo->dado = dado;
    novo_nodo->prox = pilha->topo;
    pilha->topo = novo_nodo;
    pilha->tamanho++;
    return 1;
}

int pop(pilha_t *pilha, int *dado)
{
    if (!pilha || !pilha->topo)
        return 0;

    nodo_t *topo = pilha->topo;
    *dado = topo->dado;
    pilha->topo = topo->prox;
    free(topo);
    pilha->tamanho--;
    return 1;
}
int pilha_topo(pilha_t *pilha, int *dado)
{
    if (!pilha || !pilha->topo)
        return 0;

    *dado = pilha->topo->dado;
    return 1;
}
int pilha_tamanho(pilha_t *pilha)
{
    if (!pilha)
        return 0;

    return pilha->tamanho;
}
int pilha_vazia(pilha_t *pilha)
{
    return !pilha->tamanho;
}