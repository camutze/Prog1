#include <stdlib.h>
#include <stdio.h>

#include "lef.h"

struct evento_t *cria_evento(int tempo, int tipo, int dado1, int dado2)
{
    struct evento_t *e;
    /*Aloca memoria para o evento*/
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
    /*Inicializa a lista*/
    l->primeiro = NULL;

    return l;
}

struct lef_t *destroi_lef(struct lef_t *l)
{
    struct nodo_lef_t *aux;

    if (!l)
        return NULL;
    aux = l->primeiro;

    /*Liberta a memoria de todos os nodos da lista*/
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
        /*se o tempo for igual, insere na fila*/
        ant = aux;
        aux = aux->prox;
    }

    novo->evento = e;
    novo->prox = aux;
    /*primeiro elemento*/
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

    /*se a lista estiver vazia, retorna NULL*/
    if (!l->primeiro)
        return NULL;
    /*retira o primeiro elemento da lista*/
    aux = l->primeiro;
    l->primeiro = aux->prox;

    e = aux->evento;
    free (aux) ;

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
    /*percorre a lista e imprime todos os elementos*/
    printf("LEF:\n");
    while (aux)
    {
        printf("\ttempo %d tipo %d d1 %d d2 %d\n", aux->evento->tempo,
               aux->evento->tipo, aux->evento->dado1, aux->evento->dado2);
        total++;
        aux = aux->prox;
    }

    printf("\tTotal %d eventos\n", total);
}
