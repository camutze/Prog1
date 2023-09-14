#include <stdio.h>
#include <stdlib.h>
#include "racionais.h"

void imprime_vet(struct racional **r, int n);
void sem_invalido(struct racional **r, int *n);
void selection_sort(struct racional **r, int n);
void trocar(struct racional *r1,struct racional *r2);
void soma_tudo(struct racional *r1,struct racional *r2,struct racional *r3);

int main()
{
  int n;
  long int num, den;
  struct racional **r;

  do
  {
    scanf("%d", &n);
  } while (n < 0 || n > 100);

  if (!(r = malloc(n * sizeof(r)))) //ver se ta certo
    return 0;

  for (int i = 0; i < n; i++)
  {
    scanf("%ld", &num);
    scanf("%ld", &den);

    if (!(r[i] = cria_r(num, den)))
      return 0;
  }

  imprime_vet(r, n);
  
  sem_invalido(r, &n);
  imprime_vet(r, n);

  selection_sort(r, n);
  imprime_vet(r, n);

  

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
        (*n)--;
      }
      r[i] = r[*n - 1];
      (*n)--;
    }
  }
}

void trocar(struct racional *r1,struct racional *r2)
{
    struct racional *aux;
    aux = r1;
    r1 = r2;
    r2 = aux;

}

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
    trocar(r[i], r[menor]);
  }
}
void soma_tudo(struct racional *r1,struct racional *r2,struct racional *r3)
{
  for(int i)
}