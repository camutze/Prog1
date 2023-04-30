#define CIMA 20
#define BAIXO 10

struct bolodepote{
    char tipo;
    int data_pote; 
};

struct tortinha{
    int data;
    int data_tortinha; 
};


struct frigobar{
    struct bolodepote *p_cima[CIMA];
    struct tortinha *p_baixo[BAIXO];
};

struct frigobar cria_frigobar();

/* Retorna a posição do vetor parte de BAIXO ou cima
 onde sera possivel fazer malloc ou -1 para erro*/
int posi_disponivel(struct frigobar *consul, int parte_de);

void cria_produto();

struct frigobar aloca_vetor(struct frigobar *consul, int index);

int lista_qtd();

void destroi_vencido();

void destroi_figobar();



