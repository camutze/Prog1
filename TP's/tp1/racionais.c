#include <stdio.h>
#include <stdlib.h>
#include "racionais.h"

int aleat(int min, int max)
{
    if (max < min)
    {
        /*garantindo que max seja maior*/
        int troca = max;
        max = min;
        min = troca;
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
    if (valido_r(r))
    {
        int divisor_comum;
        divisor_comum = mdc(r.num, r.den);
        r.num /= divisor_comum;
        r.den /= divisor_comum;

        /*perceba que se o denominador estiver negativo,
        vou ter que multiplicar o numerador por -1,
        não importando o sinal do numerador*/
        if (r.den < 0)
        {
            r.num *= -1;
            r.den *= -1;
        }
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
    int denominador, numerador;

    numerador = aleat(0, n);
    denominador = aleat(0, n);

    r = cria_r(numerador, denominador);

    return r;
}
void imprime_r(struct racional r)
{
    r = simplifica_r(r);
    if (!valido_r(r))
    {
        printf("INVALIDO ");
        return;
    }
    else if (r.den == r.num)
    {
        printf("1 ");
        return;
    }

    else if (!r.num)
    {
        printf("0 ");
        return;
    }
    else if (r.den == 1)
    {
        printf("%d ", r.num);
        return;
    }
    else
        printf("%d/%d ", r.num, r.den);
}
int valido_r(struct racional r)
{
    if (!r.den)
        return 0;
    return 1;
}

struct racional soma_r(struct racional r1, struct racional r2)
{
    if (valido_r(r1) && valido_r((r2)))
    {
        if (r1.den == r2.den)
        {
            /*se os denominadores forem iguais, é só fazer a soma
            dos numeradores*/
            r1.num += r2.num;
        }
        else
        {
            /*caso contrario, calcula o mmc dos denominadores,
            divide pelo denominador de r1 vezes o numerador de r1
            mais o resultado de
            mmc dividido pelo numerador de r2 vezes o numerador de r2*/
            int mmc_var = mmc(r1.den, r2.den);
            r1.num = ((mmc_var / r1.den) * r1.num) + ((mmc_var / r2.den) * r2.num);
            r1.den = mmc_var;
        }

        return r1;
    }
    /*aterrando, garantindo que o retorno seja invalido*/
    r1.valido = 0;
    r1.den = 0;
    return r1;
}
struct racional subtrai_r(struct racional r1, struct racional r2)
{
    if (valido_r(r1) && valido_r((r2)))
    {
        if (r1.den == r2.den)
        {
            r1.num -= r2.num;
            return r1;
        }
        else
        {
            /*exceto o sinal, mesma coisa que a soma*/
            int mmc_var = mmc(r1.den, r2.den);
            r1.num = ((mmc_var / r1.den) * r1.num) - ((mmc_var / r2.den) * r2.num);
            r1.den = mmc_var;
        }

        return r1;
    }
    r1.valido = 0;
    r1.den = 0;
    return r1;
}
struct racional multiplica_r(struct racional r1, struct racional r2)
{
    if (valido_r(r1) && valido_r((r2)))
    {
        r1.num *= r2.num;
        r1.den *= r2.den;

        r1.valido = valido_r(r1);

        return r1;
    }

    r1.valido = 0;
    r1.den = 0;
    return r1;
}
struct racional divide_r(struct racional r1, struct racional r2)
{

    if (valido_r(r1) && valido_r((r2)))
    {
        int mutz;
        mutz = r2.den;
        r2.den = r2.num;
        r2.num = mutz;

        r1 = multiplica_r(r1, r2);

        if (!r1.den)
        {
            r1.valido = 0;
            r1.den = 0;
            return r1;
        }

        r1.valido = 1;
        return r1;
    }
    r1.valido = 0;
    r1.den = 0;
    return r1;
}