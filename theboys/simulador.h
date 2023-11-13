#ifndef _SIMULADOR_H
#define _SIMULADOR_H

#include "set.h"
#include "lista.h"
#include "lef.h"

#define T_INICIO 0
#define T_FIM_DO_MUNDO 5000//525600
#define N_TAMANHO_MUNDO 2000 //20000
#define N_HABILIDADES 10
#define TEMPO_INICIAL 200 // 4320 = 60*24*3 = 3 dias
/*
    mundo->n_missoes = T_FIM_DO_MUNDO / 100;
    mundo->n_herois = N_HABILIDADES * 5;
    mundo->n_bases = mundo->n_herois / 6;
*/

struct heroi_t
{
    int id;
    int experiencia;
    int paciencia;
    int velocidade;
    int base_id;
    struct set_t *habil;
};

struct pontos_t
{
    unsigned int x;
    unsigned int y;
};

struct base_t
{
    int id;
    int lotacao;
    struct set_t *presentes;
    lista_t *lista_espera;
    struct pontos_t local;
};

struct missao_t
{
    int id;
    struct set_t *habil;   // conjunto de habilidades necessárias para cumprir a missão
    short realizada;         // se foi comcluida == 0, 1 caso contrario
    int tentativas;        // número de tentativas de cumprir a missão
    struct pontos_t local; // localização da missão
};

typedef struct mundo_t
{
    struct lef_t *eventos;   // lista de eventos futuros
    struct heroi_t *heroi;   // vetor representando todos os heróis
    struct base_t *base;     // vetor representando todas as bases
    struct missao_t *missao; // vetor representando todas as missões
    int relogio;             // tempo atual do mundo
    int size_max;            // x == y coordenadas máximas do plano cartesiano (as coordenadas mínimas são 0, 0);
    int n_herois;            // número de heróis
    int n_bases;             // número de bases
    int n_missoes;           // número de missões
    int n_miss_impos;        // número de missões impossíveis
    int n_habil;             // número de habilidades distintas possíveis

} mundo_t;

int gera_aleat(int min, int max);

int cria_herois(struct mundo_t *mundo);

int destroi_herois(struct mundo_t *mundo);

int cria_bases(struct mundo_t *mundo);

int destroi_bases(struct mundo_t *mundo);

int cria_missoes(struct mundo_t *mundo);

int destroi_missoes(struct mundo_t *mundo);

struct mundo_t *cria_mundo();

int destroi_mundo(struct mundo_t *mundo);

void fim_execucao(char *msg);

int retorna_relogio(struct mundo_t *mundo);

struct lef_t *retorna_eventos(mundo_t *mundo);

#endif