#include<stdio.h>

typedef struct racional{
    int numerador;
    int denominador;
} racional; 

racional leRacional();
void imprimeFracionario(racional num_racional);

racional simplifica(racional num_racional);
racional somaRacional(racional num_racional1,racional num_racional2);
racional subtracaoRacional(racional num_racional1,racional num_racional2);
racional multiplicaRacional(racional num_racional1,racional num_racional2);
racional divisaoRacional(racional num_racional1,racional num_racional2);

int mdc(int numerador,int denominador);
int verificaRacional(racional num_racional);

int main(void)
{
    struct racional num_racional1;
    struct racional num_racional2;

    num_racional1 = leRacional();
    if(verificaRacional(num_racional1)){
        return -1;
    }
    num_racional2 = leRacional();
    if(verificaRacional(num_racional2)){
        return -1;
    }

    imprimeFracionario(somaRacional(num_racional1,num_racional2));
    imprimeFracionario(subtracaoRacional(num_racional1,num_racional2));
    imprimeFracionario(multiplicaRacional(num_racional1,num_racional2));
    imprimeFracionario(divisaoRacional(num_racional1,num_racional2));

    return 0;
}

racional leRacional(){
    struct racional tmp;
    scanf("%d",&tmp.numerador);
    scanf("%d",&tmp.denominador);
    return tmp;
}

void imprimeFracionario(racional num_racional){
    if (num_racional.numerador % num_racional.denominador == 0){
        printf("%d\n",num_racional.numerador / num_racional.denominador);

    }
    else{
        printf("%d/%d\n",num_racional.numerador,num_racional.denominador);

    }    
}

racional somaRacional(racional num_racional1,racional num_racional2){
    racional tmp;
    int aux,aux2;
    if(num_racional1.denominador == num_racional2.denominador){
        tmp.numerador = num_racional1.numerador + num_racional2.numerador;
        tmp.denominador = num_racional1.denominador;
    }
    else{
        aux = num_racional1.numerador * num_racional2.denominador;
        aux2 = num_racional2.numerador * num_racional1.denominador;
        tmp.numerador = aux + aux2;
        tmp.denominador = num_racional1.denominador * num_racional2.denominador;
    }
    return simplifica(tmp);
}

racional subtracaoRacional(racional num_racional1,racional num_racional2){
    racional tmp;
    int aux,aux2;
    if(num_racional1.denominador == num_racional2.denominador){
        tmp.numerador = num_racional1.numerador - num_racional2.numerador;
        tmp.denominador = num_racional1.denominador; 
    }else{
        aux = num_racional1.numerador * num_racional2.denominador;
        aux2 = num_racional2.numerador * num_racional1.denominador;
        tmp.numerador = aux - aux2;
        tmp.denominador = num_racional1.denominador * num_racional2.denominador;
    }
    return simplifica(tmp);
}

racional multiplicaRacional(racional num_racional1,racional num_racional2){ 
    racional tmp;
    tmp.numerador = num_racional1.numerador * num_racional2.numerador;
    tmp.denominador = num_racional1.denominador * num_racional2.denominador;

    return simplifica(tmp);
}

racional divisaoRacional(racional num_racional1,racional num_racional2){
    racional tmp;
    tmp.numerador = num_racional1.numerador * num_racional2.denominador;
    tmp.denominador = num_racional1.denominador * num_racional2.numerador;
    return simplifica(tmp);
}

racional simplifica(racional num_racional){
    int tmp = mdc(num_racional.numerador,num_racional.denominador);
    num_racional.numerador /= tmp;
    num_racional.denominador /= tmp;
    return num_racional;
    
}

int mdc(int numerador, int denominador){
    if (denominador == 0){
        return numerador;
    } 
    else{
        return mdc(denominador, numerador % denominador);
    }
}

int verificaRacional(racional sracionall){
    if(sracionall.denominador == 0){
        return 1;
    }
    else{
        return 0;
    }
}