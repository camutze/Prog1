#include <stdio.h>
#include <stdlib.h>
#define TAM 1024
void print_vet(int vet[], int n)
{
for(int i=0; i<n; i++){
        printf("%d ",vet [i]);
        
          }

}
void ler_vet(int vet[], int n){
    for(int i=0; i<n; i++){
        printf("Digite Vet[%d]: \n",i);
        scanf("%d",&vet[i]);
    }

}
void produto_vet(int vet[], int vet1[], int vet_x[], int n){
    for(int i=0; i<n; i++){
        vet_x[i]=vet1[i]*vet[i];
    }

}
int main()
{
    int n, vet[TAM], vet1[TAM],vet_x[TAM],cont, soma;
    printf("Digite n: \n");
    scanf("%d", &n);
    while(n>TAM){
        puts("Maior, digite novamente");
        printf("Digite n: \n");
        scanf("%d",&n);
    }
    printf("Digite os valores do VETOR 1:\n");
    ler_vet(vet, n);
    printf("Digite os valores do VETOR 2:\n");
    ler_vet(vet1, n);
    produto_vet(vet1,vet,vet_x,n);
    print_vet(vet_x,n);
    return 0;
} 