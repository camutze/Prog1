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

void evento_chega(mundo_t *m, int clk, int h, int b)
{
    struct evento_t *ev;
    bool espera;
    m->relogio = clk;

    m->heroi[h].base_id = b;
    /*se há vagas em B e a fila de espera está vazia:*/
    if (set_card(m->base[b].presentes) < m->base->lotacao && lista_vazia(m->base[b].lista_espera))
        espera = true;
    else
        /*Aqui se for maior TRUE, se for menor FALSE
        ******OPERACAO BOLEANA********/
        espera = (m->heroi[h].paciencia) > (10 * lista_tamanho(m->base->lista_espera));

    /*Disparo de novos eventos*/
    if (espera)
    {
        if (!(ev = cria_evento(m->relogio, EV_ESPERA, h, b)))
            fim_execucao("nao aloc func evento_chega");
        insere_lef(m->eventos, ev);
    }
    else if (!(ev = cria_evento(m->relogio, EV_DESISTE, h, b)))
        fim_execucao("nao aloc func evento_chega");
    insere_lef(m->eventos, ev);
}

void evento_espera(mundo_t *m, int clk, int h, int b)
{
    struct evento_t *ev;
    m->relogio = clk;

    /*adiciona H ao fim da fila de espera de B*/
    lista_insere(m->base[b].lista_espera, h, L_FIM);

    if (!(ev = cria_evento(m->relogio, EV_ESPERA, h, b)))
        fim_execucao("nao aloc func evento_espera");
    insere_lef(m->eventos, ev);
}

void evento_desiste(mundo_t *m, int clk, int h)
{
    struct evento_t *ev;
    int dest_b;
    m->relogio = clk;

    dest_b = gera_aleat(0, m->n_bases - 1);

    if (!(ev = cria_evento(m->relogio, EV_VIAJA, h, dest_b)))
        fim_execucao("nao aloc func evento_desiste");
    insere_lef(m->eventos, ev);
}

/*AVISA (T, B):

enquanto houver vaga em B e houver heróis enao sper fila:
    retira primeiro herói (H') da fila de B
    adiciona H' ao conjunto de heróis presentes em B
    cria evento ENTRA (agora, H', B)*/

void evento_avisa(mundo_t *m, int clk, int b)
{
    evento_t *ev;
    int h;
    m->relogio = clk;

    while ((set_card(m->base->presentes) < m->base->lotacao) && !lista_vazia(m->base->lista_espera))
    {
        lista_retira(m->base->lista_espera, &h, L_INICIO);
        set_add(m->base->presentes, h);

        if (!(ev = cria_evento(m->relogio, EV_ENTRA, h, b)))
            fim_execucao("nao aloc func evento_avisa");
        insere_lef(m->eventos, ev);
    }
}

void evento_entra(mundo_t *m, int clk, int h, int b)
{
    evento_t *ev;
    int tpb;
    m->relogio = clk;

    tpb = 15 + m->heroi[h].paciencia * gera_aleat(1, 20);

    m->relogio += tpb;
    // PERGUTAR, PODE? ev = cria_evento(m->relogio += tpb, EV_SAI, h, b);
    if (!(ev = cria_evento(m->relogio, EV_SAI, h, b)))
        fim_execucao("nao aloc func evento_entra");
    insere_lef(m->eventos, ev);
}

void evento_sai(mundo_t *m, int clk, int h, int b)
{
    evento_t *ev;
    int dest_b;

    m->relogio = clk;

    set_del(m->base[b].presentes, h);

    dest_b = gera_aleat(0, m->n_bases - 1);

    if (!(ev = cria_evento(m->relogio, EV_VIAJA, h, dest_b)))
        fim_execucao("nao aloc func evento_sai");
    insere_lef(m->eventos, ev);

    if (!(ev = cria_evento(m->relogio, EV_AVISA, h, dest_b)))
        fim_execucao("nao aloc func evento_sai");
    insere_lef(m->eventos, ev);
}

