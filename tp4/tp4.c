#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "liblista.h"

void procura_e_imprime(lista_t *l, int elem);
void consulta_e_imprime(lista_t *l, int pos);
void retira_imprime(lista_t *l, int elem);

int main()
{
  lista_t *l;
  int i, elem;

  /*cria uma lista L vazia*/
  if (!(l = lista_cria()))
    return 1;

  lista_imprime("LISTA", l);

  /* insere no final de L os valores 10, 11, 12, 13 e 14, nessa ordem*/
  i = 10;
  do
  {
    lista_insere(l, i, -1);
    i++;
  } while (i < 15);
  lista_imprime("LISTA", l);

  /* insere no início de L o valor 32 e 64*/
  lista_insere(l, 32, 0);
  lista_insere(l, 64, 0);
  lista_imprime("LISTA", l);

  /* insere no meio de L o valor 103 e 47*/
  lista_insere(l, 103, lista_tamanho(l) / 2);
  lista_insere(l, 47, lista_tamanho(l) / 2);
  lista_imprime("LISTA", l);
  printf("\n");

  /* Imprime as posições início, 5, última e 100:*/
  consulta_e_imprime(l, 0);
  consulta_e_imprime(l, 5);
  consulta_e_imprime(l, -1);
  consulta_e_imprime(l, 100);
  printf("\n");

  /* para os valores 5, 10 e 14:*/
  procura_e_imprime(l, 5);
  procura_e_imprime(l, 10);
  procura_e_imprime(l, 14);
  printf("\n");

  /* para os valores 12, 103 e 79:*/
  retira_imprime(l, 12);
  retira_imprime(l, 103);
  retira_imprime(l, 79);

  printf("\n");

  /* enquanto L não estiver vazia,
  retira no inicio e no final e imprime
  o valor caso encontrado*/
  while (lista_tamanho(l) > 0)
  {
    printf("RETIRADO PRIMEIRO: ");
    if (lista_retira(l, &elem, 0) == -1)
      printf("NAO ENCONTRADO\n");
    else
      printf("%d\n", elem);

    printf("RETIRADO ULTIMO: ");
    if (lista_retira(l, &elem, -1) == -1)
      printf("NAO ENCONTRADO\n");
    else
      printf("%d\n", elem);

    lista_imprime("LISTA", l);

  }

  lista_destroi(l);
}
/*Informa a posicao e o valor do elemento
caso tenha encontrado*/
void consulta_e_imprime(lista_t *l, int pos)
{
  int elem;
  printf("VALOR NA POSICAO %d:", pos);
  if (lista_consulta(l, &elem, pos) == -1)
    printf(" NAO ENCONTRADO");
  else
    printf(" %d", elem);
  printf("\n");
}
/*Procura a posição onde o elemento esta
com a função lista procura, e remove caso tenha retornada uma 
posicao valida, caso contrario NAO ENCONTRADO*/
void procura_e_imprime(lista_t *l, int elem)
{
  int i;
  i = lista_procura(l, elem);
  printf("POSICAO DO VALOR %d:", elem);
  if (i != -1)
    printf(" %d", i);
  else
    printf(" NAO ENCONTRADO");
  printf("\n");
}

void retira_imprime(lista_t *l, int elem)
{
  int pos;
  pos = lista_procura(l, elem);
  printf("RETIRA VALOR %d ", elem);
  if (pos == -1)
    printf("NAO ENCONTRADO");
  else
  {
    lista_retira(l, &elem, pos);
    printf("DA POSICAO %d", pos);
  }

  printf("\n");
}