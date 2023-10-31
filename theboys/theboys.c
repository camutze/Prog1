// programa principal do projeto "The Boys - 2023"
// Autor: Carlos Alberto Teixeira Mutzenberg, GRR: 20215520

#include <stdio.h>
#include <stdlib.h>
#include "set.h"
#include "lef.h"
#include "simulador.h"

int main()
{
  /*testando heroi*/
  struct heroi_h *h = cria_um_heroi(10);
  h->experiencia = 10;
  h->paciencia = 10;
  h->velocidade = 10;
  set_add(h->habil, 1);
  set_add(h->habil, 2);
  set_add(h->habil, 3);
  set_add(h->habil, 4);
  set_add(h->habil, 5);
  h = destroi_um_heroi(h);

  /*Testando base*/
  struct base_b *b = cria_base(20);
  b->id = 20;
  b->local[0] = 10;
  b->local[1] = 10;
  b->lotacao = 10;
  set_add(b->presentes, 2);
  lista_insere(b->lista_espera, 1, -1);
  lista_insere(b->lista_espera, 2, -1);
  b = destroi_base(b);

  /* testando missão*/
  struct missao_m *m = cria_missao(15);
  m->id = 15;
  m->local[0] = 10;
  m->local[1] = 10;
  set_add(m->habil, 1);
  set_add(m->habil, 2);
  set_add(m->habil, 3);
  m = destroi_missao(m);

  /* testando mundo*/
  struct mundo_m *w = cria_mundo();
  w->bases[0] = 10;
  w->bases[1] = 10;
  w->herois[0] = 10;
  w->herois[1] = 10;
  w->missoes[0] = 10;
  w->missoes[1] = 10;
  w->n_bases = 10;
  w->n_herois = 10;
  w->n_missoes = 10;
  w->n_habil = 10;
  w->size_max = 10;
  w->relogio = 10;
  w = destroi_mundo(w);



  return (0);
}