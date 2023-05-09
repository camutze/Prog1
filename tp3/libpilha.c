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
    pilha_t *aux;
    while ((*pilha!=NULL))
    {
        aux= *pilha;
        //GIT
    }
    

}

int push(pilha_t *pilha, int dado)
{
    return 0;
}

int pop(pilha_t *pilha, int *dado)
{
    return 0;
}
int pilha_topo(pilha_t *pilha, int *dado)
{
    return 0;
}
int pilha_tamanho(pilha_t *pilha)
{
    return pilha->tamanho;
}
int pilha_vazia(pilha_t *pilha)
{
    return !pilha->tamanho;
}