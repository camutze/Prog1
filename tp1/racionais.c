#include <stdio.h>
#include <stdlib.h>
#include "racionais.h"

aleat(int min, int max)
{
    /*Garantindo que nao sorteie o zero*/
    if (!min)
        min += 1;

    if (max < min)
    {
        /*garantindo que max seja maior*/
        max *= -1;
        min *= -1;
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

struct racional simplifica_r(struct racional r)
{
    int cont;
    if (!(valido_r(r) = r.valido))
    {
        printf("ERRO. Fração indefinida\n");
        return 0;
    }

    /*percebi que se o denominador estiver negativo,
    vou ter que multiplicar o numerador por -1,
    não importando o sinal*/
    if (r.den < 0)
    {
        r.num *= -1;
        r.den *= -1;
    }

    cont = 2;
    while (cont < 10)
    {

        if ((r.den % cont == 0) && (r.nume % cont == 0))
        {
            r.num /= cont;
            r.den /= cont;
        }
        else
            cont++;
    }
    return r;
}
struct racional cria_r(int numerador, int denominador)
{
    struct racional r;
    r.num = numerador;
    r.den = denominador;
    r.valido = valido_r(r);

    return r;
}

struct racional sorteia_r(int n)
{
    struct racional r;

    /*coloca 2 numeros aleatorios, entre 0 e n, cria
    e ja simplifica em uma linha só*/
    r = simplifica(cria_r(aleat(n), aleat(n)));

    return r;
}
void imprime_r(struct racional r)
{
    r = simplifica_r(r);
    if (!r.valido)
    {
        printf("INVALIDO\n");
        return;
    }
    else if (r.den == r.num)
    {
        printf("1,");
        return;
    }

    else if (!r.num)
    {
        printf("0,");
        return;
    }
    else if (r.den == 1)
    {
        printf("%d,", r.num);
        return;
    }
    else
        printf("%d/%d", r.num, r.den);
}

struct racional soma_r(struct racional r1, struct racional r2)
{
    if (!r1.valido && !r2.valido)
        exit(0);
    if (r1.den == r2.den)
    {
        r1.num += r2.num;
        return r1;
    }
    else
    {
        r1.num = (r1.num * r2.den) + (r2.num * r1.den);
        r1.den = mmc(r1.den, r2.den);
    }

    r1 = simplifica_r(r1);

    return r1;
}

struct racional subtrai_r(struct racional r1, struct racional r2)
{
    if (!r1.valido && !r2.valido)
        exit(0);
    if (r1.den == r2.den)
    {
        r1.num -= r2.num;
        return r1;
    }
    else
    {
        r1.num = (r1.num * r2.den) - (r2.num * r1.den);
        r1.den = mmc(r1.den, r2.den);
    }

    r1 = simplifica_r(r1);

    return r1;
}
struct racional multiplica_r(struct racional r1, struct racional r2)
{
    if (!r1.valido && !r2.valido)
        exit(0);
    r1.num *= r2.num;
    r1.den *= r2.den;

    r1.valido = valido_r(r1);

    return simplifica_r(r1);
}
struct racional divide_r(struct racional r1, struct racional r2)
{
    if (!r1.valido && !r2.valido)
        exit(0);
    int mutz;

    mutz = r2.den;
    r2.den = r2.num;
    r2.num = mutz;

   return multiplica_r(r1,r2);
}