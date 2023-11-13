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
    while (i < m->base[id_base].lotacao)
    {
        /*Pergunta se o heroi "i" esta contido no conjunto "presentes"*/
        if (set_in(m->base[id_base].presentes, i))
        {
            if (!set_union(m->heroi[i].habil, m->heroi[i].habil, uniao)) /*Se ele estiver contido faço a uniao de todas as habilidades de todos os herois*/
                fim_execucao("nao aloc func evento_missao");
        }
        i++;
    }
    return uniao;
}

/******************EVENTOS************************/
// ok
void evento_chega(mundo_t *m, int clk, int h, int b)
{
    struct evento_t *ev;
    bool espera;

    testa_ponteiros(m);
    m->relogio = clk;
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
        if (!(ev = cria_evento(m->relogio, EV_ESPERA, h, b)))
            fim_execucao("nao aloc func evento_chega");
        printf("ESPERA");
    }
    else
    {
        if (!(ev = cria_evento(m->relogio, EV_DESISTE, h, b)))
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

    m->relogio = clk;

    /*adiciona H ao fim da fila de espera de B*/
    lista_insere(m->base[b].lista_espera, h, L_FIM);
    lista_imprime("FILA", m->base[b].lista_espera);

    if (!(ev = cria_evento(m->relogio, EV_AVISA, h, b)))
        fim_execucao("nao aloc func evento_espera");
    insere_lef(m->eventos, ev);
}

void evento_desiste(mundo_t *m, int clk, int h, int b)
{
    struct evento_t *ev;
    int dest_b;

    printf("%6d: DESIST HEROI %2d BASE %d \n", clk, h, b);

    testa_ponteiros(m);
    m->relogio = clk;

    dest_b = gera_aleat(0, m->n_bases - 1);

    if (!(ev = cria_evento(m->relogio, EV_VIAJA, h, dest_b)))
        fim_execucao("nao aloc func evento_desiste");
    insere_lef(m->eventos, ev);
}

void evento_avisa(mundo_t *m, int clk, int h, int b)
{
    struct evento_t *ev;

    testa_ponteiros(m);
    m->relogio = clk;

    /*enquanto houver vaga em B e houver heróis esperando na fila*/
    while ((set_card(m->base[b].presentes) < m->base[b].lotacao) && !lista_vazia(m->base[b].lista_espera))
    {
        printf("%6d: AVISA  PORTEIRO BASE %d (%2d/%2d)", m->relogio, b, set_card(m->base[b].presentes), m->base[b].lotacao);
        lista_imprime("FILA", m->base[b].lista_espera);

        /*retira primeiro herói (H') da fila de B, armazena o id do heroi em h*/
        lista_retira(m->base[b].lista_espera, &h, L_INICIO);

        printf("%6d: AVISA  PORTEIRO BASE %d ADMITE %2d\n", m->relogio, b, h);

        if (!(ev = cria_evento(m->relogio, EV_ENTRA, h, b)))
            fim_execucao("nao aloc func evento_avisa");
        insere_lef(m->eventos, ev);
    }
}

void evento_entra(mundo_t *m, int clk, int h, int b)
{
    struct evento_t *ev;
    int tpb; // tempo de permanência na base

    testa_ponteiros(m);
    m->relogio = clk;

    /*adiciona H' ao conjunto de heróis presentes em B, o mesmo h que foi removido*/
    set_add(m->base[b].presentes, h);

    tpb = 15 + (m->heroi[h].paciencia * gera_aleat(1, 20));

    printf("%6d: ENTRA  HEROI %2d BASE %d (%2d/%2d) SAI %d\n", clk, h, b, set_card(m->base[b].presentes), m->base[b].lotacao, clk + tpb);

    /*cria proximo evento que ira acontecer relogio + tpd*/
    if (!(ev = cria_evento(m->relogio + tpb, EV_SAI, h, b)))
        fim_execucao("nao aloc func evento_entra");
    insere_lef(m->eventos, ev);
}

