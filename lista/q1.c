#include <stdio.h>
int main()
{
    int n, i, produto;

    do
    {
        printf("escreva um numero maior que 0\n");
        scanf("%d", &n);

    } while (n < 0);

    produto = 1;
    for (i = 0; produto < n; i++)
    {
        produto = i * (i + 1) * (i + 2);
    }

    if (produto == n)

        printf("1\n");

    else
    {
        printf("0\n");
    }

    return 0;
}