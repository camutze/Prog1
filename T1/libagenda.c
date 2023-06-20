#include "libagenda.h"
#include <stdlib.h>

agenda_t *cria_agenda()
{
    agenda_t *new_agenda;
    mes_t *new_mes;
    if (!(new_agenda = malloc(sizeof(agenda_t))))
        return 0;
    if (!(new_mes = malloc(sizeof(mes_t))))
        return 0;

    new_mes->mes = 1;
    new_mes->prox = new_mes;
    new_mes->ant = new_mes;
    new_mes->dias = NULL;

    new_agenda->mes_atual = 1;
    new_agenda->ptr_mes_atual = new_mes;
}

compromisso_t *cria_compromisso(horario_compromisso_t hc, int id, char *descricao)
{
    compromisso_t *new_comp;

    if (!(new_comp = malloc(sizeof(compromisso_t))))
        return 0;
    if (!(new_comp->descricao = malloc(sizeof(descricao + 1))))
        return 0;
    strcpy(new_comp->descricao, descricao);

    new_comp->inicio = hc.ini_h * 60 + hc.ini_m; /*Transformando tudo em minutos*/
    new_comp->fim = hc.fim_h * 60 + hc.fim_m;

    new_comp->prox = NULL;

    return 0;
}

void destroi_agenda(agenda_t *agenda)
{
    agenda_t *aux, *temp;

    /*Terminar depois*/
}

int marca_compromisso_agenda(agenda_t *agenda, int dia, compromisso_t *compr)
{
    dia_t *aux, *atual;
    if (agenda->ptr_mes_atual->dias == NULL)
    {
        if (!(agenda->ptr_mes_atual->dias = malloc((sizeof(dia_t)))))
            return 0;
        agenda->ptr_mes_atual->dias->dia = dia;
        agenda->ptr_mes_atual->dias->prox = NULL;
        agenda->ptr_mes_atual->dias->comprs = compr;
        return 1;
    }

    atual = agenda->ptr_mes_atual->dias;
    while (agenda->ptr_mes_atual->dias->prox != NULL && agenda->ptr_mes_atual->dias->dia < dia)
    {
        atual = atual->prox;
    }

    if (atual->prox == NULL) /* ele nao esta*/
    {
        if (!(atual->prox = malloc((sizeof(dia_t)))))
            return 0;
        atual->prox->prox = NULL;
        atual->prox->dia = dia;
        atual->prox->comprs = compr;
        return 1;
    }
    else
    {
        

    }

        return 9;
}

int desmarca_compromisso_agenda(agenda_t *agenda, int dia, compromisso_t *compr)
{
    return 0;
}

void imprime_agenda_mes(agenda_t *agenda)
{
}

int mes_atual_agenda(agenda_t *agenda)
{
    return 0;
}

void prim_mes_agenda(agenda_t *agenda)
{
}

int prox_mes_agenda(agenda_t *agenda)
{
    return 0;
}

int ant_mes_agenda(agenda_t *agenda)
{
    return 0;
}

compromisso_t *compr_agenda(agenda_t *agenda, int dia)
{
    return 0;
}

compromisso_t *prox_compr(compromisso_t *compr)
{
    return 0;
}

horario_compromisso_t hc_compr(compromisso_t *compr)
{
    return 0;
}

int id_compr(compromisso_t *compr)
{
    return 0;
}
char *descricao_compr(compromisso_t *compr)
{
    return '0';
}

void imprime_agenda_mes(agenda_t *agenda)
{
}

int insere_comp(agenda_t *ag, compromisso_t *compromisso)
{
}
