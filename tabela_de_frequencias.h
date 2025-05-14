#ifndef TABELA_DE_FREQUENCIAS_H
#define TABELA_DE_FREQUENCIAS_H

#include "tipos.h"

// elemento da tabela: byte + frequencia
typedef struct {
    U8* byte;
    U64 frequencia;
} Elemento;

// estrutura do nó da arvore de huffman
typedef struct Struct_do_no_de_arvore_binaria {
    struct Struct_do_no_de_arvore_binaria* esquerda;
    Elemento informacao;
    struct Struct_do_no_de_arvore_binaria* direita;
} Struct_do_no_de_arvore_binaria;

typedef Struct_do_no_de_arvore_binaria* Ptr_de_no_de_arvore_binaria;

// armazena todos os nós dos bytes de 0 a 255
typedef struct {
    Ptr_de_no_de_arvore_binaria vetor[256];
    U16 quantidade_de_posicoes_preenchidas;
} Tabela_de_frequencias;

void nova_tabela_de_frequencias(Tabela_de_frequencias* tab);
boolean inclua_byte(U8 byte, Tabela_de_frequencias* tab);

#endif
