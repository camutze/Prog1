/*Eventos feito por Carlos A. T. Mutzenberg
**GRR 20215520*/
#ifndef _EVENTOS_H
#define _EVENTOS_H

#include <math.h>

#include "lef.h"
#include "lista.h"
#include "set.h"
#include "simulador.h"
#include "eventos.h"

/*Define Lista*/
#define L_FIM -1
#define L_INICIO 0
/*Tipos de eventos que vao entrar na lef:
NAO usar 0 ou -1 pois sao #defines da lista_t*/
#define EV_CHEGA 1
#define EV_ESPERA 2
#define EV_DESISTE 3
#define EV_AVISA 4
#define EV_ENTRA 5
#define EV_SAI 6
#define EV_VIAJA 7
#define EV_MISSAO 8
#define EV_FIM 9

/*Função responsável por atualizar o relogio do mundo.*/
void atualiza_relogio(mundo_t *m, struct evento_t *ev);

/*Função responsável por tratar a chegada de um novo evento no mundo.*/
void ev_chega(mundo_t *m, int clk, int h, int b);

/*Função responsável por tratar a espera de um novo evento no mundo.*/
void ev_espera(mundo_t *m, int clk, int h, int b);

/*Função responsável por tratar a desistencia de um heroi .*/
void ev_desiste(mundo_t *m, int clk, int h, int b);

/*Função responsável por fazer a fila de espera andar se tiver vaga na base .*/
void ev_avisa(mundo_t *m, int clk, int h, int b);

/*Função responsável por tratar a entrada de um heroi na base .*/
void ev_entra(mundo_t *m, int clk, int h, int b);

/*Função responsável por tratar a saida de um heroi da base .*/
void ev_sai(mundo_t *m, int clk, int h, int b);

/*Função responsável por tratar a viagem de um heroi .*/
void ev_viaja(mundo_t *m, int clk, int h, int b);

/*Função responsável por tratar a missao de um heroi .*/
void ev_missao(mundo_t *m, int clk, int mis);

/*Função responsável por tratar o fim da simulação .*/
void ev_fim(mundo_t *m);

/*Função responsável por tratar o inicio da simulação .*/
void ev_inicia(mundo_t *m);

/*Função responsável por selecionar o evento que vai ser tratado .*/
void ev_seleciona(mundo_t *mundo ,struct evento_t *ev);

#endif