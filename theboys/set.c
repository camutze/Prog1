#include <stdlib.h>

#include "set.h"

struct set_t *set_create(int max)
{
    struct set_t *s;
    if (!(s = malloc(sizeof(struct set_t))))
        return NULL;
    if (!(s->flag = malloc(sizeof(bool) * max)))
        return NULL;
    s->size = max;
    s->num = 0;
    return s;
}

struct set_t *set_destroy(struct set_t *s)
{
    if (!s)
        return NULL;
    free(s->flag);
    free(s);
    return NULL;
}

int set_add (struct set_t *s, int item)
{
    if (!s)
        return 0;
    if (s->num == s->size)
        return 0;
    s->flag[item] = true;
    s->num++;
    return 1;
}