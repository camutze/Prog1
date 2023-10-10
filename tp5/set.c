#include <stdlib.h>
#include <stdio.h>
#include "set.h"

struct set_t *set_create(int max)
{
    struct set_t *s;

    if (!(s = malloc(sizeof(struct set_t))))
        return 0;

    if (!(s->flag = malloc(max * sizeof(bool))))
        return 0;

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

    free(s->flag);
    free(s);

    return NULL;
}

int set_add(struct set_t *s, int item)
{
    if (item >= s->size)
        return 0;
    if (!s->flag[item])
    {
        s->flag[item] = true;
        s->size++;
        return 1;
    }
    return 0;
}

int set_del(struct set_t *s, int item)
{
    if (item >= s->size)
        return 0;
    if (s->flag[item])
    {
        s->flag[item] = false;
        s->size--;
        return 1;
    }
    return 0;
}

int set_in(struct set_t *s, int item)
{
    if (item >= s->size)
        return 0;
    return 1;
}

int set_emply(struct set_t *s)
{
    return !s->size ? 0 : 1;
}

int set_card (struct set_t *s)
{
    return s->size;
}

int set_contains (struct set_t *s1, struct set_t *s2)
{
    for (int i = 0; i < s1->size; i++)
    {
        if (s1->flag[i] && !s2->flag[i])
            return 0;
    }
    return 1;
}

int set_equal (struct set_t *s1, struct set_t *s2)
{
    /*se o tamanho for diferente, não são iguais*/
    if (s1->size != s2->size)
        return 0;
    for (int i = 0; i < s1->size; i++)
    {   /*algum elemento for diferente, nao sao iguais*/
        if (s1->flag[i] != s2->flag[i])
            return 0;
    }
    return 1;

}

int set_union (struct set_t *s1, struct set_t *s2, struct set_t *s3)
{
    for(int i = 0; i < s1->size; i++)
    {
        if (s1->flag[i] || s2->flag[i])
            set_add(s3, i);
    }
    return 1;

}

int set_intersect (struct set_t *s1, struct set_t *s2, struct set_t *s3)
{
    for(int i = 0; i < s1->size; i++)
    {
        if (s1->flag[i] && s2->flag[i])
            set_add(s3, i);
    }
    return 1;
}

void set_print (struct set_t *s)
{
    printf("[ ");
    for (int i = 0; i < s->size; i++)
    {
        if (s->flag[i])
            printf("%d ", i);
    }
    printf(" ]\n");

}