void evento_sai(mundo_t *m, int clk, int h, int b)
{
    struct evento_t *ev;
    int dest_b;

    printf("%6d: SAI  HEROI %2d BASE %d (%2d/%2d)\n", clk, h, b, set_card(m->base[b].presentes) - 1, m->base[b].lotacao);

    testa_ponteiros(m);
    m->relogio = clk;

    /*retira H do conjunto de heróis presentes em B*/
    set_del(m->base[b].presentes, h);
    /*escolhe uma base destino D aleatória*/
    dest_b = gera_aleat(0, m->n_bases - 1);

    /*cria ev VIAJA*/
    if (!(ev = cria_evento(m->relogio, EV_VIAJA, h, dest_b)))
        fim_execucao("nao aloc func evento_sai");
    insere_lef(m->eventos, ev);

    /*cria ev AVISA*/
    if (!(ev = cria_evento(m->relogio, EV_AVISA, h, b))) // BASE b ou base de destino dest_b???????????
        fim_execucao("nao aloc func evento_sai");
    insere_lef(m->eventos, ev);
}

void evento_viaja(mundo_t *m, int clk, int h, int b)
{
    struct evento_t *ev;
    int b_ori;
    long dist, duração;

    b_ori = m->heroi[h].base_id;

    dist = calcula_distancia(m->base[b_ori].local, m->base[b].local);
    duração = dist / m->heroi[h].velocidade;

    if (!(ev = cria_evento(clk + duração, EV_CHEGA, h, b)))
        fim_execucao("nao aloc func evento_viaja");
    insere_lef(m->eventos, ev);
}

void evento_missao(mundo_t *m, int clk, int mis)
{
    /*uniao = uniao_habilidades(m, i);
    adiciona_exp(m, id_base);*/
    struct evento_t *ev;
    struct set_t *uniao;
    int id_base, distancia, min_dist, i;

    testa_ponteiros(m);
    m->relogio = clk;

    m->missao[mis].tentativas++; // incrementa tentativas

    printf("%d: MISSAO %d HAB REQ: ", clk, mis);
    set_print(m->missao[mis].habil);
    printf("\n");

    /*calcula a distância de cada base ao local da missão M*/
    distancia = calcula_distancia(m->base[0].local, m->missao[mis].local);
    min_dist = distancia;

    i = 0;
    while (i < m->n_bases)
    {
        uniao = uniao_habil(m, i);
        printf("%d: MISSAO %d HAB BASE %d:", clk, mis, i);
        set_print(uniao);
        printf("\n");
        set_destroy(uniao);
        if (min_dist > distancia)
        {
            min_dist = distancia;
            id_base = i;
        }

        distancia = calcula_distancia(m->base[i].local, m->missao[mis].local);
        i++;
    }
    uniao = uniao_habil(m, id_base);

    /*se houver incrementa xp aos herois presentes na base*/
    if (set_contains(uniao, m->missao[mis].habil))
    {
        printf("%d: MISSAO %d CUMPRIDA BASE %d HEROIS: ", clk, mis, id_base);
        set_print(m->base[id_base].presentes);

        m->missao[mis].realizada = 1; // missao realizada

        for (int i = 0; i < m->n_herois; i++)
        {
            if (set_in(m->base[id_base].presentes, i))
                m->heroi[i].experiencia++;
        }
    }
    /*Se não houver adia a missao para daqui tres dias */
    else
    {

        printf("%d: MISSAO %d IMPOSSIVEL:", clk, mis);

        if (!(ev = cria_evento(m->relogio + 24 * 60, EV_MISSAO, mis, 0)))
            fim_execucao("fun even missao cria evento");
        m->n_miss_impos++;
        insere_lef(m->eventos, ev);
    }
    set_destroy(uniao);
    printf("\n");
}

void evento_fim(mundo_t *m)
{
    int m_compridas, tentativas;  // missões cumpridas (missao total - missao impossivel)
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
    for(int i = 0; i < m->n_missoes; i++)
        tentativas =  m->missao[i].tentativas + tentativas;
    printf("TENTATIVAS: %d\n", tentativas);
    
    /*5242/5256 MISSOES CUMPRIDAS (99.73%), MEDIA 2.09 TENTATIVAS/MISSAO*/
  

    // printf("%d/%d MISSOES CUMPRIDAS ", m_compridas, m->n_missoes);


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
        if (!(ev = cria_evento(tempo, EV_MISSAO, 3, 0)))
            fim_execucao("nao aloc func evento_inicia");
        insere_lef(m->eventos, ev);
    }
    if (!(ev = cria_evento(T_FIM_DO_MUNDO, EV_FIM, 0, 0)))
        fim_execucao("nao aloc func evento_inicia");
    insere_lef(m->eventos, ev);
}