#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "liblista.h"

int get_nome(char *nome);

int main()
{
  lista_t *L;
  int elem, pos, i;
  char *nome;

  if (!(L = lista_cria()))
    return 1;

  if(!get_nome(nome))
    return 1;

  lista_imprime(nome, L);

  i = 10;
  while (i < 15)
  {
    lista_insere(L, i, -1);
    i++;
  }
  lista_imprime(nome, L);

  lista_insere(L, 32, 0);
  lista_insere(L, 64, 0);
  lista_imprime(nome, L);

  lista_insere(L, 103, 5);
  lista_insere(L, 47, 5);

  lista_imprime(nome, L);
  
  lista_retira(L, &elem, 0);

  // para as posições início, 5, última e 100:
  //   imprime o conteúdo da posição em L
  // fim para
  // para os valores 5, 10 e 14:
  //   imprime posição do valor em L
  // fim para
  // para os valores 12, 103 e 79:
  //   retira de L o elemento com o valor indicado, se estiver em L
  // fim para
  // imprime L
  // enquanto L não estiver vazia
  //   retira o primeiro valor de L e o imprime
  //   retira o último valor de L e o imprime
  // imprime L
  // fim enquanto

  free(nome);
  // destrói L
  // encerra
}

int get_nome(char *nome)
{
  if (!(nome = malloc(sizeof(char) * 24)))
    return 0;

  strcpy(nome, "Carlos A. T. Mutzenberg");
  nome[24] = '\0';
  return 1;
}