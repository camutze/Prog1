#include <stdio.h>
#include <stdlib.h>
#define TAM 1024

int main()
{
    int n, vet[TAM];
    printf("Digite n: \n");
    scanf("%d", &n);
    while(n>TAM){
        puts("Maior, digite novamente");
        printf("Digite n: \n");
        scanf("%d",&n);
    }
    for(int i=0; i<n; i++){
        vet[i]=i;
    }
    for(int i=0; i<n; i++){
        printf("%d /n",vet[i]);
    }
    
    return 0;
}