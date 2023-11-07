#include <stdio.h>

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

/*Garanto que os ponteiros estao chegando certos dentro da função*/
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

/*Retorna a media de tentativas por missao*/
float media_missao(mundo_t *m)
{
    float media;
    if (!m)
        fim_execucao("mundo nao existe");
    if (!m->missao)
        fim_execucao("Missao nao existe");

    /*somo todas as as tentativas de cada uma missao, e divido pelo n_missoes*/
    media = 0;
    for (int i = 0; i < m->n_missoes; i++)
        media += m->missao[i].tentativa;

    media /= m->n_missoes;
    return media;
}

/******************EVENTOS************************/

void evento_chega(mundo_t *m, int clk, int h, int b)
{
    struct evento_t *ev;
    bool espera;

    printf("%6d: CHEGA  HEROI %2d ", clk, h);
    printf("BASE %d (%2d/%2d) ", b, set_card(m->base[b].presentes), m->base[b].lotacao);

    testa_ponteiros(m);
    m->relogio = clk;
    m->heroi[h].base_id = b;

    /*se há vagas em B e a fila de espera está vazia:*/
    if (set_card(m->base[b].presentes) < m->base->lotacao && lista_vazia(m->base[b].lista_espera))
        espera = true;
    else
        /*Se for maior espera TRUE, FALSE caso contrario*/
        espera = (m->heroi[h].paciencia) > (10 * lista_tamanho(m->base->lista_espera));

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
    insere_lef(m->eventos, ev);
}

void evento_espera(mundo_t *m, int clk, int h, int b)
{
    struct evento_t *ev;

    printf("%6d: ESPERA HEROI %2d BASE %d (%2d)", clk, h, b, lista_tamanho(m->base->lista_espera));

    testa_ponteiros(m);
    m->relogio = clk;

    /*adiciona H ao fim da fila de espera de B*/
    lista_insere(m->base[b].lista_espera, h, L_FIM);

    if (!(ev = cria_evento(m->relogio, EV_AVISA, h, b)))
        fim_execucao("nao aloc func evento_espera");
    insere_lef(m->eventos, ev);
}

