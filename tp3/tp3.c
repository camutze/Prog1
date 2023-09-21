#include <stdio.h>
#include <stdlib.h>
#include "racionais.h"

/*Protótipos das Funções*/
void imprime_vet(struct racional **r, int n);
void sem_invalido(struct racional **r, int *n);
void trocar(struct racional **r1, struct racional **r2);
void selection_sort(struct racional **r, int n);
struct racional *soma_tudo(struct racional **r, int n);
int destroi_tudo(struct racional **r, struct racional *soma, int n);

int main()
{
  int n;
  long int num, den;
  struct racional **r, *soma;

  do
  {
    scanf("%d", &n);
  } while (n < 0 || n > 100);

  if (!(r = malloc(n * sizeof(struct racional *))))
    return 0;

  /* Ler os racionais, criar estruturas, simplifica e imprime*/
  for (int i = 0; i < n; i++)
  {
    scanf("%ld %ld", &num, &den);
    if (!(r[i] = cria_r(num, den)))
      return 0;

    simplifica_r(r[i]);
  }
  imprime_vet(r, n);

  /*retira os invalidos do vetor e imprime o resultado*/
  sem_invalido(r, &n);
  imprime_vet(r, n);

  /*Ordena e imprime*/
  selection_sort(r, n);
  imprime_vet(r, n);

  /*soma todos os elementos do vetor e imprime*/
  printf("SOMA = ");
  soma = soma_tudo(r, n);
  imprime_r(soma);

  printf("\n");

  /*Free em todo mundo*/
  destroi_tudo(r, soma, n);
  return 0;
}

/*imprime todos os dados do vetor*/
void imprime_vet(struct racional **r, int n)
{
  for (int i = 0; i < n; i++)
  {
    imprime_r(r[i]);
    printf(" ");
  }
  printf("\n");
}

/*Retira todos os invalidos e diminui vetor*/
void sem_invalido(struct racional **r, int *n)
{
  int tam, i;

  tam = 0;
  for (i = 0; i < *n; i++)
  {
    if (valido_r(r[i]))
    {
      r[tam] = r[i];
      tam++;
    }
    else
      free(r[i]);
  }
  *n = tam;
}

/*faz a troca de 2 racionais*/
void trocar(struct racional **r1, struct racional **r2)
{
  struct racional *aux;

  aux = *r1;
  *r1 = *r2;
  *r2 = aux;
}

/*ordena o vetor de n posições*/
void selection_sort(struct racional **r, int n)
{
  int i, j, menor;

  if (!r)
    return;

  for (i = 0; i < n - 1; i++)
  {
    menor = i;
    for (j = i + 1; j < n; j++)
    {
      if (compara_r(r[j], r[menor]) == -1)
      {
        menor = j;
      }
    }
    trocar(&r[i], &r[menor]);
  }
}

/*Soma todos os elementos do vetor*/
struct racional *soma_tudo(struct racional **r, int n)
{
  struct racional *soma, *incremento;

  if (!(soma = cria_r(0, 1)))
    return NULL;
  if (!(incremento = cria_r(0, 1)))
    return NULL;

  for (int i = 0; i < n; i++)
  {
    soma_r(soma, r[i], incremento);
    *soma = *incremento;
  }

  free(incremento);
  return soma;
}

/*Libera toda memoria alocada*/
int destroi_tudo(struct racional **r, struct racional *soma, int n)
{
  if (!r)
    return 0;

  if (soma)
    destroi_r(soma);

  for (int i = 0; i < n; i++)
  {
    if (r[i])
      destroi_r(r[i]);
  }

  free(r);
  return 1;
}