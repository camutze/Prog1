struct eventos_e
{
    int tipo;
    int tempo;
    struct pontos_p *local;
};

void evento_chega(struct mundo_m *mundo, int tempo, int heroi_pos, int base_pos);

void evento_espera(struct mundo_m *mundo, int tempo, struct heroi_h *heroi, struct base_b *base);

void evento_desiste(struct mundo_m *mundo, int tempo, struct heroi_h *heroi, struct base_b *base);

void evento_avisa(struct mundo_m *mundo, int tempo, struct base_b *base);

void evento_entra(struct mundo_m *mundo, struct mundo_m *m, int tempo, struct heroi_h *heroi, struct base_b *base);

void evento_sai(struct mundo_m *mundo, int tempo, struct heroi_h *heroi, struct base_b *base);

void envento_viaja(struct mundo_m *mundo, int tempo, struct heroi_h *heroi, struct base_b *base);

void evento_missao(struct mundo_m *mundo, int tempo, struct heroi_h *heroi, struct base_b *base);




