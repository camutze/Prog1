#include <stdio.h>

typedef struct {
    int numerador;
    int denominador;
} racional;
int mdc(int numerador, int denominador){                                        
    if (denominador == 0){                                                      
        return numerador;                                                       
    }                                                                           
    else{                                                                       
        return mdc(denominador, numerador % denominador);                       
    }                                                                           
}
racional simplifica(racional a)
{
    int tmp = mdc(a.numerador,a.denominador);             
    a.numerador /= tmp;                                              
    a.denominador /= tmp;                                            
    return a; 

}
/* le racional 1 */
racional le_racional (racional a)
{
    scanf("%d %d", &a.numerador, &a.denominador);
    return a;
}

// ===================================================


void imprime (racional s)
{
    printf("%d/%d\n", s.numerador, s.denominador);
}

// ===================================================

racional soma (racional s, racional s1)
{   
    racional so;
    so.numerador= (s.numerador*s1.denominador)+(s1.numerador*s.denominador);
    so.denominador= s.denominador* s1.denominador;
    return so;
}
// ===================================================

racional subtracao (racional s, racional s1)
{
    racional so;
    so.numerador= (s.numerador*s1.denominador)-(s1.numerador*s.denominador);
    so.denominador= s.denominador* s1.denominador;
    return so;
}

// ===================================================

racional multiplicacao (racional s, racional s1)
{
    racional so;
    so.numerador = s.numerador * s1.numerador;
    so.denominador = s.denominador * s1.denominador;
    return so;
}

// ===================================================

racional divisao (racional s, racional s1)
{
    racional so;
    so.numerador = s.numerador * s1.denominador;
    so.denominador = s.denominador * s1.numerador;
    return simplifica(so);
}

// ===================================================

int valido(racional s, racional s1)
{
    if(s.denominador!=0 && s1.denominador!=0){
        return 1;
    }
    return 0;

}


int main()
{
    racional a, b;
    a = le_racional (a);
    b = le_racional (b);
    while (valido(a,b)!=0)
    {
    

    imprime(soma(a, b));
    imprime(subtracao(a, b));
    imprime(multiplicacao(a, b));
    imprime(divisao(a, b));
    a = le_racional (a);
    b = le_racional (b);

    }
    
    
    
      
    
    return 0;
}