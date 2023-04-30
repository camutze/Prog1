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
    else{
        return -1; /*nenhuma posição disponivel*/
    }
    

    
    
}


void cria_produto(struct frigobar *consul){
    int caso, indice;

    printf("Digite para inserir:\n");
    printf("1 - Bolo de Pote - CIMA/n");
    printf("2- Tortinha - BAIXO/n");
    printf("0 - SAIR");

    scanf("%d", &caso);
    while (caso!=0){
        switch (caso)
        {
        case 1:
            /*Verica posição disponivel para bolo de pote*/
            indice= posi_disponivel(consul, CIMA);

            if(indice!= -1){
                printf("Sem espaço disponivel EM CIMA");
                return;
            }
            
            consul->p_cima[indice]= malloc(sizeof(struct bolodepote));

            if(consul->p_cima[indice]){
                printf("Erro, IMPOSSIVEL ALOCAR MEMÓRIA");
                return;
            }

            break;

        case 2:
            /*Verica posição disponivel parte de baixo*/
            indice= posi_disponivel(consul, BAIXO);
            if(indice!= -1){
                printf("Sem espaço disponivel EM BAIXO");
                return;
            }

            consul->p_baixo[indice]= malloc(sizeof(struct bolodepote));

            if(consul->p_baixo[indice]){
                printf("Erro, IMPOSSIVEL ALOCAR MEMÓRIA");
                return;
            }

            break;

        case 0:
            break;
    
        default:
            printf("Digite uma opção correta");      
            break;
        }
         

    }
  
   
    
    return consul;
}

struct frigobar aloca_vetor(struct frigobar *consul, int index){

}

int lista_qtd(){

}

void destroi_vencido(){

}

void destroi_figobar(struct frigobar consul){
    int up, donw;

    up=0;
    donw=0;
    do{
        if(up<CIMA){
            consul.p_cima[up]=0;
            up++;
        }
        if(donw<BAIXO){
            consul.p_baixo[donw]=0;
            donw++;
        }

    }while(up!=CIMA || donw!= BAIXO );
    return consul;

}
