#include "eventos.h"

long calcula_distancia(mundo_t *m, int clk, int h, int b)
{
   
    long distancia;
    int b_at; //base atual
    b_at = m->heroi[h].base_id;

    /*TERMINAR AMANHA*/



    long x = (local_destino->x - local->x) * (local_destino->x - local->x);
    long y = (local_destino->y - local->y) * (local_destino->y - local->y);

    distancia = sqrt(x + y);

    return distancia;
}

void evento_chega(mundo_t *m, int h, int b)
{
    evento_t *ev;
    bool espera;

    m->heroi[h].base_id = b;
    /*se há vagas em B e a fila de espera está vazia:*/
    if (set_size(m->base[b].presentes) < m->base->lotacao && lista_vazia(m->base[b].lista_espera))
        espera = true;
    else
        /*Aqui se for maior TRUE, se for menor FALSE
        ******OPERACAO BOLEANA********/
        espera = (m->heroi[h].paciencia) > (10 * lista_tamanho(m->base->lista_espera));

    /*Disparo de novos eventos*/
    if (espera)
    {
        if (!(ev = cria_evento(m->relogio, EV_ESPERA, h, b)))
            fim_execucao("nao aloc func evento_chega");
    }
    else if (!(ev = cria_evento(m->relogio, EV_DESISTE, h, b)))
        fim_execucao("nao aloc func evento_chega");

    insere_lef(m->eventos, ev);

    return 1;
}

void evento_espera(mundo_t *m, int clk, int h, int b)
{
    evento_t *ev;

    /*adiciona H ao fim da fila de espera de B*/
    lista_insere(m->base[b].lista_espera, h, L_FIM);

    if (!(ev = cria_evento(m->relogio, EV_ESPERA, h, b)))
        fim_execucao("nao aloc func evento_espera");
}

void evento_desiste(mundo_t *m, int clk, int h, int b)
{
    int dest_b;
    dest_b = gera_aleat(0, m->n_bases - 1);
    envento_viaja(m, clk, h, b);
}

/*AVISA (T, B):

enquanto houver vaga em B e houver heróis enao sper fila:
    retira primeiro herói (H') da fila de B
    adiciona H' ao conjunto de heróis presentes em B
    cria evento ENTRA (agora, H', B)*/



void evento_avisa(mundo_t *m, int clk, int b)
{
    evento_t *ev;
    int h;

    while((set_size(m->base->presentes) < m->base->lotacao) && !lista_vazia(m->base->lista_espera))
    {
        h = lista_remove(m->base->lista_espera, L_INICIO);
        set_add(m->base->presentes, h);

        if (!(ev = cria_evento(m->relogio, EV_ENTRA, h, b)))
            fim_execucao("nao aloc func evento_avisa");
    }

}

void evento_entra(mundo_t *m, int clk, int h, int b)
{
    evento_t *ev;
    int tpb;

    tpb = 15 + m->heroi[h].paciencia * gera_aleat(1, 20);
    
    m->relogio += tpb;
    //PERGUTAR, PODE? ev = cria_evento(m->relogio += tpb, EV_SAI, h, b);
    ev = cria_evento(m->relogio, EV_SAI, h, b);
    
}

void evento_sai(mundo_t *m, int clk, int h, int b)
{
    evento_t *ev;
    int dest_b;

    set_del(m->base[b].presentes, h);

    dest_b = gera_aleat(0, m->n_bases - 1);

    if (!(ev = cria_evento(m->relogio, EV_VIAJA, h, dest_b)))
        fim_execucao("nao aloc func evento_sai");
    
    if(!(ev = cria_evento(m->relogio, EV_AVISA, h, dest_b)))
        fim_execucao("nao aloc func evento_sai");
    

}

void evento_viaja(mundo_t *m, int clk, int h, int b)
{
    evento_t *ev;
    long dist; //calcular a distancia que vai viajar e o tempo que vai demorar

    dist = calcula_distancia(m, h, b);
    


}