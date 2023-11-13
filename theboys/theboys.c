// programa principal do projeto "The Boys - 2023"
// Autor: Carlos Alberto Teixeira Mutzenberg, GRR: 20215520

#include <stdio.h>
#include <stdlib.h>

#include "lef.h"
#include "set.h"
#include "lista.h"

#include "simulador.h"
#include "eventos.h"

int main()
{
  struct mundo_t *mundo;

  mundo = cria_mundo();
  struct evento_t *ev;
  // set_add(mundo->base[0].presentes, 0);
  // set_add(mundo->base[0].presentes, 1);
  // lista_insere(mundo->base[0].lista_espera, 2, L_FIM);
  // lista_insere(mundo->base[0].lista_espera, 3, L_FIM);
  // lista_insere(mundo->base[0].lista_espera, 4, L_FIM);
  // lista_insere(mundo->base[0].lista_espera, 5, L_FIM);

  // evento_avisa(mundo, 14, 4, 0);

  // evento_desiste(mundo, 10, 0, 0);
  // imprime_lef(retorna_eventos(mundo));
  // evento_entra(mundo, 20, 2, 3);
  // evento_sai(mundo, 365, 2, 3);
  mundo->heroi[0].base_id = 0;
  evento_viaja(mundo, 4, 0, 5);
  imprime_lef(retorna_eventos(mundo));

  evento_inicia(mundo);

  /*
    while (mundo->relogio < T_FIM_DO_MUNDO)
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
        evento_missao(mundo, ev->tempo, ev->dado1);
        break;
      case EV_FIM:
        evento_fim(mundo);
        break;

      default:
        break;
      }
      destroi_evento(ev);

    }*/

  destroi_mundo(mundo);

  return 0;
}
// for (int i = 0; i < mundo->n_herois; i++)
// {
//   printf("Heroi %d %d %d",mundo->heroi[i].id, mundo->heroi[i].experiencia,
//   mundo->heroi[i].paciencia);
//   printf(" card habil: %d", set_card(mundo->heroi[i].habil));
//   set_print(mundo->heroi[i].habil);
//   printf("\n");
// }

// for (int i = 0; i < mundo->n_bases; i++)
// {
//   printf("Base %d %d %d", mundo->base[i].id, mundo->base[i].lotacao, set_card(mundo->base[i].presentes));

//   printf(" card habil: %d", set_card(mundo->base[i].presentes));
//   printf("\n");
// }
