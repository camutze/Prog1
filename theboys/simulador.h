
#include <stdio.h>
#include <stdlib.h>
#include "set.h"
#include "lista.h"
#include "lef.h"

#define T_INICIO 0
#define T_FIM_DO_MUNDO 525600
#define N_TAMANHO_MUNDO 20000
#define N_HABILIDADES 10


struct heroi_h
{
    int id;
    int experiencia;
    int paciencia;
    int velocidade;
    int base_id;
    struct set_t *habil;
};

struct pontos_p
{
    unsigned int x;
    unsigned int y;
};

struct base_b
{
    int id;
    int lotacao;
    struct set_t *presentes;
    lista_t *lista_espera;
    struct pontos_p local;
};

struct missao_m
{
    int id;
    struct set_t *habil; // conjunto de habilidades necessárias para cumprir a missão
    struct pontos_p local;
};

struct mundo_m
{
    struct heroi_t *heroi;   // vetor representando todos os heróis
    struct base_t  *base;     // vetor representando todas as bases
    struct missao_t *missao; // vetor representando todas as missões
    int relogio;
    int size_max; // x == y coordenadas máximas do plano cartesiano (as coordenadas mínimas são 0, 0);
    int n_herois;
    int n_bases;
    int n_missoes;
    int n_habil; // número de habilidades distintas possíveis
};

int gera_aleat(int min, int max);

struct heroi_t *cria_um_heroi(int id);

struct heroi_t *destroi_um_heroi(struct heroi_h *heroi);

struct base_t *cria_base(int id);

struct base_t *destroi_base(struct base_b *base);

struct missao_t *cria_missao(int id);

struct missao_t *destroi_missao(struct missao_m *missao);

struct mundo_t *cria_mundo();

struct mundo_t *destroi_mundo(struct mundo_m *mundo);
