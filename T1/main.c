#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libagenda.h"

int main() {
    agenda_t* agenda = cria_agenda();
    
    // Criação de compromissos
    horario_compromisso_t hc1 = {9, 0, 10, 30};
    compromisso_t* c1 = cria_compromisso(hc1, 1, "Reunião");
    
    horario_compromisso_t hc2 = {14, 0, 15, 30};
    compromisso_t* c2 = cria_compromisso(hc2, 2, "Almoço");
    
    horario_compromisso_t hc3 = {16, 0, 17, 30};
    compromisso_t* c3 = cria_compromisso(hc3, 3, "Apresentação");
    
    // Marcação de compromissos na agenda
    marca_compromisso_agenda(agenda, 1, c1);
    marca_compromisso_agenda(agenda, 2, c2);
    marca_compromisso_agenda(agenda, 2, c3);
    
    // Impressão da agenda do mês atual
    printf("Agenda do mês %d:\n", mes_atual_agenda(agenda));
    imprime_agenda_mes(agenda);
    
    // Acesso aos compromissos de um dia específico
    int dia = 2;
    compromisso_t* compr = compr_agenda(agenda, dia);
    
    if (compr != NULL) {
        printf("Compromissos do dia %d:\n", dia);
        
        while (compr != NULL) {
            horario_compromisso_t hc = hc_compr(compr);
            printf("Hora de Início: %d:%02d, Hora de Fim: %d:%02d, ID: %d, Descrição: %s\n",
                   hc.ini_h, hc.ini_m, hc.fim_h, hc.fim_m, id_compr(compr), descricao_compr(compr));
            compr = prox_compr(compr);
        }
    } else {
        printf("Não há compromissos marcados para o dia %d.\n", dia);
    }
    
    // Desmarcação de um compromisso
    desmarca_compromisso_agenda(agenda, 2, c2);
    
    // Impressão da agenda atualizada
    printf("Agenda do mês %d após desmarcação do compromisso:\n", mes_atual_agenda(agenda));
    imprime_agenda_mes(agenda);
    
    destroi_agenda(agenda);
    
    return 0;
}
