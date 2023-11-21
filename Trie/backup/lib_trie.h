#ifndef TRIE_T
#define TRIE_T

#define ALPHABET_SIZE 52
#define TAM_PALAVRA 40
#define TAM_ARQUIVO 100

typedef struct trie_node
{
    struct trie_node *children[ALPHABET_SIZE];
    char origem[TAM_ARQUIVO]; // Adiciona campo para armazenar a origem do arquivo
    int eh_final;
} TrieNode;


TrieNode *get_node();

void insert(TrieNode *raiz, const char *palavra, const char *origem);

void print_trie(TrieNode *raiz, char str[], int nivel);

void print_prefix(TrieNode *raiz, const char *prefix);

void destroy(TrieNode *raiz);

int tem_acento(char *str);

void retira_pontuacao(char *str);

void tudo_minusculo(char *str);

void export_trie(FILE *base, TrieNode *raiz, char str[], int nivel);

int import_trie(FILE *base, TrieNode *raiz);

#endif