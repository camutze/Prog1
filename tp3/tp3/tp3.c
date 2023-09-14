#include <stdio.h>
#include <stdlib.h>
#include "racionais.h"

void imprime_vet(struct racional **r, int n);
void sem_invalido(struct racional **r, int *n);

int main()
{
  int n;
  long int num, den;
  struct racional **r;

  do
  {
    scanf("%d", &n);
  } while (n < 0 || n > 100);

  if (!(r = malloc(n * sizeof(r))))
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

void trocar(int *a, int *b)
{
  int t = *a;
  *a = *b;
  *b = t;
}

int particionar(int v[], int baixo, int alto)
{
  int pivo = v[alto];
  int i = (baixo - 1);

  for (int j = baixo; j <= alto - 1; j++)
  {
    if (v[j] < pivo)
    {
      i++;
      trocar(v[i], v[j]);
    }
  }

  trocar(&v[i + 1], &v[alto]);
  return (i + 1);
}

void ordenar_quick(int **v, int baixo, int alto)
{
  if (baixo < alto)
  {
    int pi = particionar(v, baixo, alto);

    ordenar_quick(v, baixo, pi - 1);
    ordenar_quick(v, pi + 1, alto);
  }
}