void evento_desiste(mundo_t *m, int clk, int h, int b)
{
    struct evento_t *ev;
    int dest_b;

    printf("%6.d: DESIST HEROI %2.d BASE %.d", clk, h, b);

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
    while ((set_card(m->base->presentes) < m->base->lotacao) && !lista_vazia(m->base->lista_espera))
    {
        printf("%6.d: AVISA  PORTEIRO BASE %d (%2d/%2d)", clk, b, set_card(m->base[b].presentes), m->base[b].lotacao); 
        lista_imprime("FILA ", m->base[b].lista_espera);

        /*retira primeiro herói (H') da fila de B*/
        lista_retira(m->base->lista_espera, &h, L_INICIO);
        /*adiciona H' ao conjunto de heróis presentes em B*/
        set_add(m->base->presentes, h);
        printf("%6.d: AVISA  PORTEIRO BASE %d ADMITE %2d", clk, b, h);

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

    tpb = 15 + m->heroi[h].paciencia * gera_aleat(1, 20);
    printf("%6.d: ENTRA  HEROI %2.d BASE %.d (%2.d/%2.d) SAI %d", clk, h, b, set_card(m->base[b].presentes), m->base[b].lotacao, clk + tpb);


    /*cria proximo evento que ira acontecer relogio + tpd*/
    if (!(ev = cria_evento(m->relogio + tpb, EV_SAI, h, b)))
        fim_execucao("nao aloc func evento_entra");
    insere_lef(m->eventos, ev);
}
/*46101: SAI    HEROI 30 BASE 2 ( 7/9)

%6d: SAI    HEROI %2d BASE %d (%2d/%2d)
Significado: no instante 46101 o herói 30 sai da base 2, que passa a ter 7 heróis presentes e lotação de 9.*/
void evento_sai(mundo_t *m, int clk, int h, int b)
{
    struct evento_t *ev;
    int dest_b;

    printf("%6.d: SAI    HEROI %2.d BASE %.d (%2.d/%2.d)", clk, h, b, set_card(m->base[b].presentes) - 1, m->base[b].lotacao);

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
    if (!(ev = cria_evento(m->relogio, EV_AVISA, h, dest_b)))
        fim_execucao("nao aloc func evento_sai");
    insere_lef(m->eventos, ev);
}
/*46101: VIAJA  HEROI 30 BASE 2 BASE 6 DIST 6922 VEL 4763 CHEGA 46102

%6d: VIAJA  HEROI %2d BASE %d BASE %d DIST %d VEL %d CHEGA %d*/
void evento_viaja(mundo_t *m, int clk, int h, int b)
{
    struct evento_t *ev;
    long dist;     // calcular a distancia que vai viajar e o tempo que vai demorar
    long duracao;  // tempo que vai demorar a viagem
    int id_origem; // id da base de origem

    testa_ponteiros(m);
    m->relogio = clk;

    id_origem = m->heroi[h].base_id;
    dist = calcula_distancia(m->base[id_origem].local, m->base[b].local);

    duracao = dist / m->heroi[h].velocidade;

    printf("%6.d: VIAJA  HEROI %2.d BASE %d BASE %d DIST %d VEL %d CHEGA %d", clk, h, m->heroi[h].base_id, b, dist, m->heroi[h].velocidade, clk + duracao);

    if (!(ev = cria_evento(m->relogio + duracao, EV_CHEGA, h, b)))
        fim_execucao("nao aloc func evento_viaja");
    insere_lef(m->eventos, ev);
}

/* 45952: MISSAO 3053 HAB REQ: [ 0 3 4 5 8 9 ]
 45952: MISSAO 3053 HAB BASE 3: [ 0 1 2 3 4 5 6 7 9 ]
 45952: MISSAO 3053 HAB BASE 6: [ 0 2 5 7 8 9 ]
 45952: MISSAO 3053 HAB BASE 4: [ 0 2 3 5 6 7 8 9 ]
 45952: MISSAO 3053 HAB BASE 0: [ 0 1 2 3 4 5 6 8 9 ]
 45952: MISSAO 3053 CUMPRIDA BASE 0 HEROIS: [ 8 11 16 18 23 24 39 ]
ou 
 45952: MISSAO 3053 IMPOSSIVEL

%6d: MISSAO %d HAB REQ: [ %d %d ... ]
%6d: MISSAO %d HAB BASE %d: [ %d %d ... ]
%6d: MISSAO %d CUMPRIDA BASE %d HEROIS: [ %d %d ... ]
%6d: MISSAO %d IMPOSSIVEL
Significado:

Linha “HAB REQ”: a missão 3053 requer as habilidades 0, 3, 4, 5, 8 e 9.
Linha “HAB BASE 3”: as habilidades conjuntas dos heróis da base 3 são 0, 1, 2, 3, 4, 5, 6, 7 e 9; as bases são listadas na ordem de distâncias crescentes do local da missão.
… (idem para as demais bases)
Linha “CUMPRIDA”: a missão 3053 foi cumprida pela equipe da base 0, composta pelos heróis 8, 11, 16, 18, 23, 24 e 39.
Linha “IMPOSSIVEL”: não foi encontrada equipe para cumprir a missão 3053 naquele momento e ela foi reagendada.*/
void evento_missao(mundo_t *m, int clk, int mis)
{
    struct evento_t *ev;
    struct set_t *uniao;
    int i, id_base;
    long dist, menor_dist;

    printf("%6.d: MISSAO %d HAB REQ: ", clk, mis);
    set_print(m->missao[mis].habil);

    testa_ponteiros(m);
    m->relogio = clk;

    m->missao[mis].tentativa++; // incrementa o numero de tentativas

    /*Calculo da distancia da base 0 até a missao*/
    menor_dist = calcula_distancia(m->base[0].local, m->base[mis].local);
    dist = menor_dist;
    /*Calculo da distancia da base i até a missao*/
    for (i = 1; i < m->n_bases; i++)
    {
        if (dist < menor_dist)
        {
            menor_dist = dist;
            id_base = i;
        }
        dist = calcula_distancia(m->base[i].local, m->base[mis].local);
    }

    if (!(uniao = set_create(N_HABILIDADES)))
        fim_execucao("set create in fun ev missao");

    /*1 - Heroi esta na base mais proxima,onde o id é: "id_base"
    **faço a uniao de todas as habilidades de todos os herois que estao na base.
    **2- ele vai de 0 ate o lotação do conjunto set_t presentes*/
    i = 0;
    while (i <= m->base[id_base].lotacao)
    {
        /*Pergunta se o heroi "i" esta contido no conjunto "presentes"*/
        if (set_in(m->base[id_base].presentes, i))
            if (!set_union(m->heroi[i].habil, uniao, uniao)) /*Se ele estiver contido faço a uniao de todas as habilidades de todos os herois*/
                fim_execucao("nao aloc func evento_missao");
        i++;
    }

    /* - Aqui ja chega salvo dentro da variavel "Uniao" a uniao de todos as
    habilidades dos herois que estavam dentro da base "id_base"*/
    /* - Verifica se as habilidades "uniao" contem "m->[mis].habil"*/
    if (set_contains(uniao, m->missao[mis].habil))
    {
        /*se estiver apto pra missao, ganha experiencia*/
        for (i = 0; i < m->base[id_base].lotacao; i++)
        {
            /*Pergunta se o heroi "i" esta contido no conjunto "presentes"*/
            if (set_in(m->base[id_base].presentes, i))
                m->heroi[i].experiencia += 10;
        }
    }
    /*se nao estiver apto pra missao adia*/
    else
    {
        m->n_miss_impos++; // incrementa o numero de missões impossiveis

        if (!(ev = cria_evento(m->relogio + (24 * 60), EV_MISSAO, mis, id_base)))
            fim_execucao("nao aloc func evento_missao");
        insere_lef(m->eventos, ev);
    }
}

void evento_fim(mundo_t *m)
{
    int m_compridas;  // missões cumpridas (missao total - missao impossivel)
    float media_tent; // media de tentativas por missão

    testa_ponteiros(m);

    for (int i = 0; i < m->n_herois; i++)
    {
        printf("HEROI %2.d PAC  %3.d", m->heroi[i].id, m->heroi[i].paciencia);
        printf(" VEL %4.d EXP %4.d HABS ", m->heroi[i].velocidade, m->heroi[i].experiencia);
        set_print(m->heroi[i].habil);
        printf("\n");
    }

    m_compridas = m->n_missoes - m->n_miss_impos;
    media_tent = m->n_missoes / m_compridas;
    /*5242/5256 MISSOES CUMPRIDAS (99.73%), MEDIA 2.09 TENTATIVAS/MISSAO*/

    printf("%d/%d MISSOES CUMPRIDAS (%.2f%%), ", m_compridas, m->n_missoes, media_tent);
    printf("MEDIA %.2f TENTATIVAS/MISSAO", media_missao(m));
}
