#include <stdlib.h>
#include <simulador.h>

#define T_INICIO 0
#define T_FIM_DO_MUNDO 525600
#define N_TAMANHO_MUNDO 20000
#define N_HABILIDADES 10
#define N_HEROIS N_HABILIDADES * 5
#define N_BASES N_HEROIS / 6
#define N_MISSOES T_FIM_DO_MUNDO / 100

struct heroi_h *cria_um_heroi(struct missao_m *mundo, int id)
{
    struct heroi_h *heroi;

    if (!(heroi = malloc(sizeof(struct heroi_h))))
        return NULL;

    heroi->id = id;
    heroi->experiencia = 0;
    heroi->paciencia = gera_aleat(1, 100);
    heroi->velocidade = gera_aleat(50, 5000);
    heroi->habilidades = set_create(gera_aleat(1, 3));
    for (int i = 0; i < heroi->habilidades->size; i++)
    {
        set_add(heroi->habilidades, gera_aleat(0, N_HABILIDADES)); // Quanto eu inicio aqui?
    }

    return heroi;
}

struct heroi_h *destroi_um_heroi(struct heroi_h *heroi)
{
    if (!heroi)
        return NULL;

    set_destroy(heroi->habilidades);
    free(heroi);

    return NULL;
}

struct base_b *cria_base(int id)
{
    struct base_b *base;

    if (!(base = malloc(sizeof(struct base_b))))
        return NULL;

    base->id = id;
    /*E SE DER REPETIDO PROFESSOR?*/
    base->local[0] = gera_aleat(0, N_TAMANHO_MUNDO - 1); // x
    base->local[1] = gera_aleat(0, N_TAMANHO_MUNDO - 1); // y

    base->lotacao = gera_aleat(3, 10);

    base->presentes = set_create(base->lotacao);

    base->lista_espera = lista_create();

    return base;
}

struct base_b *destroi_base(struct base_b *base)
{
    if (!base)
        return NULL;

    set_destroy(base->presentes);
    lista_destroy(base->lista_espera);
    free(base);

    return NULL;
}

//lembre se de passar o id sequencial que nao se repete
struct missao_m *cria_missao(int id)
{
    struct missao_m *missao;

    if (!(missao = malloc(sizeof(struct missao_m))))
        return NULL;

    missao->id = id;
    missao->local[0] = gera_aleat(0, N_TAMANHO_MUNDO - 1); // x
    missao->local[1] = gera_aleat(0, N_TAMANHO_MUNDO - 1); // y

    missao->habilidades = set_create(gera_aleat(6, 10));
    
    return missao;
}

struct missao_m *destroi_missao(struct missao_m *missao)
{
    if (!missao)
        return NULL;

    set_destroy(missao->habilidades);
    free(missao);

    return NULL;

}




int gera_aleat(int min, int max)
{
    return (rand() % (max - min + 1)) + min;
}