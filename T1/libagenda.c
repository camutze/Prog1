#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libagenda.h"

agenda_t* cria_agenda() {
	agenda_t* agenda = (agenda_t*)malloc(sizeof(agenda_t));
	if (agenda == NULL) {
		return NULL;
	}

	agenda->ptr_mes_atual = NULL;
	agenda->mes_atual = 1;

	return agenda;
}

compromisso_t* cria_compromisso(horario_compromisso_t hc, int id, char* descricao) {
	compromisso_t* compromisso = (compromisso_t*)malloc(sizeof(compromisso_t));
	if (compromisso == NULL) {
		return NULL;
	}

	compromisso->id = id;
	compromisso->descricao = strdup(descricao);
	compromisso->inicio = hc.ini_h * 60 + hc.ini_m;
	compromisso->fim = hc.fim_h * 60 + hc.fim_m;
	compromisso->prox = NULL;

	return compromisso;
}

void destroi_agenda(agenda_t* agenda) {
	if (agenda == NULL) {
		return;
	}

	mes_t* mes_atual = agenda->ptr_mes_atual;
	while (mes_atual != NULL) {
		dia_t* dia_atual = mes_atual->dias;
		while (dia_atual != NULL) {
			compromisso_t* compromisso_atual = dia_atual->comprs;
			while (compromisso_atual != NULL) {
				compromisso_t* prox_compromisso = compromisso_atual->prox;
				free(compromisso_atual->descricao);
				free(compromisso_atual);
				compromisso_atual = prox_compromisso;
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
	if (agenda == NULL || compr == NULL) {
		return 0;
	}

	mes_t* mes_atual = agenda->ptr_mes_atual;
	while (mes_atual != NULL) {
		if (mes_atual->mes == agenda->mes_atual) {
			dia_t* dia_atual = mes_atual->dias;
			while (dia_atual != NULL) {
				if (dia_atual->dia == dia) {
					compromisso_t* compromisso_anterior = NULL;
					compromisso_t* compromisso_atual = dia_atual->comprs;

					while (compromisso_atual != NULL && compr->inicio > compromisso_atual->inicio) {
						compromisso_anterior = compromisso_atual;
						compromisso_atual = compromisso_atual->prox;
					}

					if (compromisso_atual != NULL && compr->fim > compromisso_atual->inicio) {
						return -1; // Compromisso tem interseção com outro
					}

					if (compromisso_anterior != NULL) {
						compromisso_anterior->prox = compr;
					} else {
						dia_atual->comprs = compr;
					}

					compr->prox = compromisso_atual;
					return 1; // Sucesso
				}
				dia_atual = dia_atual->prox;
			}
			break;
		}
		mes_atual = mes_atual->prox;
	}

	return 0;
}

int desmarca_compromisso_agenda(agenda_t* agenda, int dia, compromisso_t* compr) {
	if (agenda == NULL || compr == NULL) {
		return 0;
	}

	mes_t* mes_atual = agenda->ptr_mes_atual;
	while (mes_atual != NULL) {
		if (mes_atual->mes == agenda->mes_atual) {
			dia_t* dia_atual = mes_atual->dias;
			while (dia_atual != NULL) {
				if (dia_atual->dia == dia) {
					compromisso_t* compromisso_anterior = NULL;
					compromisso_t* compromisso_atual = dia_atual->comprs;

					while (compromisso_atual != NULL && compromisso_atual != compr) {
						compromisso_anterior = compromisso_atual;
						compromisso_atual = compromisso_atual->prox;
					}

					if (compromisso_atual != NULL) {
						if (compromisso_anterior != NULL) {
							compromisso_anterior->prox = compromisso_atual->prox;
						} else {
							dia_atual->comprs = compromisso_atual->prox;
						}

						free(compromisso_atual->descricao);
						free(compromisso_atual);
						return 1; // Sucesso
					}
				}
				dia_atual = dia_atual->prox;
			}
			break;
		}
		mes_atual = mes_atual->prox;
	}

	return 0;
}

void imprime_agenda_mes(agenda_t* agenda) {
	if (agenda == NULL) {
		return;
	}

	mes_t* mes_atual = agenda->ptr_mes_atual;
	while (mes_atual != NULL) {
		if (mes_atual->mes == agenda->mes_atual) {
			dia_t* dia_atual = mes_atual->dias;
			while (dia_atual != NULL) {
				compromisso_t* compromisso_atual = dia_atual->comprs;
				while (compromisso_atual != NULL) {
					horario_compromisso_t hc = hc_compr(compromisso_atual);
					printf("Dia: %d, Hora de Início: %d:%02d, Hora de Fim: %d:%02d, ID: %d, Descrição: %s\n",
						   dia_atual->dia, hc.ini_h, hc.ini_m, hc.fim_h, hc.fim_m, id_compr(compromisso_atual),
						   descricao_compr(compromisso_atual));
					compromisso_atual = compromisso_atual->prox;
				}
				dia_atual = dia_atual->prox;
			}
			break;
		}
		mes_atual = mes_atual->prox;
	}
}

int mes_atual_agenda(agenda_t* agenda) {
	if (agenda == NULL) {
		return 0;
	}

	return agenda->mes_atual;
}

void prim_mes_agenda(agenda_t* agenda) {
	if (agenda == NULL) {
		return;
	}

	mes_t* mes_atual = agenda->ptr_mes_atual;
	while (mes_atual != NULL && mes_atual->mes != 1) {
		mes_atual = mes_atual->ant;
	}

	agenda->ptr_mes_atual = mes_atual;
	agenda->mes_atual = 1;
}

int prox_mes_agenda(agenda_t* agenda) {
	if (agenda == NULL) {
		return 0;
	}

	mes_t* mes_atual = agenda->ptr_mes_atual;

	if (mes_atual == NULL) {
		mes_atual = (mes_t*)malloc(sizeof(mes_t));
		if (mes_atual == NULL) {
			return 0;
		}

		mes_atual->mes = 1;
		mes_atual->dias = NULL;
		mes_atual->prox = mes_atual;
		mes_atual->ant = mes_atual;
		agenda->ptr_mes_atual = mes_atual;
		agenda->mes_atual = 1;
		return 1;
	}

	if (mes_atual->prox == agenda->ptr_mes_atual) {
		mes_t* novo_mes = (mes_t*)malloc(sizeof(mes_t));
		if (novo_mes == NULL) {
			return 0;
		}

		novo_mes->mes = mes_atual->mes + 1;
		novo_mes->dias = NULL;
		novo_mes->prox = mes_atual->prox;
		novo_mes->ant = mes_atual;
		mes_atual->prox->ant = novo_mes;
		mes_atual->prox = novo_mes;
		agenda->ptr_mes_atual = novo_mes;
		agenda->mes_atual = novo_mes->mes;
		return novo_mes->mes;
	}

	agenda->ptr_mes_atual = mes_atual->prox;
	agenda->mes_atual = mes_atual->prox->mes;
	return mes_atual->prox->mes;
}

int ant_mes_agenda(agenda_t* agenda) {
	if (agenda == NULL) {
		return 0;
	}

	mes_t* mes_atual = agenda->ptr_mes_atual;

	if (mes_atual == NULL) {
		mes_atual = (mes_t*)malloc(sizeof(mes_t));
		if (mes_atual == NULL) {
			return 0;
		}

		mes_atual->mes = 1;
		mes_atual->dias = NULL;
		mes_atual->prox = mes_atual;
		mes_atual->ant = mes_atual;
		agenda->ptr_mes_atual = mes_atual;
		agenda->mes_atual = 1;
		return 1;
	}

	if (mes_atual->ant == agenda->ptr_mes_atual) {
		mes_t* novo_mes = (mes_t*)malloc(sizeof(mes_t));
		if (novo_mes == NULL) {
			return 0;
		}

		novo_mes->mes = mes_atual->mes - 1;
		novo_mes->dias = NULL;
		novo_mes->prox = mes_atual;
		novo_mes->ant = mes_atual->ant;
		mes_atual->ant->prox = novo_mes;
		mes_atual->ant = novo_mes;
		agenda->ptr_mes_atual = novo_mes;
		agenda->mes_atual = novo_mes->mes;
		return novo_mes->mes;
	}

	agenda->ptr_mes_atual = mes_atual->ant;
	agenda->mes_atual = mes_atual->ant->mes;
	return mes_atual->ant->mes;
}

compromisso_t* compr_agenda(agenda_t* agenda, int dia) {
	if (agenda == NULL) {
		return NULL;
	}

	mes_t* mes_atual = agenda->ptr_mes_atual;
	while (mes_atual != NULL) {
		if (mes_atual->mes == agenda->mes_atual) {
			dia_t* dia_atual = mes_atual->dias;
			while (dia_atual != NULL) {
				if (dia_atual->dia == dia) {
					return dia_atual->comprs;
				}
				dia_atual = dia_atual->prox;
			}
			break;
		}
		mes_atual = mes_atual->prox;
	}

	return NULL;
}
