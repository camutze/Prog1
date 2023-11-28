// programa principal do projeto "The Boys - 2023"
// Autor: Carlos Alberto Teixeira Mutzenberg, GRR: 20215520

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "lef.h"
#include "set.h"
#include "lista.h"

#include "simulador.h"
#include "eventos.h"


int main()
{
  struct mundo_t *mundo;
  struct evento_t *ev;

  mundo = cria_mundo();

  ev_inicia(mundo);

  while (mundo->relogio < T_FIM_DO_MUNDO)
  {

    ev = retira_lef(retorna_evento(mundo));
    atualiza_relogio(mundo, ev);

    ev_seleciona(mundo, ev);
    
    destroi_evento(ev);
  }

  destroi_mundo(mundo);

  return 0;
}
