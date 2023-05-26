#include "liblista_ordenada.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{

    lista_t *l;
    elemento_t elemento;
    if (!(l = lista_cria()))
    {
        printf("Erro ao criar Lista");
        return 0;
    }

    /*adicionar*/
    do
    {
        printf("Digite para inserir, ou -1 para sair\n");
        scanf("%d", &elemento.chave);
        if (!lista_insere_ordenado(l, &elemento))
        {
            printf("não inseriu\n");
            return 0;
        }
    

    } while (elemento.chave != -1);

    do
    {
        printf("Digite para remover, ou -1 para sair\n");
        scanf("%d", &elemento.chave);
        if (!lista_remove_ordenado(l, &elemento))
        {
            printf("não removeu\n");
            return 0;
        }

    } while (elemento.chave != -1);

    printf("destroi\n");
    lista_destroi(&l);
    return 1;
}
