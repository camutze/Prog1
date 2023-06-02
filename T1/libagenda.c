#include "libagenda.h"
#include <stdlib.h>
#include <stdio.h>

agenda_t* cria_agenda() {
    agenda_t* nova_agenda = (agenda_t*)malloc(sizeof(agenda_t));
    nova_agenda->mes_atual = 1;
    nova_agenda->ptr_mes_atual = NULL;
    return nova_agenda;
}

compromisso_t* cria_compromisso(horario_compromisso_t hc, int id, char* descricao) {
    compromisso_t* novo_compromisso = (compromisso_t*)malloc(sizeof(compromisso_t));
    novo_compromisso->id = id;
    novo_compromisso->descricao = descricao;
    novo_compromisso->inicio = hc.ini_h * 60 + hc.ini_m;
    novo_compromisso->fim = hc.fim_h * 60 + hc.fim_m;
    novo_compromisso->prox = NULL;
    return novo_compromisso;
}

void destroi_agenda(agenda_t* agenda) {
    if (agenda == NULL)
        return;
    
    mes_t* mes_atual = agenda->ptr_mes_atual;
    while (mes_atual != NULL) {
        dia_t* dia_atual = mes_atual->dias;
        while (dia_atual != NULL) {
            compromisso_t* compr_atual = dia_atual->comprs;
            while (compr_atual != NULL) {
                compromisso_t* prox_compromisso = compr_atual->prox;
                free(compr_atual->descricao);
                free(compr_atual);
                compr_atual = prox_compromisso;
            }
            dia_t* prox_dia = dia_atual->prox;
            free(dia_atual);
            dia_atual = prox_dia;
        }
        mes_t* prox_mes = mes_atual->prox;
        free(mes_atual);
        mes_atual = prox_mes;
    }
    free(agenda);
}

int marca_compromisso_agenda(agenda_t* agenda, int dia, compromisso_t* compr) {
    mes_t* mes_atual = agenda->ptr_mes_atual;
    while (mes_atual != NULL && mes_atual->mes != agenda->mes_atual)
        mes_atual = mes_atual->prox;

    if (mes_atual == NULL)
        return 0; // Mês atual não encontrado na lista de meses

    dia_t* dia_atual = mes_atual->dias;
    while (dia_atual != NULL && dia_atual->dia != dia)
        dia_atual = dia_atual->prox;

    if (dia_atual == NULL)
        return 0; // Dia não encontrado na lista de dias

    if (dia_atual->comprs == NULL) {
        dia_atual->comprs = compr;
        return 1; // Sucesso ao marcar o compromisso (lista vazia)
    }

    compromisso_t* anterior = NULL;
    compromisso_t* atual = dia_atual->comprs;
    while (atual != NULL) {
        if (compr->fim <= atual->inicio) {
            compr->prox = atual;
            if (anterior != NULL)
                anterior->prox = compr;
            else
                dia_atual->comprs = compr;
            return 1; // Sucesso ao marcar o compromisso (interseção à esquerda ou início igual)
        } else if (compr->inicio >= atual->fim) {
            anterior = atual;
            atual = atual->prox;
        } else {
            return -1; // Interseção com outro compromisso
        }
    }

    anterior->prox = compr;
    return 1; // Sucesso ao marcar o compromisso (interseção à direita)
}

int desmarca_compromisso_agenda(agenda_t* agenda, int dia, compromisso_t* compr) {
    mes_t* mes_atual = agenda->ptr_mes_atual;
    while (mes_atual != NULL && mes_atual->mes != agenda->mes_atual)
        mes_atual = mes_atual->prox;

    if (mes_atual == NULL)
        return 0; // Mês atual não encontrado na lista de meses

    dia_t* dia_atual = mes_atual->dias;
    while (dia_atual != NULL && dia_atual->dia != dia)
        dia_atual = dia_atual->prox;

    if (dia_atual == NULL)
        return 0; // Dia não encontrado na lista de dias

    compromisso_t* anterior = NULL;
    compromisso_t* atual = dia_atual->comprs;
    while (atual != NULL) {
        if (atual == compr) {
            if (anterior != NULL)
                anterior->prox = atual->prox;
            else
                dia_atual->comprs = atual->prox;
            free(atual->descricao);
            free(atual);
            return 1; // Sucesso ao desmarcar o compromisso
        }
        anterior = atual;
        atual = atual->prox;
    }

    return 0; // Compromisso não encontrado
}

