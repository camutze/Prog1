#include <stdio.h>
#include <stdlib.h>
#include "racionais.h"

long int mdc(int a, int b)
{
    if (b == 0)
        return a;
    return mdc(b, a % b);
}

long int mmc(int a, int b)
{
    return ((a * b) / mdc(a, b));
}

struct racional *cria_r(long int numerador, long int denominador)
{
    struct racional *r;

    if (!(r = malloc(sizeof(struct racional))))
        return NULL;

    r->num = numerador;
    r->den = denominador;

    return r;
}

void destroi_r(struct racional *r)
{
    if (!r)
        return;
    free(r);
    r = NULL;
}

long int numerador_r(struct racional *r)
{
    if (!r)
        return 0;
    return r->num;
}

long int denominador_r(struct racional *r)
{
    if (!r)
        return 0;
    return r->den;
}

int valido_r(struct racional *r)
{
    if (!r)
        return 0;
    return r->den;
}

void imprime_r(struct racional *r)
{

    // // o racional deve estar na forma simplificada;
    // se o racional for negativo, o sinal deve ser impresso antes do numero;
    //  - se numerador e denominador forem negativos, o racional eh positivo.
    if (!r)
    {
        printf("NULO");
        return;
    }

    if (!(valido_r(r)))
    {
        printf("INVALIDO");
        return;
    }

    if (!r->num)
    {
        printf("0");
        return;
    }

    if (r->den == 1)
    {
        printf("%d", r->num);
        return;
    }

    if (r->den == r->num)
    {
        printf("1");
        return;
    }
}

int compara_r(struct racional *r1, struct racional *r2)
{
    if (!r1 || !r2)
        return -2;

    /*deixa os denominadores equivalentes, e comparo somente
    os numeradores*/
    long int mmc_var = mmc(r1->den, r2->den);
    long int num1 = r1->num * (mmc_var / r1->den);
    long int num2 = r2->num * (mmc_var / r2->den);

    if (num1 < num2)
    {
        return -1; /*r1 < r2*/
    }
    if (num1 > num2)
        return 1; /*r1 > r2*/
    return 0;     /* r1 == r2.*/
}

int simplifica_r(struct racional *r)
{
    if (!r || !valido_r(r))
        return 0;

    int div_comum;
    div_comum = mdc(r->num, r->den);
    r->num /= div_comum;
    r->den /= div_comum;

    if (r->den < 0)
    {
        r->num *= -1;
        r->den *= -1;
    }
    return 1;
}
int soma_r(struct racional *r1, struct racional *r2, struct racional *r3)
{
    if (!r1 || !r2 || !r3)
        return 0;
    if (!valido_r(r1) || !valido_r(r2))
        return 0;

    if (r1->den = r2->den)
    {
        r3->num = r1->num + r2->num;
        r3->den = r1->den;
        return 1;
    }

    r3->den = mmc(r1->num, r2->den);
    r3->num = (r3->den / r1->den) * r1->num;
    r3->num += (r3->den / r2->den) * r2->num;
    return 1;
}
int subtrai_r(struct racional *r1, struct racional *r2, struct racional *r3)
{
    if (!r1 || !r2 || !r3)
        return 0;
    if (!valido_r(r1) || !valido_r(r2))
        return 0;

    if (r1->den = r2->den)
    {
        r3->num = r1->num - r2->num;
        r3->den = r1->den;
        simplifica_r(r3);
        return 1;
    }

    r3->den = mmc(r1->num, r2->den);
    r3->num = (r3->den / r1->den) * r1->num;
    r3->num -= (r3->den / r2->den) * r2->num;
    simplifica_r(r3);

    return 1;
}
int multiplica_r(struct racional *r1, struct racional *r2, struct racional *r3)
{
    if (!r1 || !r2 || !r3)
        return 0;
    if (!valido_r(r1) || !valido_r(r2))
        return 0;
    r3->num = r1->num * r2->num;
    r3->den = r1->den * r2->den;
    return 1;
}
void troca_var(struct racional *r)
{
    int aux;
    aux = r->den;
    r->den = r->num;
    r->num = aux;
}
int divide_r(struct racional *r1, struct racional *r2, struct racional *r3)
{
    if (!r1 || !r2 || !r3)
        return 0;
    if (!valido_r(r1) || !valido_r(r2))
        return 0;

    troca_var(&r2);

    if (!multiplica_r(r1, r2, r3))
        return 0;
    return 1;
}
