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
  srand(0);


  mundo = cria_mundo();
  struct evento_t *ev;
  ev_inicia(mundo);

  while (mundo->relogio < T_FIM_DO_MUNDO)
  {

    ev = retira_lef(retorna_eventos(mundo));
    atualiza_relogio(mundo, ev);


    switch (ev->tipo)
    {
    case EV_CHEGA:
      ev_chega(mundo, ev->tempo, ev->dado1, ev->dado2);
      break;

    case EV_ESPERA:
      ev_espera(mundo, ev->tempo, ev->dado1, ev->dado2);
      break;

    case EV_DESISTE:
      ev_desiste(mundo, ev->tempo, ev->dado1, ev->dado2);
      break;

    case EV_AVISA:
      ev_avisa(mundo, ev->tempo, ev->dado1, ev->dado2);
      break;

    case EV_ENTRA:
      ev_entra(mundo, ev->tempo, ev->dado1, ev->dado2);
      break;

    case EV_SAI:
      ev_sai(mundo, ev->tempo, ev->dado1, ev->dado2);
      break;

    case EV_VIAJA:
      ev_viaja(mundo, ev->tempo, ev->dado1, ev->dado2);
      break;

    case EV_MISSAO:
      ev_missao(mundo, ev->tempo, ev->dado1);
      break;
    case EV_FIM:
      ev_fim(mundo);
      break;

    default:
      break;
    }
    destroi_evento(ev);
  }

  destroi_mundo(mundo);

  return 0;
}
