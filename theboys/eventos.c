#include <stdio.h>
#include <stdlib.h>

#include "simulador.h"
#include "eventos.h"

long calcula_distancia(struct pontos_t loc, struct pontos_t next_loc)
{
    long distancia;

    // calculo da distancia
    long x = (next_loc.x - loc.x) * (next_loc.x - loc.x);
    long y = (next_loc.y - loc.y) * (next_loc.y - loc.y);

    distancia = sqrt(x + y);

    return distancia;
}

void testa_ponteiros(mundo_t *m)
{
    if (!m)
        fim_execucao("mundo nao existe");
    if (!m->eventos)
        fim_execucao("eventos nao existe");
    if (!m->heroi)
        fim_execucao("heroi nao existe");
    if (!m->base)
        fim_execucao("base nao existe");
    if (!m->missao)
        fim_execucao("missao nao existe");
}

struct set_t *uniao_habil(mundo_t *m, int id_base)
{
    struct set_t *uniao;
    int i;

    if (!(uniao = set_create(N_HABILIDADES - 1)))
        fim_execucao("set create in fun uniao_habilidades");

    /*1 - Heroi esta na base mais proxima,onde o id é: "id_base"
    **faço a uniao de todas as habilidades de todos os herois que estao na base.
    **2- ele vai de 0 ate o lotação do conjunto set_t presentes*/
    i = 0;
    while (i < m->n_herois)
    {
        /*Pergunta se o heroi "i" esta contido no conjunto "presentes"*/
        if (set_in(m->base[id_base].presentes, i))
            set_union(m->heroi[i].habil, uniao, uniao);

        i++;
    }
    return uniao;
}

void troca(int vetor[], int vetor_id[], int a, int b)
{
    int aux, aux_id;

    aux = vetor[a];
    aux_id = vetor_id[a];

    vetor[a] = vetor[b];
    vetor_id[a] = vetor_id[b];

    vetor[b] = aux;
    vetor_id[b] = aux_id;
}

void ordena_vetor(int vetor[], int vetor_id[], int n)
{
    int i, j, min;

    for (i = 0; i < n - 1; i++)
    {
        min = i;
        for (j = i + 1; j < n; j++)
            if (vetor[j] < vetor[min])
                min = j;
        troca(vetor, vetor_id, i, min);
    }
}

void atualiza_relogio(mundo_t *m, struct evento_t *ev)
{
    m->relogio = ev->tempo;
}

/******************EVENTOS************************/
// ok
void evento_chega(mundo_t *m, int clk, int h, int b)
{
    struct evento_t *ev;
    bool espera;

    testa_ponteiros(m);
    m->heroi[h].base_id = b;

    /*se há vagas em B e a fila de espera está vazia:*/
    if (set_card(m->base[b].presentes) < m->base[b].lotacao && !lista_vazia(m->base[b].lista_espera))
        espera = true;
    else
        /*Se for maior espera TRUE, FALSE caso contrario*/
        espera = (m->heroi[h].paciencia) > (10 * lista_tamanho(m->base[b].lista_espera));

    /*Imprime o evento*/
    printf("%6d: CHEGA  HEROI %2d ", clk, h);
    printf("BASE %d (%2d/%2d) ", b, set_card(m->base[b].presentes), m->base[b].lotacao);

    /*Disparo de novos eventos*/
    if (espera)
    {
        if (!(ev = cria_evento(clk, EV_ESPERA, h, b)))
            fim_execucao("nao aloc func evento_chega");
        printf("ESPERA");
    }
    else
    {
        if (!(ev = cria_evento(clk, EV_DESISTE, h, b)))
            fim_execucao("nao aloc func evento_chega");
        printf("DESISTE");
    }
    printf("\n");
    insere_lef(m->eventos, ev);
}

// ok
void evento_espera(mundo_t *m, int clk, int h, int b)
{
    struct evento_t *ev;
    testa_ponteiros(m);

    printf("%6d: ESPERA HEROI %2d BASE %d (%2d)", clk, h, b, lista_tamanho(m->base[b].lista_espera));

    /*adiciona H ao fim da fila de espera de B*/
    lista_insere(m->base[b].lista_espera, h, L_FIM);
    lista_imprime("FILA", m->base[b].lista_espera);

    if (!(ev = cria_evento(clk, EV_AVISA, h, b)))
        fim_execucao("nao aloc func evento_espera");
    insere_lef(m->eventos, ev);
}

