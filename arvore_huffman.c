#include <stdlib.h>
#include <stdio.h>
#include "arvore_huffman.h"
#include "tipos.h"
#include "tabela_de_frequencias.h"
#include "codigo.h"

// SERIALIZA A ARVORE DE HUFFMAN (grava em pre-ordem) e transforma a arvore numa sequencia de bytes
void serializar_arvore(Ptr_de_no_de_arvore_binaria raiz, FILE* out) {
    if (raiz == NULL) return;

    if (raiz->esquerda == NULL && raiz->direita == NULL && raiz->informacao.byte != NULL) {
        fputc('1', out);                        // marca como folha
        fputc(*(raiz->informacao.byte), out);   // grava o byte
    } else {
        fputc('0', out);                        // marca como interno
        serializar_arvore(raiz->esquerda, out);
        serializar_arvore(raiz->direita, out);
    }
}

// LIBERA TODA A ARVORE DE HUFFMAn
void liberar_arvore(Ptr_de_no_de_arvore_binaria raiz) {
    if (raiz == NULL) return;

    liberar_arvore(raiz->esquerda);
    liberar_arvore(raiz->direita);

    if (raiz->informacao.byte != NULL)
        free(raiz->informacao.byte);

    free(raiz);
}

// Funcao auxiliar p ordencao por freq (qsort)
static int comparar(const void* a, const void* b) {
    Ptr_de_no_de_arvore_binaria na = *(Ptr_de_no_de_arvore_binaria*)a;
    Ptr_de_no_de_arvore_binaria nb = *(Ptr_de_no_de_arvore_binaria*)b;

    if (na == NULL && nb == NULL) return 0;
    if (na == NULL) return 1;
    if (nb == NULL) return -1;

    if (na->informacao.frequencia < nb->informacao.frequencia) return -1;
    if (na->informacao.frequencia > nb->informacao.frequencia) return 1;
    return 0;
}

// constroi a arvore de huffman a partir da tabela
Ptr_de_no_de_arvore_binaria construir_arvore_huffman(Tabela_de_frequencias* tabela) {
    while (tabela->quantidade_de_posicoes_preenchidas > 1) {
        // Ordena os nós por frequência
        qsort(tabela->vetor, 256, sizeof(Ptr_de_no_de_arvore_binaria), comparar);

        // pega os dois menores
        Ptr_de_no_de_arvore_binaria a = tabela->vetor[0];
        Ptr_de_no_de_arvore_binaria b = tabela->vetor[1];

        // cria novo NÓ pai
        Elemento elem;
        elem.byte = NULL;
        elem.frequencia = a->informacao.frequencia + b->informacao.frequencia;

        Ptr_de_no_de_arvore_binaria novo = (Ptr_de_no_de_arvore_binaria)malloc(sizeof(Struct_do_no_de_arvore_binaria));
        if (novo == NULL) return NULL;

        novo->informacao = elem;
        novo->esquerda = a;
        novo->direita = b;

        // substitui os 2 primeiros pelo novo nó e reordena
        tabela->vetor[0] = novo;
        tabela->vetor[1] = NULL;

        for (int i = 2; i < 256; i++) {
            if (tabela->vetor[i] != NULL) {
                tabela->vetor[i - 1] = tabela->vetor[i];
                tabela->vetor[i] = NULL;
            }
        }

        tabela->quantidade_de_posicoes_preenchidas--;
    }

    return tabela->vetor[0];
}

// gera os codigos binarios na arvore
void gerar_codigos(Ptr_de_no_de_arvore_binaria raiz, Codigo* codigos[256], Codigo atual) {
    if (raiz == NULL) return;

    if (raiz->esquerda == NULL && raiz->direita == NULL && raiz->informacao.byte != NULL) {
        U8 byte = *(raiz->informacao.byte);
        Codigo* novo = (Codigo*)malloc(sizeof(Codigo));
        if (clone(atual, novo)) {
            codigos[byte] = novo;
        }
        return;
    }

    adiciona_bit(&atual, 0);
    gerar_codigos(raiz->esquerda, codigos, atual);
    joga_fora_bit(&atual);

    adiciona_bit(&atual, 1);
    gerar_codigos(raiz->direita, codigos, atual);
    joga_fora_bit(&atual);
}
