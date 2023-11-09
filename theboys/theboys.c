// programa principal do projeto "The Boys - 2023"
// Autor: Carlos Alberto Teixeira Mutzenberg, GRR: 20215520

#include <stdio.h>
#include <stdlib.h>

#include "simulador.h"
#include "eventos.h"

void imprime_herois_mundo(struct mundo_t *m)
{
  struct heroi_t *herois = m->heroi;

  if (m)
  {

    for (int i = 0; i < m->n_herois; i++)
    {
      printf("Herói %d:\n", herois[i].id);
      printf("Paciência: %d\n", herois[i].paciencia);
      printf("Velocidade: %d\n", herois[i].velocidade);
      printf("Experiência: %d\n", herois[i].experiencia);
      printf("Habilidades do Herói:\n");
      set_print(herois[i].habil);
      printf("\n");
    }
  }
}

void imprime_bases_mundo(struct mundo_t *m)
{
  if (m)
  {
    for (int i = 0; i < m->n_bases; i++)
    {
      struct base_t *bases = m->base;
      {
        printf("Base %d:\n", bases[i].id);
        printf("Lotação: %d\n", bases[i].lotacao);
        printf("Localização: (%d, %d)\n", bases[i].local.x, bases[i].local.y);
        printf("Heróis Presentes na Base:\n");
        set_print(bases->presentes);
        printf("Heróis na Fila de Espera:\n");
        lista_imprime("FILA", bases->lista_espera);
        printf("\n");
      }
    }
  }
}

void imprime_missoes_mundo(struct mundo_t *m)
{
  if (m)
  {
    for (int i = 0; i < m->n_missoes; i++)
    {
      struct missao_t *missoes = m->missao;

      printf("Missão %d:\n", missoes[i].id);
      printf("Localização da Missão: (%d, %d)\n", missoes[i].local.x, missoes[i].local.y);
      printf("Habilidades Necessárias:\n");
      set_print(missoes[i].habil);
      printf("\n");
    }
  }
}

int main()
{
  struct mundo_t *mundo;
  //struct eventos_t *ev;

  mundo = cria_mundo();
  evento_inicia(mundo);
  //imprime_herois_mundo(mundo);
  // imprime_bases_mundo(mundo);
  //imprime_missoes_mundo(mundo);
  
  /*
  while (retorna_relogio(mundo) < T_FIM_DO_MUNDO)
  {
    ev = retira_lef(retorna_eventos(mundo));
    printf("\n");

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
  */
 imprime_lef(mundo->eventos);
  destroi_mundo(mundo);
  return 0;
}
