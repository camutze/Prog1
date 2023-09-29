#include <stdlib.h>
#include <liblista.h>

lista_t *lista_cria()
{
    lista_t *l;
    if (!(l = malloc(sizeof(lista_t))))
        return NULL;

    l->head = NULL;
    l->tail = NULL;
    l->size = 0;
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

    aux = lst->head;
    while (aux)
    {
        lst->head = lst->head->next;
        free(aux);
        aux = lst->head;
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

    // inserção no início
    if (!lst->head)
    {
        lst->head = novo;
        lst->tail = novo;
        lst->size++;
        return lst->size;
    }
    // garantindo que a posição esteja dentro da lista
    // e se for, insere no final
    if (pos >= lst->size)
    {
        novo->prev = lst->tail;
        novo->next = lst->head;

        lst->tail->next = novo;
        lst->tail = novo;
        lst->head->prev = novo;
        lst->size++;
        return lst->size;
    }
    // inserção no meio
    i = 0;
    while (i < pos)
    {
        aux = aux->next;
        i++;
    }
    novo->next = aux->next;
    novo->prev = aux;

    aux->next = novo;
    novo->next->prev = novo;
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

    // retirada do início
    if (!pos)
    {
        aux = lst->head;
        lst->head = lst->head->next;
        lst->head->prev = lst->tail;
        lst->tail->next = lst->head;
        *elem = aux->val;
        free(aux);
        lst->size--;
        return lst->size;
    }
    // retirada do final
    if (pos == lst->size - 1)
    {
        aux = lst->tail;
        lst->tail = lst->tail->prev;
        lst->tail->next = lst->head;
        lst->head->prev = lst->tail;
        *elem = aux->val;
        free(aux);
        lst->size--;
        return lst->size;
    }
    // retirada do meio
    i = 0;
    aux = lst->head;
    while (i < pos)
    {
        aux = aux->next;
        i++;
    }
    // ponteiro que aponta para aux, aponta para o próximo de aux
    aux->prev->next = aux->next;
    // ponteiro que aponta para o anterior de aux, aponta para o anterior de aux
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

    // consulta no início
    if (!pos)
    {
        *elem = lst->head->val;
        return lst->size;
    }

    // consulta no final
    if (pos == lst->size - 1)
    {
        *elem = lst->tail->val;
    }
    // consulta no meio
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
    while (i < lst)
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

int lista_tamanho (lista_t* lst)
{
    if (!lst)
        return -1;
    return lst->size;
}
void lista_imprime (char *nome, lista_t* lst)
{
    lnode_t *aux;
    int i;

    if (!lst)
        return -1;
    if(!lst->head)
        return;
    printf("nome: [ ");
    while ()
    {
        /* code */
    }
    
}