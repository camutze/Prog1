// programa principal do projeto "The Boys - 2023"
// Autor: Carlos Alberto Teixeira Mutzenberg, GRR: 20215520

#include <stdio.h>
#include <stdlib.h>
#include "set.h"
#include "lef.h"
#include "simulador.h"

void testa_tudo();

int main()
{
  testa_tudo();
  return 0;
}

void testa_tudo()
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
  // struct base_b *b = cria_base(20);
  // b->id = 20;
  // b->local.x = 10;
  // b->local.y = 10;
  // b->lotacao = 10;
  // set_add(b->presentes, 2);
  // lista_insere(b->lista_espera, 1, -1);
  // lista_insere(b->lista_espera, 2, -1);
  // b = destroi_base(b);

  /* testando missão*/
  struct missao_m *m = cria_missao(15);
  m->id = 15;
  m->local.x = 10;
  m->local.y = 10;
  set_add(m->habil, 1);
  set_add(m->habil, 2);
  set_add(m->habil, 3);
  m = destroi_missao(m);

  /* testando mundo*/
  struct mundo_m *w = cria_mundo();
  w = destroi_mundo(w);
}