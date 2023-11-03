#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "set.h"
#include "lef.h"
#include "lista.h"
#include "simulador.h"


/*Define Lista*/
#define L_FIM -1
#define L_INICIO 0
/*Tipos de enventos que vao entrar na lef:
NAO usar 0 ou -1 pois sao #defines da lista_t*/
#define EV_CHEGA 1
#define EV_ESPERA 2
#define EV_DESISTE 3
#define EV_AVISA 4
#define EV_ENTRA 5
#define EV_SAI 6
#define EV_VIAJA 7
#define EV_MISSAO 8


/*Representa um herói H chegando em uma base B no instante T*/
void evento_chega(mundo_t *m, int clk, int h, int b);

void evento_espera(mundo_t *m, int clk, int h, int b);

void evento_desiste(mundo_t *m, int clk, int h);

void evento_avisa(mundo_t *m, int clk, int b);

void evento_entra(mundo_t *m, int clk, int h, int b);

void evento_sai(mundo_t *m, int clk, int h, int b);

void evento_viaja(mundo_t *m, int clk, int h, int b);

void evento_missao(mundo_t *m, int clk, int b);









