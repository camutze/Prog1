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
  struct mundo_t *w = cria_mundo();
  destroi_mundo(w);
  return 0;
}
