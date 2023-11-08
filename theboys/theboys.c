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
  struct evento_t *evento;

  mundo = cria_mundo();
  evento_inicia(mundo);

  while (relogio_mundo(mundo) < T_FIM_DO_MUNDO)
  {
    evento = retira_lef(mundo->eventos);
    
    switch ()
    {
    case /* constant-expression */:
      /* code */
      break;
    
    default:
      break;
    }
  }
  

  destroi_mundo(mundo);
  return 0;
}
