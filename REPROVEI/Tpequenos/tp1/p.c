#include <stdio.h>
#include <math.h>
int main(){
    float a,b,c, delta, aux;
    scanf("%f %f %f",  &a,&b,&c);

    delta= (b*b) - 4 * a * c;
    if (delta<0) {
        puts("Não existe raiz");
    }
    else {
        delta = sqrt(delta);
        printf("X1= %f", aux);
    }
    aux= (-b +delta)/(2*a);
    printf("X1= %f", aux);
    aux= (-b -delta)/(2*a);
    printf("X2= %f", aux);
}
//teste 23/056