void evento_desiste(mundo_t *m, int clk, int h, int b)
{
    struct evento_t *ev;
    int dest_b;

    printf("%6d: DESIST HEROI %2d BASE %d \n", clk, h, b);

    testa_ponteiros(m);

    dest_b = gera_aleat(0, m->n_bases - 1);

    if (!(ev = cria_evento(clk, EV_VIAJA, h, dest_b)))
        fim_execucao("nao aloc func evento_desiste");
    insere_lef(m->eventos, ev);
}

void evento_avisa(mundo_t *m, int clk, int h, int b)
{
    struct evento_t *ev;

    testa_ponteiros(m);
    printf("%6d: AVISA  PORTEIRO BASE %d (%2d/%2d)", clk, b, set_card(m->base[b].presentes), m->base[b].lotacao);
    lista_imprime("FILA", m->base[b].lista_espera);

    /*enquanto houver vaga em B e houver heróis esperando na fila*/
    while ((set_card(m->base[b].presentes) < m->base[b].lotacao) && !lista_vazia(m->base[b].lista_espera))
    {

        /*retira primeiro herói (H') da fila de B, armazena o id do heroi em h*/
        lista_retira(m->base[b].lista_espera, &h, L_INICIO);

        printf("%6d: AVISA  PORTEIRO BASE %d ADMITE %2d\n", clk, b, h);

        if (!(ev = cria_evento(clk, EV_ENTRA, h, b)))
            fim_execucao("nao aloc func evento_avisa");
        insere_lef(m->eventos, ev);
    }
}

void evento_entra(mundo_t *m, int clk, int h, int b)
{
    struct evento_t *ev;
    int tpb; // tempo de permanência na base

    testa_ponteiros(m);

    /*adiciona H' ao conjunto de heróis presentes em B, o mesmo h que foi removido*/
    set_add(m->base[b].presentes, h);

    /*Calcula o quanto tempo o heroi vai ficar dentro desta mesma base*/
    tpb = (m->heroi[h].paciencia * gera_aleat(1, 20) + 15);

    printf("%6d: ENTRA  HEROI %2d BASE %d (%2d/%2d) SAI %d\n", clk, h, b, set_card(m->base[b].presentes), m->base[b].lotacao, clk + tpb);

    /*cria proximo evento que ira acontecer relogio + tpd*/
    if (!(ev = cria_evento(clk + tpb, EV_SAI, h, b)))
        fim_execucao("nao aloc func evento_entra");
    insere_lef(m->eventos, ev);
}

void evento_sai(mundo_t *m, int clk, int h, int b)
{
    struct evento_t *ev;
    int dest_b;

    testa_ponteiros(m);

    printf("%6d: SAI  HEROI %2d BASE %d (%2d/%2d)\n", clk, h, b, set_card(m->base[b].presentes), m->base[b].lotacao);

    /*retira H do conjunto de heróis presentes em B*/
    set_del(m->base[b].presentes, h);

    /*escolhe uma base destino D aleatória*/
    dest_b = gera_aleat(0, m->n_bases - 1);

    /*cria ev VIAJA*/
    if (!(ev = cria_evento(clk, EV_VIAJA, h, dest_b)))
        fim_execucao("nao aloc func evento_sai");
    insere_lef(m->eventos, ev);

    /*cria ev AVISA*/
    if (!(ev = cria_evento(clk, EV_AVISA, h, b)))
        fim_execucao("nao aloc func evento_sai");
    insere_lef(m->eventos, ev);
}

void evento_viaja(mundo_t *m, int clk, int h, int b)
{
    struct evento_t *ev;
    int b_ori;
    int dist, duracao;

    b_ori = m->heroi[h].base_id;

    dist = calcula_distancia(m->base[b_ori].local, m->base[b].local);
    duracao = dist / m->heroi[h].velocidade;

    printf("%6d: VIAJA  HEROI %2d BASE %d BASE %d DIST %d VEL %d CHEGA %d\n", clk, h, b_ori,
           b, dist, m->heroi[h].velocidade, clk + duracao);

    if (!(ev = cria_evento(clk + duracao, EV_CHEGA, h, b)))
        fim_execucao("nao aloc func evento_viaja");
    insere_lef(m->eventos, ev);
}

