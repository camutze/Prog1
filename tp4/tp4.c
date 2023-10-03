#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "liblista.h"

void procura_e_imprime(lista_t *l, int elem);
void consulta_e_imprime(lista_t *l, int pos);

int main()
{
  lista_t *l;
  int pos, i;

  // cria uma lista L vazia
  if (!(l = lista_cria()))
    return 1;

  lista_imprime("LISTA", l);

  // insere no final de L os valores 10, 11, 12, 13 e 14, nessa ordem
  i = 10;
  do
  {
    lista_insere(l, i, -1);
    lista_imprime("LISTA", l);

    i++;
  } while (i < 15);
  lista_imprime("LISTA", l);

  // insere no início de L o valor 32 e 64
  lista_insere(l, 32, 0);
  lista_insere(l, 64, 0);
  lista_imprime("LISTA", l);

  // insere no meio de L o valor 103 e 47
  lista_insere(l, 103, lista_tamanho(l) / 2);
  lista_insere(l, 47, lista_tamanho(l) / 2);
  lista_imprime("LISTA", l);

  // para as posições início, 5, última e 100:
  consulta_e_imprime(l, 0);
  consulta_e_imprime(l, 5);
  consulta_e_imprime(l, -1);
  consulta_e_imprime(l, 100);

  // para os valores 5, 10 e 14:
  procura_e_imprime(l, 5);
  procura_e_imprime(l, 10);
  procura_e_imprime(l, 14);

  // para os valores 12, 103 e 79:
  lista_retira(l, &pos, 12);
  lista_retira(l, &pos, 103);
  lista_retira(l, &pos, 79);
  lista_imprime("LISTA", l);

  // enquanto L não estiver vazia
  while (lista_tamanho(l) > 0)
  {
    // retira o primeiro valor de L e o imprime
    lista_retira(l, &pos, 0);
    printf("Valor retirado da posicao %d\n", pos);
    // retira o último valor de L e o imprime
    lista_retira(l, &pos, -1);
    printf("Valor retirado da posicao %d\n", pos);
    // imprime L
    lista_imprime("LISTA", l);
  }

  lista_destroi(l);
}

void procura_e_imprime(lista_t *l, int elem)
{
  int i;
  i = lista_procura(l, elem);
  if (i != -1)
    printf("Valor %d encontrado na posição %d\n", elem, i);
  else
    printf("Valor %d não encontrado\n", elem);
}

void consulta_e_imprime(lista_t *l, int pos)
{
  int elem;
  if (lista_consulta(l, &elem, pos) != -1)
    printf("Valor na posicao %d: %d\n", pos, elem);
  else
    printf("Posição %d invalida\n", pos);
}