#include <stdio.h>
#define TAM 10

int main()
{
    int vet[TAM];
    if (ler(vet))
        printf("Erro ao ler\n");
    imprimir(vet);

    return 0;
}

int ler(int vet[])
{
    for (int i = 0; i < TAM; i++)
    {
        printf("digite vet[%d]:\n", i);
        scanf("%d", vet);
    }
}

void imprimir(int vet[])
{
    int i;
    for (i = 0; i < TAM - 1; i++)
    {
        printf("%d, ", vet[i]);
    }
    printf("%d.", vet[TAM - 1]);
    printf("\n");
}
void imprimir_inversp(int vet[])
{
    int i;
    for (i = TAM; i > 0; i--)
    {
        printf("%d, ", vet[i]);
    }
    printf("%d.", vet[0]);
    printf("\n");
}