void evento_viaja(mundo_t *m, int clk, int h, int b)
{
    evento_t *ev;
    long dist;    // calcular a distancia que vai viajar e o tempo que vai demorar
    long duracao; // tempo que vai demorar a viagem
    int id_origem = m->heroi[h].base_id;

    m->relogio = clk;

    dist = calcula_distancia(m->base[id_origem].local, m->base[b].local);

    duracao = dist / m->heroi[h].velocidade;

    m->relogio += duracao;
    if (!(ev = cria_evento(m->relogio, EV_CHEGA, h, b)))
        fim_execucao("nao aloc func evento_viaja");
    insere_lef(m->eventos, ev);
}

/*Evento MISSAO
Uma missão M é disparada no instante T. São características de uma missão:


Ao completar uma missão, os heróis da equipe escolhida ganham pontos de experiência.
Se uma missão não puder ser completada, ela é marcada como “impossível” e adiada de 24 horas.*/

void evento_missao(mundo_t *m, int clk, int mis)
{
    evento_t *ev;
    struct set_t *uniao;
    int i, id_base;
    long dist, menor_dist;
    m->relogio = clk;

    /*Calculo da distancia da base 0 até a missao*/
    menor_dist = calcula_distancia(m->base[0].local, m->base[mis].local);
    dist = menor_dist;

    /*Calculo da base mais proxima*/
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
    /*Verifica se a base mais proxima tem a equipe apta para a missao*/
    // intesecçao entre as habilidades dos herois presentes na base id_base e as habilidades necessarias para a missao
    i = 0;
    while (i < m->base[id_base].lotacao)
    {
        // aqui eu vejo se o heroi esta na lista de presentes
        if (set_in(m->base[id_base].presentes, i))
            if (!set_union(m->heroi[i].habil, uniao, uniao)) // faço a uniao de todas as habilidades de todos os herois

                i++;
    }
    /*foi apto entao adiciona xp*/
    if (set_contains(uniao, m->missao[mis].habil))
    {
        for (i = 0; i < m->base[id_base].lotacao; i++)
        {
            if (set_in(m->base[id_base].presentes, i))
            {
                m->heroi[i].experiencia += 10;
            }
        }
    }
    /*se nao estiver apto pra missao adia*/
    else if (!(ev = cria_evento(m->relogio + (24 * 60), EV_MISSAO, mis, id_base)))
        fim_execucao("nao aloc func evento_missao");
    insere_lef(m->eventos, ev);
}

/*  apresenta as experiências dos heróis
  apresenta as estatísticas das missões
  encerra a simulação
  
  
  Evento FIM
O evento FIM encerra a simulação, gerando um relatório com informações sobre heróis e missões:

...
525600: FIM
HEROI  0 PAC  32 VEL 3879 EXP  441 HABS [ 5 ]
HEROI  1 PAC  52 VEL 2974 EXP  620 HABS [ 2 9 ]
HEROI  2 PAC  94 VEL 1480 EXP  581 HABS [ 0 6 9 ]
...
HEROI 48 PAC  39 VEL 1902 EXP  568 HABS [ 6 ]
HEROI 49 PAC  84 VEL  522 EXP  510 HABS [ 5 ]
5242/5256 MISSOES CUMPRIDAS (99.73%), MEDIA 2.09 TENTATIVAS/MISSAO

%6d: FIM
HEROI %2d PAC %3d VEL %4d EXP %4d HABS [ %d %d %d ... ]
%d/%d MISSOES CUMPRIDAS (%.2f%%), MEDIA %.2f TENTATIVAS/MISSAO
Significado:

O herói 0 tem paciência 32, velocidade 3879, experiência 441 e possui o conjunto de habilidades [ 5 ].
Foram cumpridas 5242 das 5256 missões geradas (99,73% de sucesso); cada missão foi agendada em média 2,09 vezes até ser cumprida*/
void evento_fim(mundo_t *m)
{
    long 
    printf("%d: FIM\n", m->relogio);
    for(int i = 0; i < m->n_herois; i++)

}