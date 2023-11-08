/*Eventos feito por Carlos A. T. Mutzenberg
**GRR 20215520*/
#ifndef _EVENTOS_H
#define _EVENTOS_H

#include "simulador.h"

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

/*Retorna a distancia entre duas coordenadas*/
long calcula_distancia(struct pontos_t loc, struct pontos_t next_loc);

/*Testa se os elementos alocados dentro de mundo estao ok, incluso o mundo
caso não estiver ok, finaliza a execução*/
void testa_ponteiros(mundo_t *m);

/*Calcula a média de tentativas para uma missão em um mundo dado.*/
float media_missao(mundo_t *m);

/*Retorna a uniao de todas as habilidades de todos os herois que estao na base*/
struct set_t *uniao_habilidades(mundo_t *m, int id_base);

/*Função responsável por tratar a chegada de um novo evento no mundo.*/
void evento_chega(mundo_t *m, int clk, int h, int b);

/*Função responsável por tratar a espera de um novo evento no mundo.*/
void evento_espera(mundo_t *m, int clk, int h, int b);

/*Função responsável por tratar a desistencia de um heroi .*/
void evento_desiste(mundo_t *m, int clk, int h, int b);

/*Função responsável por fazer a fila de espera andar se tiver vaga na base .*/
void evento_avisa(mundo_t *m, int clk, int h, int b);

/*Função responsável por tratar a entrada de um heroi na base .*/
void evento_entra(mundo_t *m, int clk, int h, int b);

/*Função responsável por tratar a saida de um heroi da base .*/
void evento_sai(mundo_t *m, int clk, int h, int b);

/*Função responsável por tratar a viagem de um heroi .*/
void evento_viaja(mundo_t *m, int clk, int h, int b);

/*Função responsável por tratar a missao de um heroi .*/
void evento_missao(mundo_t *m, int clk, int mis);

/*Função responsável por tratar o fim da simulação .*/
void evento_fim(mundo_t *m);

/*Função responsável por tratar o inicio da simulação .*/
void evento_inicia(mundo_t *m);

#endif