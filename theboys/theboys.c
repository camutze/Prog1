// programa principal do projeto "The Boys - 2023"
// Autor: Carlos Alberto Teixeira Mutzenberg, GRR: 20215520

#include <stdio.h>
#include <stdlib.h>
#include "set.h"
#include "lef.h"
#include "simulador.h"
#include "lista.h"
#include "eventos.h"

int main()
{
  struct mundo_t *mundo;
  struct evento_t *ev;

  mundo = cria_mundo();
  evento_inicia(mundo);

  while (retorna_relogio(mundo) < T_FIM_DO_MUNDO)
  {
    ev = retira_lef(retorna_eventos(mundo));

    switch (ev->tipo)
    {
    case EV_CHEGA:
      evento_chega(mundo, ev->tempo, ev->dado1, ev->dado2);
      break;

    case EV_ESPERA:
      evento_espera(mundo, ev->tempo, ev->dado1, ev->dado2);
      break;

    case EV_DESISTE:
      evento_desiste(mundo, ev->tempo, ev->dado1, ev->dado2);
      break;

    case EV_AVISA:
      evento_avisa(mundo, ev->tempo, ev->dado1, ev->dado2);
      break;

    case EV_ENTRA:
      evento_entra(mundo, ev->tempo, ev->dado1, ev->dado2);
      break;

    case EV_SAI:
      evento_sai(mundo, ev->tempo, ev->dado1, ev->dado2);
      break;

    case EV_VIAJA:
      evento_viaja(mundo, ev->tempo, ev->dado1, ev->dado2);
      break;

    case EV_MISSAO:
      evento_missao(mundo, ev->tempo, ev->dado1, ev->dado2);
      break;
    case EV_FIM:
      evento_fim(mundo);
      break;

    default:
      break;
    }
  }

#define EV_AVISA 4
#define EV_ENTRA 5
#define EV_SAI 6
#define EV_VIAJA 7
#define EV_MISSAO 8
#define EV_FIM 9

  destroi_mundo(mundo);
  return 0;
}
