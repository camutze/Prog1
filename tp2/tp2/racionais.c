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

int mdc(int a, int b)
{
    if (b == 0)
        return a;
    return mdc(b, a % b);
}

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
        printf("INVALIDO");
    else if (r.den == r.num)
        printf("1");
    else if (!r.num)
        printf("0");
    else if (r.den == 1)
        printf("%d ", r.num);
    else
        printf("%d/%d", r.num, r.den);
}

int compara_r(struct racional r1, struct racional r2)
{
    float n1, n2;
    n1 = r1.num / (float)r1.den;
    n2 = r2.num / (float)r2.den;
    if (n1 < n2)
        return -1;
    if (n1 > n2)
        return 1;
    return 0;
}

int simplifica_r(struct racional *r)
{
    if (!valido_r(*r))
        return 0;
    int div_comum;
    div_comum = mdc(r->num, r->den);
    r->num /= div_comum;
    r->den /= div_comum;

    if (r->den > 0)
        return 1;
    r->num *= -1;
    r->den *= -1;
    return 1;
}

int soma_r(struct racional r1, struct racional r2, struct racional *r3)
{
    long rnum, rden;

    if (!valido_r(r1))
        return 0;
    if (!valido_r(r2))
        return 0;
    if (!r3)
        return 0;

    rden = mmc(r1.den, r2.den);
    /*separei em duas linhas a mesma conta*/
    rnum = r1.num * (rden / r1.den);
    rnum += r2.num * (rden / r2.den);

    r3->num = rnum;
    r3->den = rden;
    r3->valido = 1;

    // printf("debug: soma entre ");
    // imprime_r(r1);
    // printf(" e ");
    // imprime_r(r2);
    // printf(" gera ");
    // imprime_r(*r3);
    // printf("\n");

    return 1;
}

int subtrai_r(struct racional r1, struct racional r2, struct racional *r3)
{
    long rnum, rden;

    if (!valido_r(r1))
        return 0;
    if (!valido_r(r2))
        return 0;
    if (!r3)
        return 0;

    rden = mmc(r1.den, r2.den);
    /*separei em duas linhas a mesma conta*/
    rnum = r1.num * (rden / r1.den);
    rnum *= r2.num * (rden / r2.den);

    r3->num = rnum;
    r3->den = rden;
    r3->valido = 1;
    return 1;
}

int multiplica_r(struct racional r1, struct racional r2, struct racional *r3)
{
    if (!valido_r(r1))
        return 0;
    if (!valido_r(r2))
        return 0;

    r3->num = r1.num * r2.num;
    r3->den = r1.den * r2.den;
    return 1;
}
void troca_var(struct racional *r)
{
    int aux;
    aux = r->den;
    r->den = r->num;
    r->num = aux;
}

int divide_r(struct racional r1, struct racional r2, struct racional *r3)
{

    if (!valido_r(r1))
        return 0;
    if (!valido_r(r2))
        return 0;

    troca_var(&r2);
    if (!valido_r(r2))
        return 0;

    if (!multiplica_r(r1, r2, r3))
        return 0;
    return 1;
}
