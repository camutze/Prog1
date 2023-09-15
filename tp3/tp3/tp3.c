#include <stdio.h>
#include <stdlib.h>
#include "racionais.h"

void imprime_vet(struct racional **r, int n);
void sem_invalido(struct racional **r, int *n);
void selection_sort(struct racional **r, int n);
void trocar(struct racional **r1, struct racional **r2);
void soma_tudo(struct racional **r, struct racional *soma, int n);
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

  for (int i = 0; i < n; i++)
  {
    scanf("%ld", &num);
    scanf("%ld", &den);

    if (!(r[i] = cria_r(num, den)))
      return 0;
    simplifica_r(r[i]);
  }
  imprime_vet(r, n);

  sem_invalido(r, &n);
  imprime_vet(r, n);

  selection_sort(r, n);
  imprime_vet(r, n);

  
  if (!(soma = cria_r(0, 1)))
    return 0;
  imprime_r(soma);
  // ok

   soma_tudo(r, soma, n);
   printf("SOMA = ");
   imprime_r(soma);

   printf("\n");

  // destroi_tudo(r, soma, n);

  /*

    ordene este vetor
    imprima o vetor ordenado
    calcule e imprima a soma de todos os racionais apontados pelo vetor
    libere toda a memória alocada
    - todos os racionais
    - o vetor de ponteiros
    - o espaço utilizado para fazer o cálculo da soma
    ao final, mude de linha
    retorne 0
  */
}

void imprime_vet(struct racional **r, int n)
{
  for (int i = 0; i < n; i++)
  {

    imprime_r(r[i]);
    printf(" ");
  }
  printf("\n");
}
void sem_invalido(struct racional **r, int *n)
{
  for (int i = 0; i < *n; i++)
  {
    if (!valido_r(r[i]))
    {
      while (!valido_r(r[*n - 1]))
      {
        free(r[*n - 1]);
        (*n)--;
        r[*n] = NULL;
      }

      if (r[i] && i< *n -2)
      {
        free(r[i]);

        r[i] = r[*n - 1];
        (*n)--;
      }
    }
  }
}

void trocar(struct racional **r1, struct racional **r2)
{
  struct racional *aux;
  aux = *r1;
  *r1 = *r2;
  *r2 = aux;
}

void selection_sort(struct racional **r, int n)
{

  if (!r)
    return;

  int i, j, menor;

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
void soma_tudo(struct racional **r, struct racional *soma, int n)
{
  if(!r)
    return;
  
  for (int i = 0; i < n; i++)
  {
    soma_r(soma, r[i], soma);
    
  }
}
int destroi_tudo(struct racional **r, struct racional *soma, int n)
{
  if (!r)
    return 0;
  if (soma)
    free(soma);
  for (int i = 0; i < n; i++)
  {
    if (r[i])
      free(r[i]);
  }
  free(r);
  return 1;
}