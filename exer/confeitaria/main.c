#include "libConfeitaria.h"


int main()
{   
    int i;
    struct frigobar consul;
    //aloca_vetor(&consul, CIMA);
    cria_frigobar(&consul);
    i=0;
    do{


    cria_produto(&consul);
    i++;

    }while (i<7);
    return 0;
}

