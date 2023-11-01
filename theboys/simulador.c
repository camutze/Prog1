#include <stdlib.h>
#include "simulador.h"

int gera_aleat(int min, int max)
{
    return (rand() % (max - min + 1)) + min;
}

/*herois INICIO*/
struct heroi_h *cria_um_heroi(int id)
{
    struct heroi_h *heroi;

    if (!(heroi = malloc(sizeof(struct heroi_h))))
        return NULL;

    heroi->id = id;
    heroi->experiencia = 0;
    heroi->paciencia = gera_aleat(1, 100);
    heroi->velocidade = gera_aleat(50, 5000);
    heroi->habil = set_create(gera_aleat(1, 3));
    while (set_card(heroi->habil) < heroi->habil->size)
        set_add(heroi->habil, gera_aleat(0, N_HABILIDADES)); // Quanto eu inicio aqui?

    return heroi;
}

void cria_todos_herois(struct mundo_m *mundo)
{
    for (int i = 1; i < mundo->n_herois; i++)
        mundo->herois[i] = cria_um_heroi(i);
}

void destroi_todos_herois(struct mundo_m *mundo)
{
    for (int i = 1; i < mundo->n_herois; i++)
        mundo->herois[i] = destroi_um_heroi(mundo->herois[i]);
}

struct heroi_h *destroi_um_heroi(struct heroi_h *heroi)
{
    if (!heroi)
        return NULL;
    if (heroi->habil)
        set_destroy(heroi->habil);
    free(heroi);

    return NULL;
}
/*herois FIM */

/*base INICIO*/
struct base_b *cria_base(int id)
{
    struct base_b *base;

    if (!(base = malloc(sizeof(struct base_b))))
        return NULL;

    base->id = id;
    /*E SE DER REPETIDO PROFESSOR?*/
    base->local.x = gera_aleat(0, N_TAMANHO_MUNDO - 1); // x
    base->local.y = gera_aleat(0, N_TAMANHO_MUNDO - 1); // y

    base->lotacao = gera_aleat(3, 10);

    base->presentes = set_create(base->lotacao);

    base->lista_espera = lista_cria();

    return base;
}

void cria_todas_bases(struct mundo_m *mundo)
{
    for (int i = 0; i < mundo->n_bases; i++)
        mundo->bases[i] = cria_base(i);
}

void destroi_todas_bases(struct mundo_m *mundo)
{
    for (int i = 0; i < mundo->n_bases; i++)
        mundo->bases[i] = destroi_base(mundo->bases[i]);
}

struct base_b *destroi_base(struct base_b *base)
{
    if (!base)
        return NULL;

    set_destroy(base->presentes);
    lista_destroi(base->lista_espera);
    free(base);

    return NULL;
}
/*------------base FIM -------------*/

// lembre se de passar o id sequencial que nao se repete
/*-----------missao INICIO----------*/
struct missao_m *cria_missao(int id)
{
    struct missao_m *missao;

    if (!(missao = malloc(sizeof(struct missao_m))))
        return NULL;

    missao->id = id;
    missao->local.x = gera_aleat(0, N_TAMANHO_MUNDO - 1); // x
    missao->local.y = gera_aleat(0, N_TAMANHO_MUNDO - 1); // y

    missao->habil = set_create(gera_aleat(6, 10));

    while (set_card(missao->habil) < missao->habil->size)
        set_add(missao->habil, gera_aleat(0, N_HABILIDADES));

    return missao;
}

void cria_todas_missoes(struct mundo_m *mundo)
{
    for (int i = 0; i < mundo->n_missoes; i++)
        mundo->missoes[i] = cria_missao(i);
}

void destroi_todas_missoes(struct mundo_m *mundo)
{
    for (int i = 0; i < mundo->n_missoes; i++)
        mundo->missoes[i] = destroi_missao(mundo->missoes[i]);
}

struct missao_m *destroi_missao(struct missao_m *missao)
{
    if (!missao)
        return NULL;

    set_destroy(missao->habil);
    free(missao);

    return NULL;
}
/*-----------missao FIM----------*/

struct mundo_m *cria_mundo()
{
    struct mundo_m *mundo;

    // aloca o mundo
    if (!(mundo = malloc(sizeof(struct mundo_m))))
        return NULL;

    mundo->relogio = T_INICIO;
    mundo->size_max = N_TAMANHO_MUNDO;
    mundo->n_habil = N_HABILIDADES;
    mundo->n_missoes = T_FIM_DO_MUNDO / 100;
    mundo->n_herois = N_HABILIDADES * 5;
    mundo->n_bases = mundo->n_herois / 6;

    // aloca os herois
    if (!(mundo->herois = malloc(sizeof(struct heroi_h) * mundo->n_herois)))
        return NULL;
    // aloca as bases
    if (!(mundo->bases = malloc(sizeof(struct base_b) * mundo->n_bases)))
        return NULL;
    // aloca as missoes
    if (!(mundo->missoes = malloc(sizeof(struct missao_m) * mundo->n_missoes)))
        return NULL;

    cria_todos_herois(mundo);
    cria_todas_bases(mundo);
    cria_todas_missoes(mundo);

    return mundo;
}
struct mundo_m *destroi_mundo(struct mundo_m *mundo)
{
    if (!mundo)
        return NULL;

    destroi_todas_bases(mundo);
    destroi_todas_missoes(mundo);
    destroi_todos_herois(mundo);

    free(mundo->herois);
    free(mundo->bases);
    free(mundo->missoes);
    free(mundo);

    return NULL;
}