#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "lib_trie.h"

int main(int argc, char *argv[])
{
    TrieNode *root;
    FILE *base, *arquivo;
    char str[TAM_PALAVRA];
    root = get_node();

    if (argc != 3)
    {
        printf("Uso: %s <arquivo base de dados> <arquivo para inserção>\n", argv[0]);
        return 1;
    }
    if (!(base = fopen(argv[1], "a")))
    {
        printf("Erro ao abrir o arquivo %s\n", argv[1]);
        return 1;
    }
    if (!(arquivo = fopen(argv[2], "r")))
    {
        printf("Erro ao abrir o arquivo %s\n", argv[2]);
        return 1;
    }
    import_trie(base, root);
    fclose(base);

    while (!feof(arquivo))
    {
        char palavra[TAM_PALAVRA];
        fscanf(arquivo, "%25s", palavra);
        retira_pontuacao(palavra);
        tudo_minusculo(palavra);
        if (!tem_acento(palavra) && strlen(palavra) >= 4)
            insert(root, palavra, argv[2]);
    }
    fclose(arquivo);

    if (!(base = fopen(argv[1], "w")))
    {
        printf("Erro ao abrir o arquivo %s\n", argv[1]);
        return 1;
    }
    export_trie(base, root, str, 0);
    
    fclose(base);
    destroy(root);
    printf("Arquivo \"%s\" inserido na arvore com sucesso!\n", argv[2]);
    return 0;
}
