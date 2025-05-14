#ifndef CODIGO_H
#define CODIGO_H

#include "tipos.h"

// Representa um codigo binário de Huffman
typedef struct {
    U8* byte;       // vetor de bits armazenados em bytes
    U8 capacidade;  // capacidade total em bits
    U8 tamanho;     // tamanho atual em bits
} Codigo;

boolean novo_codigo(Codigo* c);                     // cria novo codigo vazio
void free_codigo(Codigo* c);                        // libera memoria
boolean adiciona_bit(Codigo* c, U8 valor);          // adiciona bit 0 ou 1
boolean joga_fora_bit(Codigo* c);                   // remove ultimo bit
boolean clone(Codigo original, Codigo* copia);      // copia um codigo

#endif
