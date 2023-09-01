#include <stdio.h>
#include <stdlib.h>
#include "racionais.h"

int aleat(int max)
{
    int min;
    if (max > 0)
        min = max * (-1);
    else
    {
        min = max;
        max *= (-1);
    }

    return min + (rand() % (max - min + 1));
}

/* Maximo Divisor Comum entre a e b      */
/* calcula o mdc pelo metodo de Euclides */
int mdc(int a, int b)
{
    if (b == 0)
        return a;
    return mdc(b, a % b);
}

/* Minimo Multiplo Comum entre a e b */
/* mmc = (a * b) / mdc (a, b)        */
int mmc(int a, int b)
{
    return ((a * b) / mdc(a, b));
}

struct racional cria_r(int numerador, int denominador)
{
    struct racional novo;
    novo.num = numerador;
    novo.den = denominador;

    novo.valido = valido_r(novo);

    return novo;
}

struct racional sorteia_r(int max)
{
    struct racional r;
    int denominador, numerador;

    numerador = aleat(max);
    denominador = aleat(max);

    r = cria_r(numerador, denominador);
    r.valido = simplifica_r(&r);
    return r;
}

int numerador_r(struct racional r)
{
    return r.num;
}

int denominador_r(struct racional r)
{
    return r.den;
}

int valido_r(struct racional r)
{
    return r.den;
}

void imprime_r(struct racional r)
{
    if (!valido_r(r))
        printf("INVALIDO ");
    else if (r.den == r.num)
        printf("1 ");
    else if (!r.num)
        printf("0 ");
    else if (r.den == 1)
        printf("%d ", r.num);
    else
        printf("%d/%d ", r.num, r.den);
}

int compara_r(struct racional r1, struct racional r2)
{

    float n1, n2;
    n1 = numerador_r(r1) / (float)denominador_r(r1);
    n2 = numerador_r(r2) / (float)denominador_r(r2);
    if (n1 < n2)
    {
        return -1;
    }
    else if (n1 > n2)
    {
        return 1;
    }
    return 0;
}

int simplifica_r(struct racional *r)
{
    if (valido_r(*r))
    {
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

    return 0;
}

int soma_r(struct racional r1, struct racional r2, struct racional *r3)
{
    if (valido_r(r1) && valido_r((r2)))
    {
        if (denominador_r(r1) == denominador_r(r2))
        {
            r3->num = numerador_r(r1) + numerador_r(r2);
        }
        else
        {
            r3->den = mmc(denominador_r(r1), denominador_r(r2));
            /*separei em duas linhas a mesma conta*/
            r3->num = (r3->den / denominador_r(r1)) * numerador_r(r1);
            r3->num += (r3->den / denominador_r(r2)) * numerador_r(r2);
        }

        return 1;
    }
    return 0;
}

int subtrai_r(struct racional r1, struct racional r2, struct racional *r3)
{
    if (valido_r(r1) && valido_r((r2)))
    {
        if (denominador_r(r1) == denominador_r(r2))
        {
            /*so muda o sinal*/
            r3->num = numerador_r(r1) - numerador_r(r2);
        }
        else
        {
            r3->den = mmc(denominador_r(r1), denominador_r(r2));
            r3->num = (r3->den / denominador_r(r1)) * numerador_r(r1);
            r3->num -= (r3->den / denominador_r(r2)) * numerador_r(r2);
        }

        return 1;
    }
    return 0;
}

int multiplica_r(struct racional r1, struct racional r2, struct racional *r3)
{
    if (valido_r(r1) && valido_r((r2)))
    {
        r3->num = numerador_r(r1) * numerador_r(r2);
        r3->den = denominador_r(r1) * numerador_r(r2);
        return 1;
    }
    return 0;
}
void troca_var(struct racional *r)
{
    int mutz;
    mutz = denominador_r(*r);
    r->den = numerador_r(*r);
    r->num = mutz;
}

int divide_r(struct racional r1, struct racional r2, struct racional *r3)
{
    if (valido_r(r1) && valido_r((r2)))
    {
        troca_var(&r2);
        if (!valido_r(r2))
            return 0;

        if (!multiplica_r(r1, r2, r3))
            return 0;
        return 1;
    }
    return 0;
}
