#include <stdio.h>

int main()
{
    int n, i, produto;

    do
    {
        printf("Digite o numero: \n");
        scanf("%d", &n);
    } while (n < 0);

    i = 1;
    produto = 1;
    do
    {
        produto = i * (i + 1) * (i + 2);
        i++;
    } while (produto < n);

    // Verifica se é Triangular
    if (produto == n)
    {
        printf("1\n");
    }
    else
    {
        printf("0\n");
    }

    return 0;
}
