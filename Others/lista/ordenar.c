#include <stdio.h>
#define TAM 3
//gcc -Wall -Werror -Wextra -pedantic fonte.c -o executavel


int ler(int vet[])
{
    for (int i = 0; i < TAM; i++)
    {
        printf("digite vet[%d]:\n", i);
        scanf("%d", &vet[i]);
    }
    return 0;
}

void imprimir(int vet[])
{
    int i;
    for (i = 0; i < (TAM - 1); i++)
    {
        printf("%d, ", vet[i]);
    }
    printf("%d.", vet[TAM - 1]);
    printf("\n");
}

void imprimir_inverso(int vet[])
{
    int i;
    for (i = (TAM - 1); i > 0; i--)
    {
        printf("%d, ", vet[i]);
    }
    printf("%d.", vet[0]);
    printf("\n");
}

int main()
{
    int vet[TAM];
    if (ler(vet))
        printf("Erro ao ler\n");

    imprimir(vet);
    imprimir_inverso(vet);

    return 0;
}

int ordenar(int vet[])
{

}
