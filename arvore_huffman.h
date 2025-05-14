#ifndef ARVORE_HUFFMAN_H
#define ARVORE_HUFFMAN_H

#include <stdio.h>
#include "tabela_de_frequencias.h"
#include "codigo.h"

Ptr_de_no_de_arvore_binaria construir_arvore_huffman(Tabela_de_frequencias* tabela);
void gerar_codigos(Ptr_de_no_de_arvore_binaria raiz, Codigo* codigos[256], Codigo atual);
void serializar_arvore(Ptr_de_no_de_arvore_binaria raiz, FILE* out);
void liberar_arvore(Ptr_de_no_de_arvore_binaria raiz);

#endif
