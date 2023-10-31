
#include <stdio.h>
#include <stdlib.h>
#include "set.h"
#include "lista.h"
#include "lef.h"

#define T_INICIO        0
#define T_FIM_DO_MUNDO  525600
#define N_TAMANHO_MUNDO 20000
#define N_HABILIDADES   10
#define N_HEROIS        (N_HABILIDADES * 5)
#define N_BASES         (N_HEROIS / 6)
#define N_MISSOES       (T_FIM_DO_MUNDO / 100)


struct heroi_h
{
    int id;
    int experiencia;
    int paciencia;
    int velocidade;
    int base_id;
    struct set_t *habilidades;
};

struct base_b
{
    int id;
    int lotacao;
    struct set_t *presentes;
    lista_t *lista_espera;
    int local[2];
};

struct missao_m
{
    int id;
    struct set_t *habilidades; //conjunto de habilidades necessárias para cumprir a missão
    int local[2];
};

struct mundo_m
{
    int *herois; //vetor representando todos os heróis
    int *bases; //vetor representando todas as bases
    int *missoes; //vetor representando todas as missões
    int relogio;
    int size_max;// x == y coordenadas máximas do plano cartesiano (as coordenadas mínimas são 0, 0);
    int n_herois;
    int n_bases;
    int n_missoes;
    int n_habil; //número de habilidades distintas possíveis
};

