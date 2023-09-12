#include <stdlib.h>
#include <stdio.h>

int *alocar_vet(int n);
int preencher_vet(int **v, int n);
void imprime_vet(int **v, int n);
int desalocar_tudo(int **v, int n)

    int main()
{
    int n, **v;

    printf("Digite n: \n");
    scanf("%d", &n);

    v = alocar_vet(n);

    if (!(preencher_vet(v, n)))
        printf("Erro ao prencher");

    free(v);

    return 0;
}

int *alocar_vet(int n)
{
    int **v;
    if (!(v = malloc(n * sizeof(int *))))
    {
        printf("Erro ao Alocar. Saindo.");
        abort();
    }

    for (int i = 0; i < n; i++)
    {
        if ((v[i] = malloc(sizeof(int))))
        {
            printf("Erro ao Alocar. Saindo.");
            abort();
        }
    }

    return v;
}
int preencher_vet(int **v, int n)
{
    if (!v)
        return 0;

    for (int i = 0; i < n; i++)
    {

        v[i] = 100 * i;
    }
}

void imprime_vet(int **v, int n)
{
    if (!v)
        return 0;
}

int desalocar_tudo(int **v, int n)
{
    if (!v)
        return 0;
}