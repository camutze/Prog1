// programa principal do projeto "The Boys - 2023"
// Autor: Carlos Alberto Teixeira Mutzenberg, GRR: 20215520

#include <stdio.h>
#include <stdlib.h>
#include "set.h"
#include "lef.h"

// seus #defines vão aqui

// minimize o uso de variáveis globais

// programa principal
int main()
{

  struct set_t *s;
  s = set_create(10);
  set_add(s, 1);
  set_destroy(s);

  struct evento_t *e;
  e = cria_evento(1, 2, 3, 4);

  // criar a LEF
  struct lef_t *l;
  l = cria_lef();
  insere_lef(l, e);
  imprime_lef(l);

  destroi_lef(l);

  // iniciar o mundo

  // executar o laço de simulação

  // destruir o mundo

  return (0);
}
