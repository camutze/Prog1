#include <stdio.h>
#include "libAgenda.h"

int main()
{
    /* Variaveis*/
    int ano;
    char ctl;
    struct agenda ag;
    struct compromisso compr;

    /*Ponteiros*/
    struct agenda *pont_ag= &ag;
    struct compromisso *pont_compr= &compr;

    /*ler ano e cria agenda*/
    scanf("%d", &ano);
    ag = criaAgenda(ano);

    ctl= 'o';
    do
    {
        if(!leCompromisso(pont_ag,pont_compr)) // é zero?
            printf("Data e/ou hora invalidos, compromisso nao inserido\n");
        else if(verificaDisponibilidade(pont_ag,pont_compr)){ //é um?
                marcaCompromisso(pont_ag,pont_compr);
                printf("Compromisso inserido com sucesso!\n");
        }
        else
            printf("Data/Hora ocupada, compromisso nao inserido\n");
        scanf(" %c", &ctl);
    } while (ctl!='s');

    listaCompromissos(pont_ag);
    return 0;
}