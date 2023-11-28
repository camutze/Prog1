#include <stdio.h>
#include <stdlib.h>

#include "simulador.h"
#include "eventos.h"
#include "lef.h"

/*Calcula a discancia entre dois pontos*/
long calcula_distancia(struct pontos_t loc, struct pontos_t next_loc)
{
    long distancia;

    /*Calcula a distancia entre dois pontos*/
    long x = (next_loc.x - loc.x) * (next_loc.x - loc.x);
    long y = (next_loc.y - loc.y) * (next_loc.y - loc.y);

    distancia = sqrt(x + y);

    return distancia;
}

/*Testa se os ponteiros do mundo existem, se não existem, encerra o programa*/
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

/*faço a uniao das habilidades de todos os herois presentes na base*/
struct set_t *uniao_habil(mundo_t *m, int id_base)
{
    struct set_t *uniao;
    int i;

    if (!(uniao = set_create(N_HABILIDADES - 1)))
        fim_execucao("set create in fun uniao_habilidades");

    /*para cada heroi, pergunto se ele esta na base, caso esteja,
    incluo as suas habilidades ao conjunto de habilidades da base,
    sem repetir alguma que ja esta la. Def. Uniao*/
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

/*Troca os valores de dois vetores*/
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

/*Ordena o vetor de distancias e o vetor de id_base,
 usando SelectionSort*/
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
void ev_chega(mundo_t *m, int clk, int h, int b)
{
    struct evento_t *ev;
    bool espera;

    testa_ponteiros(m);
    m->heroi[h].base_id = b;

    /*se há vagas em B e a fila de espera está vazia:*/
    if (set_card(m->base[b].presentes) < m->base[b].lotacao && (!lista_vazia(m->base[b].lista_espera)))
        espera = 1;
    else
        /*Se for maior espera TRUE, FALSE caso contrario*/
        espera = (m->heroi[h].paciencia) > (10 * lista_tamanho(m->base[b].lista_espera));

    /*Imprime o evento*/
    printf("%6d: CHEGA  HEROI %2d ", clk, h);
    printf("BASE %d (%2d/%2d) ", b, set_card(m->base[b].presentes), m->base[b].lotacao);

    /*Se espera, disparo EV Espera*/
    if (espera)
    {

        if (!(ev = cria_evento(clk, EV_ESPERA, h, b)))
            fim_execucao("nao aloc func evento_chega");
        printf("ESPERA");
    }
    /*Se não espera, disparo EV Desiste*/
    else
    {
        if (!(ev = cria_evento(clk, EV_DESISTE, h, b)))
            fim_execucao("nao aloc func evento_chega");
        printf("DESISTE");
    }
    printf("\n");
    insere_lef(m->eventos, ev);
}

void ev_espera(mundo_t *m, int clk, int h, int b)
{
    struct evento_t *ev;
    testa_ponteiros(m);

    printf("%6d: ESPERA HEROI %2d BASE %d (%2d)\n", clk, h, b, set_card(m->base[b].presentes));

    /*adiciona H ao fim da fila de espera de B*/
    lista_insere(m->base[b].lista_espera, h, L_FIM);

    if (!(ev = cria_evento(clk, EV_AVISA, h, b)))
        fim_execucao("nao aloc func evento_espera");
    insere_lef(m->eventos, ev);
}

void ev_desiste(mundo_t *m, int clk, int h, int b)
{
    struct evento_t *ev;
    int dest_b;
    testa_ponteiros(m);

    printf("%6d: DESIST HEROI %2d BASE %d \n", clk, h, b);
    /*escolhe uma base destino D aleatória*/
    dest_b = gera_aleat(0, m->n_bases - 1);

    if (!(ev = cria_evento(clk, EV_VIAJA, h, dest_b)))
        fim_execucao("nao aloc func evento_desiste");
    insere_lef(m->eventos, ev);
}

void ev_avisa(mundo_t *m, int clk, int h, int b)
{
    struct evento_t *ev;
    testa_ponteiros(m);

    printf("%6d: AVISA  PORTEIRO BASE %d (%2d/%2d)", clk, b, set_card(m->base[b].presentes), m->base[b].lotacao);
    lista_imprime("FILA", m->base[b].lista_espera);

    /*enquanto houver vaga em B e houver heróis esperando na fila*/
    while ((set_card(m->base[b].presentes) < m->base[b].lotacao) && !(lista_vazia(m->base[b].lista_espera)))
    {
        /*retira primeiro herói (H') da fila de B, armazena o id do heroi em h*/
        lista_retira(m->base[b].lista_espera, &h, L_INICIO);

        printf("%6d: AVISA  PORTEIRO BASE %d ADMITE %2d\n", clk, b, h);

        if (!(ev = cria_evento(clk, EV_ENTRA, h, b)))
            fim_execucao("nao aloc func evento_avisa");
        insere_lef(m->eventos, ev);
    }
}

void ev_entra(mundo_t *m, int clk, int h, int b)
{
    struct evento_t *ev;
    int tpb;
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

void ev_sai(mundo_t *m, int clk, int h, int b)
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

void ev_viaja(mundo_t *m, int clk, int h, int b)
{
    struct evento_t *ev;
    int b_origem;
    int dist, duracao;
    testa_ponteiros(m);

    b_origem = m->heroi[h].base_id;
    /*calcula a distancia entre a base de origem e a base destino*/
    dist = calcula_distancia(m->base[b_origem].local, m->base[b].local);
    /*calcula o tempo de viagem*/
    duracao = dist / m->heroi[h].velocidade;

    printf("%6d: VIAJA  HEROI %2d BASE %d BASE %d DIST %d VEL %d CHEGA %d\n", clk, h, b_origem,
           b, dist, m->heroi[h].velocidade, clk + duracao);

    if (!(ev = cria_evento(clk + duracao, EV_CHEGA, h, b)))
        fim_execucao("nao aloc func evento_viaja");
    insere_lef(m->eventos, ev);
}

void ev_missao(mundo_t *m, int clk, int mis)
{
    struct evento_t *ev;
    struct set_t *uniao_h;
    int id_base[m->n_bases], distancia[m->n_bases];
    int i, j, base_apta;
    testa_ponteiros(m);

    printf("%6d: MISSAO %d HAB REQ: ", clk, mis);
    set_print(m->missao[mis].habil);
    printf("\n");

    /*Mais uma tentativa*/
    m->missao[mis].tentativas++;

    /*Armazena em um vetor o indice e o outro a distancia para posteriormente ordenar*/
    for (i = 0; i < m->n_bases; i++)
    {
        distancia[i] = calcula_distancia(m->base[i].local, m->missao[mis].local);
        id_base[i] = i;
    }

    ordena_vetor(distancia, id_base, m->n_bases);

    /*Com o vetor ordenado, começamos a busca da base que cumpre*/
    base_apta = -1;
    for (i = 0; i < m->n_bases; i++)
    {
        uniao_h = uniao_habil(m, id_base[i]);

        printf("%6d: MISSAO %d HAB BASE %d: ", clk, mis, id_base[i]);
        set_print(uniao_h);
        printf("\n");

        /*Se dentro de uniao, tem todas as habilidades da missão, ela pode ser cumprida*/
        if (set_contains(uniao_h, m->missao[mis].habil))
        {
            base_apta = id_base[i];
            set_destroy(uniao_h);
            break;
        }
        set_destroy(uniao_h);
    }

    if (base_apta >= 0)
    {
        printf("%6d: MISSAO %d CUMPRIDA BASE %d HEROIS: ", clk, mis, id_base[i]);
        set_print(m->base[id_base[i]].presentes);
        printf("\n");

        m->missao[mis].realizada = 1;

        /*incrementa a experiencia dos herois presentes na base*/
        for (j = 0; j < m->n_herois; j++)
            if (set_in(m->base[id_base[i]].presentes, j))
                m->heroi[j].experiencia++;
    }
    else
    {
        /* se ele não saiu da função, a missao é impossivel*/
        printf("%6d: MISSAO %d IMPOSSIVEL\n", clk, mis);
        m->n_miss_impos++;

        if (!(ev = cria_evento(clk + 24 * 60, EV_MISSAO, mis, 0)))
            fim_execucao("nao aloc func evento_missao");
        insere_lef(m->eventos, ev);
    }
}

void ev_fim(mundo_t *m)
{
    int m_compridas, tentativas; // missões cumpridas (missao total - missao impossivel)
    m_compridas = 0;
    tentativas = 0;
    testa_ponteiros(m);

    printf("%d: FIM\n", m->relogio);

    /*Imprime o estado final d cada heroi*/
    for (int i = 0; i < m->n_herois; i++)
    {
        printf("HEROI %2d PAC  %3d", i, m->heroi[i].paciencia);
        printf(" VEL %4d EXP %4d HABS ", m->heroi[i].velocidade, m->heroi[i].experiencia);
        set_print(m->heroi[i].habil);
        printf("\n");
    }
    /*faz o calculo das missões cumpridas e das tentativas*/
    for (int i = 0; i < m->n_missoes; i++)
    {
        tentativas = m->missao[i].tentativas + tentativas;
        m_compridas += m->missao[i].realizada;
    }
    
    printf("%d MISSOES CUMPRIDAS\n", m_compridas);
    printf("%d/%d MISSOES CUMPRIDAS (%.2f%%), MEDIA %.2f TENTATIVAS/MISSAO\n", m_compridas, m->n_missoes,
           (float)m_compridas / m->n_missoes * 100, (float)tentativas / m->n_missoes);
}

void ev_inicia(mundo_t *m)
{
    struct evento_t *ev;
    int base, tempo;
    testa_ponteiros(m);

    /*cria evento CHEGA para cada herói*/
    for (int i = 0; i < m->n_herois; i++)
    {
        base = gera_aleat(0, m->n_bases - 1);
        tempo = gera_aleat(0, TEMPO_INICIAL); // 4320 = 60*24*3 = 3 dias
        if (!(ev = cria_evento(tempo, EV_CHEGA, i, base)))
            fim_execucao("nao aloc func evento_inicia");
        insere_lef(m->eventos, ev);
    }

    /*cria evento MISSAO para cada missão*/
    for (int i = 0; i < m->n_missoes; i++)
    {
        tempo = gera_aleat(0, T_FIM_DO_MUNDO - 1);
        if (!(ev = cria_evento(tempo, EV_MISSAO, i, 0)))
            fim_execucao("nao aloc func evento_inicia");
        insere_lef(m->eventos, ev);
    }
    /*Cria fim do mundo*/
    if (!(ev = cria_evento(T_FIM_DO_MUNDO, EV_FIM, 0, 0)))
        fim_execucao("nao aloc func evento_inicia");
    insere_lef(m->eventos, ev);
}

void ev_seleciona(mundo_t *mundo, struct evento_t *ev)
{
    switch (ev->tipo)
    {
    case EV_CHEGA:
        ev_chega(mundo, ev->tempo, ev->dado1, ev->dado2);
        break;

    case EV_ESPERA:
        ev_espera(mundo, ev->tempo, ev->dado1, ev->dado2);
        break;

    case EV_DESISTE:
        ev_desiste(mundo, ev->tempo, ev->dado1, ev->dado2);
        break;

    case EV_AVISA:
        ev_avisa(mundo, ev->tempo, ev->dado1, ev->dado2);
        break;

    case EV_ENTRA:
        ev_entra(mundo, ev->tempo, ev->dado1, ev->dado2);
        break;

    case EV_SAI:
        ev_sai(mundo, ev->tempo, ev->dado1, ev->dado2);
        break;

    case EV_VIAJA:
        ev_viaja(mundo, ev->tempo, ev->dado1, ev->dado2);
        break;

    case EV_MISSAO:
        ev_missao(mundo, ev->tempo, ev->dado1);
        break;
    case EV_FIM:
        ev_fim(mundo);
        break;

    default:
        break;
    }
}