void evento_missao(mundo_t *m, int clk, int mis)
{
    /*uniao = uniao_habilidades(m, i);
    adiciona_exp(m, id_base);*/
    struct evento_t *ev;
    struct set_t *uniao;
    int id_base[m->n_bases], distancia_b[m->n_bases];
    int i, j, sair;

    testa_ponteiros(m);

    m->missao[mis].tentativas++; // incrementa tentativas

    printf("%6d: MISSAO %d HAB REQ: ", clk, mis);
    set_print(m->missao[mis].habil);
    printf("\n");

    /*calcula a distância de cada base ao local da missão M*/
    for (i = 0; i < m->n_bases; i++)
    {
        distancia_b[i] = calcula_distancia(m->base[i].local, m->missao[mis].local);
        id_base[i] = i;
    }

    /*ordena o vetor de distancias*/
    ordena_vetor(distancia_b, id_base, m->n_bases);

    for (i = 0; i < m->n_bases; i++)
    {
        uniao = uniao_habil(m, id_base[i]);
        printf("%6d: MISSAO %d HAB BASE %d: ", clk, mis, id_base[i]);
        set_print(uniao);
        printf("\n");
        set_destroy(uniao);
    }

    sair = 0;
    i = 0;
    while (!sair && i < m->n_bases)
    {
        uniao = uniao_habil(m, id_base[i]);
        /*se a base B[i] tem heróis com todas as habilidades necessárias para cumprir a missão M*/
        if (set_contains(uniao, m->missao[mis].habil))
        {
            printf("%6d: MISSAO %d CUMPRIDA BASE %d HEROIS: ", clk, mis, id_base[i]);
            set_print(m->base[i].presentes);
            printf("\n");

            m->missao[mis].realizada = 1; // missao realizada

            /*incrementa a experiência de todos os heróis que estão na base B[i]*/
            for (j = 0; j < m->n_herois; j++)
            {
                if (set_in(m->base[i].presentes, j))
                    m->heroi[j].experiencia++;
            }
            sair = 1;
        }
        set_destroy(uniao);
        i++;
    }

    /*se não há base com heróis com todas as habilidades necessárias para cumprir a missão M*/
    if (!sair)
    {
        printf("%d: MISSAO %d IMPOSSIVEL\n", clk, mis);
        m->n_miss_impos++;

        if (!(ev = cria_evento(clk + 24 * 60, EV_MISSAO, mis, 0)))
            fim_execucao("fun even missao cria evento");
        insere_lef(m->eventos, ev);
    }
}

void evento_fim(mundo_t *m)
{
    int m_compridas, tentativas; // missões cumpridas (missao total - missao impossivel)
    m_compridas = 0;
    tentativas = 0;

    testa_ponteiros(m);
    printf("%d: FIM\n", m->relogio);

    for (int i = 0; i < m->n_herois; i++)
    {
        printf("HEROI %2d PAC  %3d", i, m->heroi[i].paciencia);
        printf(" VEL %4d EXP %4d HABS ", m->heroi[i].velocidade, m->heroi[i].experiencia);
        set_print(m->heroi[i].habil);
        printf("\n");
    }

    for (int i = 0; i < m->n_missoes; i++)
    {
        tentativas = m->missao[i].tentativas + tentativas;
        m_compridas += m->missao[i].realizada;
    }

    printf("%d MISSOES CUMPRIDAS\n", m_compridas);
    printf("%d/%d MISSOES CUMPRIDAS (%.2f%%), MEDIA %.2f TENTATIVAS/MISSAO\n", m_compridas, m->n_missoes,
           (float)m_compridas / m->n_missoes * 100, (float)tentativas / m->n_missoes);
}

void evento_inicia(mundo_t *m)
{
    struct evento_t *ev;
    int base, tempo;

    testa_ponteiros(m);

    for (int i = 0; i < m->n_herois; i++)
    {
        base = gera_aleat(0, m->n_bases - 1);
        tempo = gera_aleat(0, TEMPO_INICIAL); // 4320 = 60*24*3 = 3 dias
        if (!(ev = cria_evento(tempo, EV_CHEGA, i, base)))
            fim_execucao("nao aloc func evento_inicia");
        insere_lef(m->eventos, ev);
    }

    for (int i = 0; i < m->n_missoes; i++)
    {
        tempo = gera_aleat(0, T_FIM_DO_MUNDO - 1);
        if (!(ev = cria_evento(tempo, EV_MISSAO, i, 0)))
            fim_execucao("nao aloc func evento_inicia");
        insere_lef(m->eventos, ev);
    }
    if (!(ev = cria_evento(T_FIM_DO_MUNDO, EV_FIM, 0, 0)))
        fim_execucao("nao aloc func evento_inicia");
    insere_lef(m->eventos, ev);
}