#include <stdlib.h>
#include "tabela_de_frequencias.h"

// inicializa tabela com todos os ponteiros nulos
void nova_tabela_de_frequencias(Tabela_de_frequencias* tab) {
    for (U16 i = 0; i < 256; i++) {
        tab->vetor[i] = NULL;
    }
    tab->quantidade_de_posicoes_preenchidas = 0;
}

// cria novo nó da arvore de huffman
static boolean novo_no_de_arvore_binaria(
    Ptr_de_no_de_arvore_binaria* novo,
    Ptr_de_no_de_arvore_binaria esq,
    Elemento inf,
    Ptr_de_no_de_arvore_binaria dir) 
{
    *novo = (Ptr_de_no_de_arvore_binaria)malloc(sizeof(Struct_do_no_de_arvore_binaria));
    if (*novo == NULL) return false;

    (*novo)->esquerda = esq;
    (*novo)->informacao = inf;
    (*novo)->direita = dir;

    return true;
}

// adiciona ou incrementa frequencia de um byte na tabela
boolean inclua_byte(U8 byte, Tabela_de_frequencias* tab) {
    if (tab->vetor[byte] != NULL) {
        tab->vetor[byte]->informacao.frequencia++;
        return true;
    }

    Elemento elem;
    elem.byte = (U8*)malloc(sizeof(U8));
    if (elem.byte == NULL) return false;

    *elem.byte = byte;
    elem.frequencia = 1;

    boolean ok = novo_no_de_arvore_binaria(&(tab->vetor[byte]), NULL, elem, NULL);
    if (!ok) {
        free(elem.byte);
        return false;
    }

    tab->quantidade_de_posicoes_preenchidas++;
    return true;
}
