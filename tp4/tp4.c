#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "liblista.h"

char *get_nome();

int main()
{
  lista_t *L;
  int elem, pos, i;
  char *nome;

  if (!(L = lista_cria()))
    return 1;
  nome = get_nome;
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
  
  
  // imprime L
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
  // destrói L
  // encerra
}

char *get_nome()
{
  char *nome;
  if ((nome = malloc(sizeof(char) * 24)) == NULL)
    return NULL;

  strcpy(nome, "Carlos A. T. Mutzenberg");
  return nome;
}