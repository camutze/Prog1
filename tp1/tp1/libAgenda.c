#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "libAgenda.h"
#define HORAS_DO_DIA 24
#define DIAS_DO_ANO 365

/* esta função transforma uma data lida pelo usuário para uma struct data
 * em uma data do tipo struct tm definida pela biblioteca time.h. 
 * Esta data é então transformada em segundos com a função mktime, para que
 * os outros membros da struct sejam preenchidos automaticamente, e então
 * reconvertida para uma data do tipo struct tm, reescrevendo a variável 
 * original. Com isso, pode-se obter o membro tm_yday, que representa o
 * dia do ano representado pela data: um inteiro entre 0 e 364 */
int obtemDiaDoAno(struct data d) {
	struct tm tipodata;
	time_t segundos;
	int dia_do_ano;

	tipodata.tm_mday = d.dia;
    tipodata.tm_mon = d.mes-1;
    tipodata.tm_year = d.ano-1900;
    tipodata.tm_isdst = -1;
	tipodata.tm_hour = 0;

	/* converte data para época, isto é, segundos desde 1970 */
	segundos = mktime(&tipodata);
	/* converte época em data, obtendo assim automaticamente
	 * o campo 'dia do ano' (tm_yday) que será o índice do
	 * vetor necessário para marcar um compromisso */
	tipodata = *localtime(&segundos);
	/* da reconversão da data, obtém o dia do ano, um número
	 * entre 0 e 364 */
    dia_do_ano = tipodata.tm_yday;
	
	return dia_do_ano;
}

/* DAQUI PARA BAIXO É COM VOCÊS! SIGAM O ENUNCIADO E O HEADER DISPONÍVEL */
struct agenda criaAgenda(int ano){
	struct agenda ag;
	ag.ano = ano;
	for (int dia = 0; dia < DIAS_DO_ANO; dia++){
		for (int hora = 0; hora < HORAS_DO_DIA; hora++)
		{
			ag.agenda_do_ano[dia].horas[hora] = 0;
		}
		
	}
	return ag;
}

struct compromisso leCompromisso(){
	struct compromisso compr;

        printf("Digite o dia do compromisso: ");
        scanf("%d", &compr.data_compr.dia);
        
        printf("Digite o mes do compromisso: ");
        scanf("%d", &compr.data_compr.mes);
        
        printf("Digite o ano do compromisso: ");
        scanf("%d", &compr.data_compr.ano);
        do
        {
            printf("Digite a hora do compromisso: entre 0 - 23 ");
            scanf("%d", &compr.hora_compr);

        } while ((compr.hora_compr<0) || (compr.hora_compr>23));
        
        
		return compr;
	
}
int validaData(struct data d, struct agenda ag){
	int dias_mes[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	
	if (((d.dia > dias_mes[d.mes - 1]) || (d.dia <= 0)) || ((d.mes > 12) || (d.mes <= 0)) || (obtemAno(ag) != d.ano)) return 0;

	return 1;
}
int verificaDisponibilidade(struct compromisso compr, struct agenda ag) {
	if (ag.agenda_do_ano[obtemDiaDoAno(compr.data_compr)].horas[obtemHora(compr)] == 1 ) return 0;

	return 1;

}
struct agenda marcaCompromisso(struct agenda ag, struct compromisso compr) {
	ag.agenda_do_ano[obtemDiaDoAno(compr.data_compr)].horas[obtemHora(compr)] = 1;
	
	return ag;
}

int obtemAno(struct agenda ag) {
	return ag.ano;
}
int obtemHora(struct compromisso compr) {
	return compr.hora_compr;
}
int obtemAno(struct agenda ag){
	return ag.ano;
	
}
//------------------------------------------
int validaData(struct data d, struct agenda ag){
	int dias_mes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if ((ag.ano != obtemAno(ag)) || ((d.mes-1 > 11) || (d.mes <= 0)) || (d.dia > dias_mes[d.mes]))
			return 0;
	return 1;
}
    

//------------------------------------------
int verificaDisponibilidade(struct compromisso compr, struct agenda ag){


	int dia_do_ano = obtemDiaDoAno(compr.data_compr); // obtém o dia do ano
    int hora = compr.hora_compr; // obtém a hora do compromisso
    
    // verifica se a hora já está ocupada na agenda
    if (ag.agenda_do_ano[dia_do_ano].horas[hora] == 1) {
        return 1; // hora ocupada
    }
    else {
        return 0; // hora livre
    }


}
//------------------------------------------

struct agenda marcaCompromisso(struct agenda ag, struct compromisso compr){
	for (int dia = 0; dia < DIAS_DO_ANO; dia++) {
			
        	for (int hora = 0; hora < HORAS_DO_DIA; hora++) {

            	if (ag.agenda_do_ano[dia].horas[hora] == 1) {
              
			    	printf("dia: %d, hora: %d, hora:%d, compromisso!\n", dia, ag.ano, hora);
				
				}
			}
		}

}
void listaCompromissos(struct agenda ag) {
	    for (int dia = 0; dia < DIAS_DO_ANO; dia++) {
			
        	for (int hora = 0; hora < HORAS_DO_DIA; hora++) {

            	if (ag.agenda_do_ano[dia].horas[hora] == 1) {
              
			    	printf("dia: %d, hora: %d, hora:%d, compromisso!\n", dia, ag.ano, hora);
				
				}
			}
		}
}