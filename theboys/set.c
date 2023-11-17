#include <stdlib.h>
#include "set.h"
#include <stdio.h>

struct set_t *set_create(int max)
{
    struct set_t *s;
    if (!max)
        max = 1;

    /*Cria um set com max elementos*/
    if (!(s = malloc(sizeof(struct set_t))))
        return 0;
    /*Cria um array de flags*/
    if (!(s->flag = malloc(max * sizeof(bool))))
        return 0;
    /*Inicializa todas as flags como falsas*/
    for (int i = 0; i < max; i++)
    {
        s->flag[i] = false;
    }

    s->num = 0;
    s->size = max;

    return s;
}

struct set_t *set_destroy(struct set_t *s)
{
    if (!s || !s->flag) // verifica se o set existe
        return 0;
    /*Libera a memoria de cada flag*/
    free(s->flag);
    free(s);

    return 0;
}

int set_add(struct set_t *s, int item)
{
    if (!s || !s->flag)
        return 0;

    /*Adiciona um item ao set*/
    if (item >= s->size)
        return 0;
    /*Se o item ja estiver no set, nao adiciona*/
    if (!s->flag[item])
    {
        /*Adiciona o item e aumenta o numero de elementos*/
        s->flag[item] = true;
        s->num++;
        return 1;
    }
    return 0;
}

int set_del(struct set_t *s, int item)
{
    if (!s || !s->flag)
        return 0;
    /*Remove um item do set*/
    if (item >= s->size)
        return 0;
    if (s->flag[item])
    {
        s->flag[item] = false;
        s->num--; /*Diminui o numero de elementos*/
        return 1;
    }
    return 0;
}

int set_in(struct set_t *s, int item)
{
    if (!s || !s->flag)
        return 0;
    /*Verifica se um item esta no set*/
    if (!s->flag[item]) // verifica se o item esta no set
        return 0;
    return 1;
}

int set_empty(struct set_t *s)
{
    if (!s)
        return 0;
    return s->size; /* retorna o tamanho do set */
}

int set_card(struct set_t *s)
{
    if (!s || !s->flag)
        return -1;
    /*Retorna o numero de elementos do set*/
    return s->num;
}

int set_contains(struct set_t *s1, struct set_t *s2)
{
    if (!s1 || !s1->flag)
        return 0;
    if (!s2 || !s2->flag)
        return 0;

    for (int i = 0; i < s1->size; i++)
    {
        /*se tem s1 E NAO tem s2, nao contem*/
        if (s1->flag[i] && !s2->flag[i])
            return 0;
    }
    return 1;
}

int set_equal(struct set_t *s1, struct set_t *s2)
{
    if (!s1 || !s1->flag)
        return 0;
    if (!s2 || !s2->flag)
        return 0;

    // se o tamanho for diferente, não são iguais
    if (s1->size != s2->size)
        return 0;
    for (int i = 0; i < s1->size; i++)
    {
        // algum elemento for diferente, nao sao iguais
        if (s1->flag[i] != s2->flag[i])
            return 0;
    }
    return 1;
}

int set_union(struct set_t *s1, struct set_t *s2, struct set_t *s3)
{
    if (!s1 || !s1->flag)
        return 0;
    if (!s2 || !s2->flag)
        return 0;

    for (int i = 0; i < s1->size; i++)
    {
        /*se tem s1 OU s2, coloca em s3*/
        if (s1->flag[i] || s2->flag[i])
            set_add(s3, i);
    }
    return 1;
}

int set_intersect(struct set_t *s1, struct set_t *s2, struct set_t *s3)
{
    if (!s1 || !s1->flag)
        return 0;
    if (!s2 || !s2->flag)
        return 0;

    for (int i = 0; i < s1->size; i++)
    {
        /*se tem s1 E s2, coloca em s3*/
        if (s1->flag[i] && s2->flag[i])
            set_add(s3, i);
    }
    return 1;
}

int set_diff(struct set_t *s1, struct set_t *s2, struct set_t *s3)
{
    if (!s1 || !s1->flag)
        return 0;
    if (!s2 || !s2->flag)
        return 0;

    for (int i = 0; i < s1->size; i++)
    {
        // se tem s1 E NAO tem s2, coloca em s3
        if (s1->flag[i] && !s2->flag[i])
            set_add(s3, i);
    }
    return 1;
}

int set_copy(struct set_t *s1, struct set_t *s2)
{
    if (!s1 || !s1->flag)
        return 0;
    if (!s2 || !s2->flag)
        return 0;

    for (int i = 0; i < s1->size; i++)
    {
        // se tem s1, coloca em s2
        if (s1->flag[i])
            set_add(s2, i);
    }
    return 1;
}
int set_size(struct set_t *s)
{
    if (!s || !s->flag)
        return 0;
    return s->size;
}
void set_print(struct set_t *s)
{
    int i;

    if (!s || !s->flag)
        return;

    printf("[ ");
    i = 0;
    while (i < s->size)
    {
        if (s->flag[i])
            printf("%d ", i);
        i++;
    }
    printf("] ");
}