void imprime_agenda_mes(agenda_t* agenda) {
    mes_t* mes_atual = agenda->ptr_mes_atual;
    while (mes_atual != NULL && mes_atual->mes != agenda->mes_atual)
        mes_atual = mes_atual->prox;

    if (mes_atual == NULL) {
        printf("Mês atual não encontrado na lista de meses.\n");
        return;
    }

    dia_t* dia_atual = mes_atual->dias;
    while (dia_atual != NULL) {
        compromisso_t* compr_atual = dia_atual->comprs;
        while (compr_atual != NULL) {
            horario_compromisso_t hc = hc_compr(compr_atual);
            printf("Dia: %d, Início: %02d:%02d, Fim: %02d:%02d, ID: %d, Descrição: %s\n",
                   dia_atual->dia, hc.ini_h, hc.ini_m, hc.fim_h, hc.fim_m,
                   id_compr(compr_atual), descricao_compr(compr_atual));
            compr_atual = prox_compr(compr_atual);
        }
        dia_atual = dia_atual->prox;
    }
}

int mes_atual_agenda(agenda_t* agenda) {
    return agenda->mes_atual;
}

void prim_mes_agenda(agenda_t* agenda) {
    agenda->mes_atual = 1;
    agenda->ptr_mes_atual = NULL;
}

int prox_mes_agenda(agenda_t* agenda) {
    if (agenda->mes_atual == 12)
        return 0; // Não é possível avançar além do mês 12

    mes_t* mes_atual = agenda->ptr_mes_atual;
    while (mes_atual != NULL && mes_atual->mes != agenda->mes_atual)
        mes_atual = mes_atual->prox;

    if (mes_atual != NULL) {
        agenda->mes_atual++;
        agenda->ptr_mes_atual = mes_atual->prox;
        return agenda->mes_atual;
    } else {
        mes_t* novo_mes = (mes_t*)malloc(sizeof(mes_t));
        novo_mes->mes = agenda->mes_atual + 1;
        novo_mes->dias = NULL;
        novo_mes->prox = NULL;

        if (agenda->ptr_mes_atual == NULL) {
            agenda->ptr_mes_atual = novo_mes;
        } else {
            mes_t* temp = agenda->ptr_mes_atual;
            while (temp->prox != NULL)
                temp = temp->prox;
            temp->prox = novo_mes;
            novo_mes->ant = temp;
        }

        agenda->mes_atual++;
        agenda->ptr_mes_atual = novo_mes;
        return agenda->mes_atual;
    }
}

int ant_mes_agenda(agenda_t* agenda) {
    if (agenda->mes_atual == 1)
        return 0; // Não é possível retroceder antes do mês 1

    mes_t* mes_atual = agenda->ptr_mes_atual;
    while (mes_atual != NULL && mes_atual->mes != agenda->mes_atual)
        mes_atual = mes_atual->prox;

    if (mes_atual != NULL) {
        agenda->mes_atual--;
        agenda->ptr_mes_atual = mes_atual->ant;
        return agenda->mes_atual;
    } else {
        mes_t* novo_mes = (mes_t*)malloc(sizeof(mes_t));
        novo_mes->mes = agenda->mes_atual - 1;
        novo_mes->dias = NULL;
        novo_mes->prox = agenda->ptr_mes_atual;
        novo_mes->ant = NULL;

        agenda->mes_atual--;
        agenda->ptr_mes_atual = novo_mes;
        return agenda->mes_atual;
    }
}

compromisso_t* compr_agenda(agenda_t* agenda, int dia) {
    mes_t* mes_atual = agenda->ptr_mes_atual;
    while (mes_atual != NULL && mes_atual->mes != agenda->mes_atual)
        mes_atual = mes_atual->prox;

    if (mes_atual == NULL)
        return NULL; // Mês atual não encontrado na lista de meses

    dia_t* dia_atual = mes_atual->dias;
    while (dia_atual != NULL && dia_atual->dia != dia)
        dia_atual = dia_atual->prox;

    if (dia_atual == NULL)
        return NULL; // Dia não encontrado na lista de dias

    return dia_atual->comprs;
}

compromisso_t* prox_compr(compromisso_t* compr) {
    return compr->prox;
}

horario_compromisso_t hc_compr(compromisso_t* compr) {
    horario_compromisso_t hc;
    hc.ini_h = compr->inicio / 60;
    hc.ini_m = compr->inicio % 60;
    hc.fim_h = compr->fim / 60;
    hc.fim_m = compr->fim % 60;
    return hc;
}

int id_compr(compromisso_t* compr) {
    return compr->id;
}

char* descricao_compr(compromisso_t* compr) {
    return compr->descricao;
}
