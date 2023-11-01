#include <stdlib.h>
#include <stdbool.h>

#include "set.h"
#include "lef.h"
#include "eventos.h"
#include "lista.h"
#include "simulador.h"

#define EV_CHEGA    0
#define EV_ESPERA   1
#define EV_DESISTE  2
...


struct eventos_e
{
    int tipo;
    int tempo;
    struct pontos_p *local;
};

long calcula_distancia(struct pontos_p *local, struct pontos_p *local_destino)
{
    long distancia;
    long x = (local_destino->x - local->x) * (local_destino->x - local->x);
    long y = (local_destino->y - local->y) * (local_destino->y - local->y);

    distancia = sqrt(x + y);

    return distancia;
}
/*Evento CHEGA
Representa um herói H chegando em uma base B no instante T. Ao chegar, o herói analisa o tamanho da fila e decide se espera para entrar ou desiste:

CHEGA (T, H, B):

atualiza base de H

se há vagas em B e a fila de espera está vazia:
    espera = true
senão:
    espera = (paciência de H) > (10 * tamanho da fila em B)

se espera:
    cria evento ESPERA (agora, H, B)
senão:
    cria evento DESISTE (agora, H, B)*/

void evento_chega(struct mundo_m *mundo, int tempo, int h, int b)
{
    bool espera;
    espera = 0;
    evento_t *ev ;

    mundo->herois[h]->base_id = b ;

    if (mundo->bases[b]->presentes->size < mundo->bases[base_pos]->lotacao && lista_vazia(mundo->bases[base_pos]->lista_espera))
        espera = true;
    else if (mundo->herois[heroi_pos]->paciencia > (10 * set_card(mundo->bases[base_pos]->lista_espera)))
        espera = true;
    else
        espera = false;

    /*Disparo de novos eventos*/
    if (espera)
        ev = cria_evento (mundo->tempo, EV_ESPERA, h, b);
        insere_lef (ev) ;
    else
        evento_desiste(tempo, mundo->herois[heroi_pos], mundo->bases[base_pos]);
    return 1;
}

/*
ESPERA (T, H, B):

adiciona H ao fim da fila de espera de B
cria evento AVISA (agora, B)*/

void evento_espera(int tempo, struct heroi_h *heroi, struct base_b *base)
{
    lista_insere(base->lista_espera, heroi->id, 0);
    evento_avisa(tempo, base);
}

/*DESISTE (T, H, B):

escolhe uma base destino D aleatória
cria evento VIAJA (agora, H, D)*/
void evento_desiste(struct mundo_m *mundo, int tempo, struct heroi_h *heroi, struct base_b *base)
{
    int destino_base_id;
    destino_base_id = gera_aleat(0, mundo->n_bases - 1);
    envento_viaja(tempo, heroi, mundo->bases[destino_base_id]);
}

/*AVISA (T, B):

enquanto houver vaga em B e houver heróis esperando na fila:
    retira primeiro herói (H') da fila de B
    adiciona H' ao conjunto de heróis presentes em B
    cria evento ENTRA (agora, H', B)*/
void evento_avisa(int tempo, struct base_b *base)
{
    int elem;
    while (base->presentes->size < base->lotacao && !lista_vazia(base->lista_espera))
    {
        int destino_base_id;

        /*ENTRA (T, H, B):

        calcula TPB = tempo de permanência na base:
            TPB = 15 + paciência de H * aleatório [1...20]
        cria evento SAI (agora + TPB, H, B)*/
        void evento_entra(struct mundo_m * m, int tempo, int id_heroi, struct base_b *base)
        {
            int tpb;
            tpb = 15 + m->herois[id_heroi]->paciencia * gera_aleat(1, 20);
            evento_sai(tempo + tpb, id_heroi, base); // arruma isso aqui ó doido
        }

        /*O herói H sai da base B. Ao sair, escolhe uma base de destino para viajar; o porteiro de B é avisado, pois uma vaga foi liberada:*/
        &mundo->bases[id_base_atual]->local, &base->local
                                                  evento_avisa(tempo, base);

        envento_viaja(tempo, id_heroi, mundo->bases[destino_base_id]);
    }
    /*VIAJA (T, H, D):

    calcula duração da viagem:
        distância = distância cartesiana entre a base atual de H e a base D
        duração = distância / velocidade de H
    cria evento CHEGA (agora + duração, H, D)*/
    void evento_viaja(struct mundo_m * mundo, int tempo, int id_heroi, struct base_b *base)
    {
        int id_base_atual;
        id_base_atual = mundo->herois[id_heroi]->base_id;

        int distancia;
        distancia = calcula_distancia(mundo->bases[id_base_atual]->local, base->local);
        int duracao;
        duracao = distancia / mundo->herois[id_heroi]->velocidade;
        evento_chega(tempo + duracao, id_heroi, base->id);
    }

    /*Evento MISSAO
    Uma missão M é disparada no instante T. São características de uma missão:

    Cada missão ocorre em um local aleatório e requer um conjunto aleatório de habilidades; ambos são definidos durante a inicialização.
    Cada equipe é formada pelo conjunto de heróis presentes em uma base.
    Uma equipe está apta para a missão se a união das habilidades de seus heróis contém as habilidades requeridas pela missão.
    Deve ser escolhida para a missão a equipe da base mais próxima ao local da missão e que esteja apta para ela.
    Ao completar uma missão, os heróis da equipe escolhida ganham pontos de experiência.
    Se uma missão não puder ser completada, ela é marcada como “impossível” e adiada de 24 horas.*/

    void evento_missao(struct mundo_m * mundo, int tempo, struct heroi_h *heroi, struct base_b *base)
    {
        // primeira distancia
        int menor_distancia = calcula_distancia(mundo->missoes[missao_pos]->local, mundo->bases[0]->local);
        for (int i = 1; i < mundo->n_bases; i++)
        {
            
            distancia = calcula_distancia(mundo->missoes[missao_pos]->local, mundo->bases[i]->local);
            if(distancia < menor_distancia)
            {
                menor_distancia = distancia;
                base_pos = i;
            }
        }
        /*PERGUNTAR*/
    }

    
