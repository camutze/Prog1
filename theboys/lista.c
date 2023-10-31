#include <stdlib.h>
#include <stdio.h>
#include "lista.h"

lista_t *lista_cria()
{
    lista_t *lista;
    if (!(lista = malloc(sizeof(lista_t))))
        return NULL;

    lista->head = NULL;
    lista->tail = NULL;
    lista->size = 0;
    return lista;
}

lnode_t *cria_nodo(int elem)
{
    lnode_t *novo;
    if (!(novo = malloc(sizeof(lnode_t))))
        return NULL;

    novo->next = NULL;
    novo->prev = NULL;
    novo->val = elem;
    return novo;
}

lista_t *lista_destroi(lista_t *lst)
{
    lnode_t *aux;

    if (!lst)
        return NULL;

    while (lst->head)
    {
        aux = lst->head;
        lst->head = lst->head->next;
        free(aux);
    }

    free(lst);
    return NULL;
}

int lista_insere(lista_t *lst, int elem, int pos)
{
    lnode_t *aux, *novo;
    int i;
    if (!lst)
        return -1;

    if (!(novo = cria_nodo(elem)))
        return -1;

    /* inserção no início lista vazia*/
    if (!lst->head)
    {
        lst->head = novo;
        lst->tail = novo;
        lst->size++;
        return lst->size;
    }
    /* inserindo também no início, mas a lista não está vazia*/
    if (!pos)
    {
        novo->next = lst->head;
        lst->head->prev = novo;
        lst->head = novo;
        lst->size++;
        return lst->size;
    }
    /* inserção no final*/
    if (pos == -1 || pos >= lst->size)
    {
        novo->prev = lst->tail;
        lst->tail->next = novo;
        lst->tail = novo;
        lst->size++;
        return lst->size;
    }
    /* inserção no meio*/
    i = 0;
    aux = lst->head;
    while (i < pos)
    {
        aux = aux->next;
        i++;
    }

    aux->prev->next = novo;
    novo->prev = aux->prev;
    novo->next = aux;
    aux->prev = novo;
    lst->size++;
    return lst->size;
}

int lista_retira(lista_t *lst, int *elem, int pos)
{
    lnode_t *aux;
    int i;

    if (!lst)
        return -1;

    if (!lst->head)
        return -1;

    if (pos > lst->size)
        return -1;

    /*retirada do início*/
    if (!pos)
    {
        aux = lst->head;

        /*se a lista tiver apenas um elemento*/
        if (lst->size == 1)
        {
            lst->head = NULL;
            lst->tail = NULL;
        }
        else
        {
            lst->head = lst->head->next;
            lst->head->prev = NULL;
        }
        *elem = aux->val;
        free(aux);
        lst->size--;
        return lst->size;
    }
    /* retirada do final*/
    if (pos == -1)
    {
        aux = lst->tail;

        /* se a lista tiver apenas um elemento*/
        if (lst->size == 1)
        {
            lst->head = NULL;
            lst->tail = NULL;
        }
        else
        {
            lst->tail = lst->tail->prev;
            lst->tail->next = NULL;
        }
        *elem = aux->val;
        free(aux);
        lst->size--;
        return lst->size;
    }

    /*retirada do meio*/
    i = 0;
    aux = lst->head;
    /* quando chegar aqui, eu ja garanti que
     pos é um valor válido para a lista
     sem acessar valor fora da lista*/
    while (i < pos)
    {
        aux = aux->next;
        i++;
    }

    aux->prev->next = aux->next;
    aux->next->prev = aux->prev;
    *elem = aux->val;
    free(aux);
    lst->size--;
    return lst->size;
}

int lista_consulta(lista_t *lst, int *elem, int pos)
{
    lnode_t *aux;
    int i;

    if (!lst)
        return -1;

    if (!lst->head)
        return -1;

    if (pos > lst->size)
        return -1;

    /*consulta no início*/
    if (!pos)
    {
        *elem = lst->head->val;
        return lst->size;
    }

    /* consulta no final*/
    if (pos == -1)
    {
        *elem = lst->tail->val;
        return lst->size;
    }

    /* consulta no meio*/
    i = 0;
    aux = lst->head;
    while (i < pos)
    {
        aux = aux->next;
        i++;
    }
    *elem = aux->val;
    return lst->size;
}

int lista_procura(lista_t *lst, int elem)
{
    lnode_t *aux;
    int i;

    if (!lst)
        return -1;

    if (!lst->head)
        return -1;
    /*Caminha até o elemento,
    quando encontrar retorna sua posicao*/
    aux = lst->head;
    i = 0;
    while (i <= lst->size - 1)
    {
        if (aux->val == elem)
        {
            return i;
        }
        aux = aux->next;
        i++;
    }
    return -1;
}

int lista_vazia(lista_t *lst)
{
    if (!lst)
        return -1;

    if (!lst->head)
        return 1;
    return 0;
}

int lista_tamanho(lista_t *lst)
{
    if (!lst)
        return -1;
    return lst->size;
}

void lista_imprime(char *nome, lista_t *lst)
{
    lnode_t *aux;

    if (!lst)
        return;
    /*se a lista for vazi*/
    if (!lst->head)
    {
        printf("%s: [ ] (%d elementos)\n", nome, lista_tamanho(lst));
        return;
    }

    printf("%s: [", nome);
    aux = lst->head;

    while (aux)
    {
        printf(" %d", aux->val);
        if (aux->next)
            printf(" ");
        aux = aux->next;
    }

    printf("] (%d elementos)\n", lista_tamanho(lst));
}