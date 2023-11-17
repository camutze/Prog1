/*Simulador feito por Carlos A. T. Mutzenberg
**GRR 20215520*/
#include <stdio.h>
#include <stdlib.h>

#include "simulador.h"

int gera_aleat(int min, int max)
{   
    /*Gera um numero aleatorio entre min e max*/
    return (rand() % (max - min + 1)) + min;
}

void set_aleat(struct set_t *set, int tam)
{
    /*Gera um conjunto aleatorio de tamanho tam*/
    while (set_card(set) < tam)
        set_add(set, gera_aleat(0, N_HABILIDADES -1));
}

int cria_herois(struct mundo_t *mundo)
{
    struct heroi_t *heroi;
    int tam, i;

    if (!(heroi = malloc(sizeof(struct heroi_t) * mundo->n_herois)))
        fim_execucao("alocando herois");

    /*Inicializa todas as variaveis de todos os herois*/
    for (i = 0; i < mundo->n_herois; i++)
    {
        heroi[i].id = i;
        heroi[i].experiencia = 0;
        heroi[i].paciencia = gera_aleat(1, 100);
        heroi[i].velocidade = gera_aleat(50, 5000);

        tam = gera_aleat(1, 3);
        heroi[i].habil = set_create(N_HABILIDADES - 1);
        set_aleat(heroi[i].habil, tam);
    }

    mundo->heroi = heroi;
    return 1;
}

int destroi_herois(struct mundo_t *mundo)
{
    if (!mundo)
        return 0;
    if (!mundo->heroi)
        return 0;

    for (int i = 0; i < mundo->n_herois; i++)
        mundo->heroi[i].habil = set_destroy(mundo->heroi[i].habil);

    free(mundo->heroi);
    return 1;
}

int cria_bases(struct mundo_t *mundo)
{
    struct base_t *base;
    int i;

    if (!mundo)
        return 0;

    if (!(base = malloc(sizeof(struct base_t) * mundo->n_bases)))
        fim_execucao("alocando base");

    for (i = 0; i < mundo->n_bases; i++)
    {
        base[i].id = i;
        base[i].lotacao = gera_aleat(3, 10);

        base[i].presentes = set_create(mundo->n_herois);
        base[i].lista_espera = lista_cria();
        base[i].local.x = gera_aleat(0, N_TAMANHO_MUNDO - 1); // x
        base[i].local.y = gera_aleat(0, N_TAMANHO_MUNDO - 1); // y
    }

    mundo->base = base;
    return 1;
}

int destroi_bases(struct mundo_t *mundo)
{
    if (!mundo)
        return 0;

    for (int i = 0; i < mundo->n_bases; i++)
    {
        set_destroy(mundo->base[i].presentes);
        lista_destroi(mundo->base[i].lista_espera);
    }
    free(mundo->base);
    return 1;
}

int cria_missoes(struct mundo_t *mundo)
{
    struct missao_t *missao;
    int tam;

    if (!(missao = malloc(sizeof(struct missao_t) * mundo->n_missoes)))
        fim_execucao("alocando missao");

    for (int i = 0; i < mundo->n_missoes; i++)
    {
        missao[i].id = i;

        missao[i].local.x = gera_aleat(0, N_TAMANHO_MUNDO - 1);
        missao[i].local.y = gera_aleat(0, N_TAMANHO_MUNDO - 1);
        missao[i].realizada = 0;
        missao[i].tentativas = 0;


        missao[i].habil = set_create(N_HABILIDADES -1);
        tam = gera_aleat(5, 9);
        
        set_aleat(missao[i].habil, tam);
    }
    mundo->missao = missao;
    return 1;
}

int destroi_missoes(struct mundo_t *mundo)
{
    if (!mundo)
        return 0;
    if (!mundo->missao)
        return 0;

    for (int i = 0; i < mundo->n_missoes; i++)
        set_destroy(mundo->missao[i].habil);
    
    free(mundo->missao);

    return 1;
}

struct mundo_t *cria_mundo()
{
    struct mundo_t *mundo;

    // aloca o mundo
    if (!(mundo = malloc(sizeof(struct mundo_t))))
        fim_execucao("alocando mundo");

    mundo->relogio = T_INICIO;
    mundo->size_max = N_TAMANHO_MUNDO;
    mundo->n_habil = N_HABILIDADES;
    mundo->n_missoes = T_FIM_DO_MUNDO / 100;
    mundo->n_herois = N_HABILIDADES * 5;
    mundo->n_bases = mundo->n_herois / 6;
    mundo->n_miss_impos = 0;
    
    mundo->eventos = cria_lef();
    cria_herois(mundo);
    cria_bases(mundo);
    cria_missoes(mundo);

    return mundo;
}

int destroi_mundo(struct mundo_t *mundo)
{
    if (!mundo)
        return 0;

    destroi_bases(mundo);
    destroi_herois(mundo);
    destroi_missoes(mundo);
    destroi_lef(mundo->eventos);

    free(mundo);

    return 1;
}

int retorna_relogio(mundo_t *mundo)
{
    return mundo->relogio;
}

struct lef_t *retorna_eventos(mundo_t *mundo)
{
    return mundo->eventos;
}

void fim_execucao(char *msg)
{
    printf("Erro: %s\n", msg);
    exit(-1);
}
