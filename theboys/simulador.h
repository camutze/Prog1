
#include <stdio.h>
#include <stdlib.h>
#include "set.h"
#include "lista.h"
#include "lef.h"

#define TAM_MUNDO 20000
#define FIM_MUNDO 525600
#define HABILIDADES 10
#define HEROIS (HABILIDADES * 5)
#define BASES (HEROIS / 6)
#define MISSOES (FIM_MUNDO / 100)

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
    struct lista_t *lista_espera;
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
    int n_herois;
    int *herois; //vetor representando todos os heróis
    int n_bases;
    int *bases; //vetor representando todas as bases
    int n_missoes;
    int *missoes; //vetor representando todas as missões
    int n_habilidades; //número de habilidades distintas possíveis
    int tamanho_mundo[2];// coordenadas máximas do plano cartesiano (as coordenadas mínimas são 0, 0);
    int relogio;
};

