#include <stdio.h>
#include "libAgenda.h"
int main()
{
  char entrada= '0';
  int cria_ano;
  struct agenda var_ag;
    struct compromisso var_compr;
    
    printf("Digite o ano:\n");
    scanf("%d", &cria_ano);
    var_ag=criaAgenda(cria_ano);
    //----------------------------------------------
    do
    {
      var_compr= leCompromisso();      
      if (validaData(var_compr.data_compr,var_ag)==0){ //se for falsa
          printf("Data invalida\n");
      }
      else if(verificaDisponibilidade(var_compr, var_ag)==0) {
        printf("Data Indisponivel na agenda\n");

      }
      else{
        var_ag= marcaCompromisso(var_ag,var_compr);//terminar essa parte
      }

      printf("Pressione qualquer tecla para continuar, ou s para sair\n");
      getchar();
      scanf("%c", &entrada); 
    } while (entrada !='s');
    //--------------------------------------------------

    listaCompromissos(var_ag);
    
    
       
    return 0;
}
