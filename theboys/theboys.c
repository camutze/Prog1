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

  /*Cria e inicializa o mundo*/
  mundo = cria_mundo();
  ev_inicia(mundo);

  /*Enquanto o relogio do mundo nao chegar ao fim do mundo, continua a simulação*/
  while (mundo->relogio < T_FIM_DO_MUNDO)
  {
    /*Retira o primeiro evento da lista de eventos futuros*/
    ev = retira_lef(retorna_evento(mundo));
    atualiza_relogio(mundo, ev);
    /*Chama a função que trata o evento*/
    ev_seleciona(mundo, ev);
    /*Liberta a memoria do evento*/
    destroi_evento(ev);
  }

  destroi_mundo(mundo);

  return 0;
}
