#ifndef _SIMULADOR_H
#define _SIMULADOR_H

#include "set.h"
#include "lista.h"
#include "lef.h"

#define T_INICIO 0
#define T_FIM_DO_MUNDO 525600 // 525600
#define N_TAMANHO_MUNDO 20000 // 20000
#define N_HABILIDADES 10
#define TEMPO_INICIAL 200 // 4320 = 60*24*3 = 3 dias

struct heroi_t
{
    int id;              // identificador do herói
    int experiencia;     // Vai ser incrementada de acordo com as missoes que o heroi compriu
    int paciencia;       // inicializada aleatoriamente
    int velocidade;      // em minutos
    int base_id;         // base em que o herói está
    struct set_t *habil; // conjunto de habilidades do herói
};

struct pontos_t
{
    unsigned int x; // coordenadas x do plano cartesiano
    unsigned int y; // coordenadas y do plano cartesiano
};

struct base_t
{
    int id;                  // identificador da base
    int lotacao;             // número máximo de heróis que podem estar na base
    struct set_t *presentes; // conjunto de herois presentes na base
    lista_t *lista_espera;   // lista de herois esperando para entrar na base
    struct pontos_t local;   // localização da base
};

struct missao_t
{
    int id;                // identificador da missão
    struct set_t *habil;   // conjunto de habilidades necessárias para cumprir a missão
    short realizada;       // se foi comcluida == 1, 0 caso contrario
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

/*Retorna um inteiro aleatório entre min e max*/
int gera_aleat(int min, int max);

/*Aloca um vetor de herois e inicializa, retorna 1 se sucesso, 0 caso contrário*/
int cria_herois(struct mundo_t *mundo);

/*Libera a memória alocada para o vetor de herois, retorna 1 se sucesso, 0 caso contrario*/
int destroi_herois(struct mundo_t *mundo);

/*Aloca um vetor de bases e inicializa, retorna 1 se sucesso, 0 caso contrário*/
int cria_bases(struct mundo_t *mundo);

/*Libera a memória alocada para o vetor de bases, retorna 1 se sucesso, 0 caso contrario*/
int destroi_bases(struct mundo_t *mundo);

/*Aloca um vetor de missoes e inicializa, retorna 1 se sucesso, 0 caso contrário*/
int cria_missoes(struct mundo_t *mundo);

/*Libera a memória alocada para o vetor de missoes, retorna 1 se sucesso, 0 caso contrario*/
int destroi_missoes(struct mundo_t *mundo);

/*Cria um mundo e inicializa todas as variáveis, retorna um ponteiro para o mundo criado*/
struct mundo_t *cria_mundo();

/*Libera a memória alocada para o mundo, retorna 1 se sucesso, 0 caso contrario*/
int destroi_mundo(struct mundo_t *mundo);

/*Função que imprime uma mensagem de erro passada por onde foi chamada
 e finaliza a execução do programa*/
void fim_execucao(char *msg);

/*Retorna o relogio do mundo*/
int retorna_relogio(struct mundo_t *mundo);

/*Retorna lef de eventos do mundo*/
struct lef_t *retorna_eventos(mundo_t *mundo);

#endif