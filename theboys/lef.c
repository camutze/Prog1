#include <stdlib.h>
#include "lef.h"
#include <stdio.h>
struct evento_t *cria_evento(int tempo, int tipo, int dado1, int dado2)
{
    struct evento_t *e;

    if (!(e = malloc(sizeof(struct evento_t))))
        return NULL;

    e->tempo = tempo;
    e->tipo = tipo;
    e->dado1 = dado1;
    e->dado2 = dado2;

    return e;
}

struct evento_t *destroi_evento(struct evento_t *e)
{
    if (!e)
        return NULL;

    free(e);

    return NULL;
}

struct lef_t *cria_lef()
{
    struct lef_t *l;

    if (!(l = malloc(sizeof(struct lef_t))))
        return NULL;

    l->primeiro = NULL;

    return l;
}

struct lef_t *destroi_lef(struct lef_t *l)
{
    struct nodo_lef_t *aux;

    if (!l)
        return NULL;

    aux = l->primeiro;

    while (aux)
    {
        l->primeiro = aux->prox;
        destroi_evento(aux->evento);
        free(aux);
        aux = l->primeiro;
    }

    free(l);

    return NULL;
}

int insere_lef(struct lef_t *l, struct evento_t *e)
{

    struct nodo_lef_t *aux, *ant;
    struct nodo_lef_t *novo;

    if (!l || !e)
        return 0;

    if (!(novo = malloc(sizeof(struct nodo_lef_t))))
        return 0;

    aux = l->primeiro;
    ant = NULL;
    while (aux && aux->evento->tempo <= e->tempo)
    {
        // se o tempo for igual, respeita a politica FIFO
        ant = aux;
        aux = aux->prox;
    }

    novo->evento = e;
    novo->prox = aux;

    if (!ant)
        l->primeiro = novo;
    else
        ant->prox = novo;

    return 1;
}

struct evento_t *retira_lef(struct lef_t *l)
{
    struct nodo_lef_t *aux;
    struct evento_t *e;

    if (!l)
        return NULL;

    if (!l->primeiro)
        return NULL;

    aux = l->primeiro;
    l->primeiro = aux->prox;

    e = aux->evento;
    free(aux);

    return e;
}

int vazia_lef(struct lef_t *l)
{
    if (!l) // falha
        return -1;

    if (!l->primeiro) // vazia
        return 1;

    return 0; // nao esta vazia
}

void imprime_lef(struct lef_t *l)
{
    struct nodo_lef_t *aux;
    int total = 0;

    if (!l)
        return;

    aux = l->primeiro;

    while (aux)
    {
        printf("%d %d %d %d\n", aux->evento->tempo,
               aux->evento->tipo, aux->evento->dado1, aux->evento->dado2);
        total++;
        aux = aux->prox;
    }

    printf("total %d eventos\n", total);
}