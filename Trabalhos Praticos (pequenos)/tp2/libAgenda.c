/* 
 * Feito por Marcos Castilho em 06/04/2023
 * para a disciplina CI1001 - Programacao 1
 * obs.: a funcao obtemDiaDoAno foi feita
 * pelo prof. Andre Gregio.
 */

#include <stdio.h>
#include <time.h>
#include "libAgenda.h"

#define LIVRE 0
#define OCUPADA 1

int obtemDiaDoAno(struct data d){
    struct tm tipodata={0};
    time_t segundos;
    int dia_do_ano;

    tipodata.tm_mday = d.dia;
    tipodata.tm_mon = d.mes - 1;
    tipodata.tm_year = d.ano - 1900;
    tipodata.tm_isdst = -1;
    tipodata.tm_hour = 0;

    /* converte data para epoca, isto eh, segundos desde 1970 */
    segundos = mktime(&tipodata);

    /* converte epoca em data, obtendo assim automaticamente
     * o campo 'dia do ano' (tm_yday) que sera o indice do
     * vetor necessario para marcar um compromisso */
    tipodata = *localtime(&segundos);

    /* da reconversao da data, obtem o dia do ano, um numero
     * entre 0 e 364 */
    dia_do_ano = tipodata.tm_yday;

    return dia_do_ano;
}

/* Daqui para frente eh com voces! */
struct agenda criaAgenda(int ano){
    int dias, horas;
    struct agenda nova_ag;
    nova_ag.ano = ano;

    for (dias=0; dias<DIAS_DO_ANO; dias++) {
        for (horas=0; horas < HORAS_DO_DIA; horas++){
            nova_ag.agenda_do_ano[dias].horas[horas] = 0;
        }
    }
    return nova_ag;
}

int obtemHora(struct compromisso *compr){
    return compr->hora_compr;
}

int obtemAno(struct agenda *ag){
    return ag->ano;
}

int leCompromisso(struct agenda *ag, struct compromisso *compr){
    scanf("%d", &compr->data_compr.dia);
    scanf("%d", &compr->data_compr.mes);
    scanf("%d", &compr->data_compr.ano);
    scanf("%d", &compr->hora_compr);
   
    if(validaData(ag, &compr->data_compr) && validaHora(compr))  //se valido
        return 1;

    return 0;
}

int validaData(struct agenda *ag, struct data *d){
    int dias_mes[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    /* SEPAREI EM DOIS BLOCOS*/
	if ((d->dia > dias_mes[d->mes - 1]) || (d->dia <= 0) || (d->mes > 12))
        return 0;
    else if ((d->mes <= 0) || (obtemAno(ag) != d->ano))
        return 0;

    return 1;
}

int validaHora(struct compromisso *compr){
    if(compr->hora_compr<0 || compr->hora_compr>23)
        return 0;
    return 1;
}

int verificaDisponibilidade(struct agenda *ag, struct compromisso *compr){
    if (ag->agenda_do_ano[obtemDiaDoAno(compr->data_compr)].horas[compr->hora_compr]== OCUPADA)
        return 0;
    return 1;
}

void marcaCompromisso(struct agenda *ag, struct compromisso *compr){
    ag->agenda_do_ano[obtemDiaDoAno(compr->data_compr)].horas[obtemHora(compr)] = OCUPADA;
}

void listaCompromissos(struct agenda *ag){
    int dias, horas;

    for (dias=0; dias<DIAS_DO_ANO; dias++) {
        for (horas=0; horas < HORAS_DO_DIA; horas++){
            if (ag->agenda_do_ano[dias].horas[horas]== OCUPADA){
                printf ("dia: %3d, ", dias);
                printf ("ano: %4d, ", obtemAno (ag));
                printf ("hora: %2d, compromisso!\n", horas);
            }
        }
    }
}