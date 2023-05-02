#include "libConfeitaria.h"

struct frigobar cria_frigobar(){
    struct frigobar consul;
    int i;
    
    i=0;
    do{
        if(i<CIMA)
            consul.p_cima[i]=0;
        if(i<BAIXO)
            consul.p_baixo[i]=0;

    }while(i<BAIXO || i<CIMA );
    return consul;
}

int posi_disponivel(struct frigobar *consul, int parte_de){
    int i;

    if(parte_de==CIMA){
        i = 0;
        do{
            if(consul->p_cima[i])
                return i; /*retorna posição disponível para alocar*/
            i++;       
        }while(i<CIMA);
    }
    else if (parte_de==BAIXO){
        i = 0;
        do{
            if(consul->p_baixo[i])
                return i; /*retorna posição disponível para alocar*/
            i++;
        }while(i<BAIXO);
        
    }

    return -1; /*nenhuma posição disponivel*/
}
void inserir_prateleira(struct frigobar *consul, int parte_de, int posi){
    if(parte_de == CIMA){
        struct bolodepote p;
        do{
            printf("c - Chocolate\n m - Morango\n");
            scanf("%c", &consul->p_cima[posi]->tipo);


    }while(consul->p_cima[posi]->tipo!='c' || consul->p_cima[posi]->tipo != 'm');

}
void cria_produto(struct frigobar *consul){
    int caso;

    printf("Digite para inserir:\n");
    printf("1 - Bolo de Pote - CIMA/n");
    printf("2- Tortinha - BAIXO/n");
    printf("0 - SAIR");

    scanf("%d", &caso);
    while (caso!=0){
        switch (caso)
        {
        case 1:            
            aloca_vetor(consul, CIMA);

            break;

        case 2:

            aloca_vetor(consul, BAIXO);
            break;

        case 0:
            exit(0);
             
        default:
            printf("Digite uma opção correta\n"); 
            
        }
         

    }
  
}

void aloca_vetor(struct frigobar *consul, int parte_de) {
    int posi;
    if (parte_de == CIMA) {
        posi = posi_disponivel(consul, CIMA);
        if (posi == -1) {
            printf("Sem espaço disponível EM CIMA\n");
            return;
        }
        consul->p_cima[posi] = malloc(sizeof(struct bolodepote));
        if (!consul->p_cima[posi]) {
            printf("Erro, IMPOSSÍVEL ALOCAR MEMÓRIA\n");
            return;
        }
    } else if (parte_de == BAIXO) {
        posi = posi_disponivel(consul, BAIXO);
        if (posi == -1) {
            printf("Sem espaço disponível EM BAIXO\n");
            return;
        }
        consul->p_baixo[posi] = malloc(sizeof(struct bolodepote));
        if (!consul->p_baixo[posi]) {
            printf("Erro, IMPOSSÍVEL ALOCAR MEMÓRIA\n");
            return;
        }
    } else {
        printf("Índice inválido\n");
        return;
    }
}

int lista_qtd(){
    return 0;

}

void destroi_vencido(struct frigobar *consul, int dia){
    dia++;
    consul->p_baixo[0]=0;



}

void destroi_figobar(struct frigobar *consul){
    int i;

    i=0;
    do{
        if(i<CIMA)
            free(consul->p_cima[i]);
        if(i<BAIXO)
            free(consul->p_baixo[i]);

    }while(i<BAIXO || i<CIMA );
}
