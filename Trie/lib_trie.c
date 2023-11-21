#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "lib_trie.h"


TrieNode *get_node()
{
    TrieNode *node;
    if(!(node = malloc(sizeof(TrieNode))))
    {
        printf("Erro ao alocar memoria!\n");
        exit(1);
    }

    node->eh_final = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++)
        node->filhos[i] = NULL;
    return node;
}

void insert(TrieNode *raiz, const char *palavra, const char *origem)
{
    int index;
    TrieNode *pCrawl = raiz;
    while (*palavra != '\0')
    {
        index = *palavra - 'a';
        if (pCrawl->filhos[index] == NULL)
        {
            pCrawl->filhos[index] = get_node();
            strcpy(pCrawl->filhos[index]->origem, origem); // Copia a origem para o novo nó
        }
        pCrawl = pCrawl->filhos[index];
        palavra++;
    }
    pCrawl->eh_final = 1;
}

void print_trie(TrieNode *raiz, char str[], int nivel)
{
    if (raiz->eh_final)
    {
        str[nivel] = '\0';
        printf("%s ", str);
        printf("%s\n", raiz->origem);
    }

    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (raiz->filhos[i])
        {
            str[nivel] = i + 'a';
            print_trie(raiz->filhos[i], str, nivel + 1);
        }
    }
}

void print_prefix(TrieNode *raiz, const char *prefix)
{
    printf("Palavras com prefixo %s:\n", prefix);
    TrieNode *pCrawl = raiz;
    while (*prefix != '\0')
    {
        int index = *prefix - 'a';
        if (!pCrawl->filhos[index])
            return;
        pCrawl = pCrawl->filhos[index];
        prefix++;
    }

    char str[TAM_PALAVRA];
    print_trie(pCrawl, str, 0);
}

void destroy(TrieNode *raiz)
{
    for (int i = 0; i < ALPHABET_SIZE; i++)
        if (raiz->filhos[i] != NULL)
            destroy(raiz->filhos[i]);
    free(raiz);
}

int tem_acento(char *str)
{
    char *acentuadas = "ÀÁÂÃÄÅÇÈÉÊËÌÍÎÏÒÓÔÕÖÙÚÛÜÝàáâãäåçèéêëìíîïðòóôõöùúûüýÿ";
    size_t i, j;

    for (i = 0; i < strlen(str); i++)
    {
        for (j = 0; j < strlen(acentuadas); j++)
        {
            if (str[i] == acentuadas[j])
            {
                return 1; // Retorna 1 se encontrar um acento a ser ignorado
            }
        }
    }
    return 0; // Retorna 0 se não encontrar acentos a serem ignorados
}

void retira_pontuacao(char *str)
{
    int len = strlen(str);
    int j = 0;
    for (int i = 0; i < len; i++)
    {
        if (!ispunct(str[i]))
        {
            str[j++] = str[i];
        }
    }
    str[j] = '\0';
}

void tudo_minusculo(char *str)
{
    int len = strlen(str);
    for (int i = 0; i < len; i++)
    {
        if (isupper(str[i]))
        {
            str[i] = tolower(str[i]); // converte para minuscula
        }
    }
}

void export_trie(FILE *base, TrieNode *raiz, char str[], int nivel)
{
    if (raiz->eh_final)
    {
        str[nivel] = '\0';
        fprintf(base, "%s ", str);
        fprintf(base, "%s\n", raiz->origem);
    }

    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (raiz->filhos[i])
        {
            str[nivel] = i + 'a';
            export_trie(base, raiz->filhos[i], str, nivel + 1);
        }
    }
}

int import_trie(FILE *base, TrieNode *raiz)
{
    char palavra[TAM_PALAVRA];
    char origem[TAM_ARQUIVO];

    // Verifica se o arquivo está vazio
    fseek(base, 0, SEEK_END);
    if (!ftell(base))
        return 0;

    rewind(base); // Volta ao início do arquivo

    while (fscanf(base, "%s %s", palavra, origem) == 2)
    {
        insert(raiz, palavra, origem);
    }
    return 1;
}
