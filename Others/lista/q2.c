#include <stdlib.h>
#include <stdio.h>

int main()
{
    int n, cont, qdr;
    // ler
    printf("Digite 0 para sair\n");
    cont = 0;
    qdr = 1;
    do
    {
        scanf("%d", &n);
        // calcula de 2 em dois
        if (cont == 0) // caso seja o primeiro n, ele calcula o quadrado e avisa que vamos pro segundo
        {
            qdr = n * n;
            cont = 1;
        }
        else if (cont == 1) // aqui estamos no segundo numero, se ele nao for quadrado, cont == 3 cod de erro
        {
            if (cont == 3 || n != qdr)
                cont = 3;
            else
                cont = 0;
        }

    } while (n);

    if (cont == 3)
        printf("0\n");
    else
        printf("1\n");

    return 0;
}