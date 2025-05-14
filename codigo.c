#include <stdlib.h>
#include <string.h>
#include "codigo.h"

// cria um novo codigo vazio com capacidade de 8 bits
boolean novo_codigo(Codigo* c) {
    c->byte = (U8*)malloc(1 * sizeof(U8));
    if (c->byte == NULL) return false;

    c->byte[0] = 0;
    c->capacidade = 8;
    c->tamanho = 0;
    return true;
}

// libera a memória de um código
void free_codigo(Codigo* c) {
    if (c->byte != NULL) {
        free(c->byte);
        c->byte = NULL;
    }
    c->capacidade = 0;
    c->tamanho = 0;
}

// adiciona um bit no final do codigo
boolean adiciona_bit(Codigo* c, U8 valor) {
    if (valor != 0 && valor != 1) return false;

    // Se n tiver mais espaco aumenta a capacidade
    if (c->tamanho == c->capacidade) {
        U8* novo = (U8*)malloc((c->capacidade / 8 + 1) * sizeof(U8));
        if (novo == NULL) return false;

        // copia os bytes existentes
        for (int i = 0; i < c->capacidade / 8; i++) {
            novo[i] = c->byte[i];
        }
        novo[c->capacidade / 8] = 0;

        free(c->byte);
        c->byte = novo;
        c->capacidade += 8;
    }

    int byte_index = c->tamanho / 8;
    int bit_index = 7 - (c->tamanho % 8);

    if (valor == 1) {
        c->byte[byte_index] |= (1 << bit_index);
    }

    c->tamanho++;
    return true;
}

// remove o ultimo bit do codigo
boolean joga_fora_bit(Codigo* c) {
    if (c->tamanho == 0) return false;

    c->tamanho--;

    int byte_index = c->tamanho / 8;
    int bit_index = 7 - (c->tamanho % 8);

    c->byte[byte_index] &= ~(1 << bit_index);

    // Libera espaço se sobrar byte extra não utilizado
    if (c->capacidade - c->tamanho >= 8 && c->capacidade > 8) {
        int novos_bytes = (c->capacidade / 8) - 1;
        U8* novo = (U8*)malloc(novos_bytes * sizeof(U8));
        if (novo == NULL) return false;

        for (int i = 0; i < novos_bytes; i++) {
            novo[i] = c->byte[i];
        }

        free(c->byte);
        c->byte = novo;
        c->capacidade -= 8;
    }

    return true;
}

// Clona um código (cópia profunda)
boolean clone(Codigo original, Codigo* copia) {
    int num_bytes = (original.capacidade + 7) / 8;
    copia->byte = (U8*)malloc(num_bytes * sizeof(U8));
    if (copia->byte == NULL) return false;

    for (int i = 0; i < num_bytes; i++) {
        copia->byte[i] = original.byte[i];
    }

    copia->capacidade = original.capacidade;
    copia->tamanho = original.tamanho;
    return true;
}
