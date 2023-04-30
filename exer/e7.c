#include <stdio.h>
#include <stdlib.h>
#define TAM 1024

typedef struct 
{
    int vet[TAM];
    int n;
}vetores;
//===============================================
//funções ------------------


vetores ler_n(vetores array); //ler tamanho do vetor
vetores ler_conteudo(vetores array);// ler e grava no vetor
void imprime_vet(vetores array);
int maior_elemento(vetores array);
//===============================================
//MAIN
//===============================================
int main()
{   
    vetores v;
    v = ler_n(v);
    v = ler_conteudo(v);
    imprime_vet(v);
    printf("%d", maior_elemento(v));
    return 0;
}

//======================================
int maior_elemento(vetores array)
{
    int maior=array.vet[0];
    for (int i = 0; i< array.n ; i++)
    {
        if(maior<array.vet[i])
            maior= array.vet[i];
    }
    
    return maior;

}
void imprime_vet(vetores array)
{
    for (int i = 0; i < array.n; i++)
    {
        printf("%d, ", array.vet[i]);
    }
    printf("\b\b.\n");

}
//===============================================
vetores ler_conteudo(vetores array)
{
    for (int i = 0; i < array.n; i++)
    {
        scanf("%d", &array.vet[i]);
    }
    return array;

}

//=============================================
vetores ler_n(vetores array)
{
    scanf("%d", &array.n);
    return array;
}

