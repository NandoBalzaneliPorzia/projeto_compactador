#include <stdio.h>
#include <stdlib.h>
#include "descompactar.h"
#include "arvore_huffman.h"
#include "tabela_de_frequencias.h"
#include "tipos.h"

// Reconstroi a arvore com base na serializacao no arquivo
Ptr_de_no_de_arvore_binaria ler_arvore(FILE* entrada) {
    int c = fgetc(entrada);
    if (c == EOF) return NULL;

    if (c == '1') {
        U8* byte = (U8*) malloc(sizeof(U8));
        *byte = fgetc(entrada);

        Elemento e;
        e.byte = byte;
        e.frequencia = 0;

        Ptr_de_no_de_arvore_binaria folha = (Ptr_de_no_de_arvore_binaria)
            malloc(sizeof(Struct_do_no_de_arvore_binaria));
        folha->esquerda = folha->direita = NULL;
        folha->informacao = e;

        return folha;
    } else if (c == '0') {
        Ptr_de_no_de_arvore_binaria esq = ler_arvore(entrada);
        Ptr_de_no_de_arvore_binaria dir = ler_arvore(entrada);

        Elemento e;
        e.byte = NULL;
        e.frequencia = 0;

        Ptr_de_no_de_arvore_binaria no = (Ptr_de_no_de_arvore_binaria)
            malloc(sizeof(Struct_do_no_de_arvore_binaria));
        no->esquerda = esq;
        no->direita = dir;
        no->informacao = e;

        return no;
    }

    return NULL;
}

void descompactar_arquivo(const char* entrada, const char* saida) {
    FILE* arquivo_entrada = fopen(entrada, "rb");
    if (!arquivo_entrada) {
        printf("Erro ao abrir o arquivo compactado: %s\n", entrada);
        return;
    }

    FILE* arquivo_saida = fopen(saida, "wb");
    if (!arquivo_saida) {
        printf("Erro ao criar o arquivo descompactado: %s\n", saida);
        fclose(arquivo_entrada);
        return;
    }

    // 1- reconstruir arvore de huffman
    Ptr_de_no_de_arvore_binaria raiz = ler_arvore(arquivo_entrada);

    // Ler \n marcador de fim da arvore
    int fim_arvore = fgetc(arquivo_entrada);
    if (fim_arvore != '\n') {
        printf("Erro: formato inválido ou árvore corrompida.\n");
        fclose(arquivo_entrada);
        fclose(arquivo_saida);
        return;
    }

    // 2= ler bits e decodificar
    Ptr_de_no_de_arvore_binaria atual = raiz;
    int c;
    while ((c = fgetc(arquivo_entrada)) != EOF) {
        for (int i = 7; i >= 0; i--) {
            int bit = (c >> i) & 1;
            if (bit == 0) {
                atual = atual->esquerda;
            } else {
                atual = atual->direita;
            }

            if (atual->esquerda == NULL && atual->direita == NULL) {
                fputc(*(atual->informacao.byte), arquivo_saida);
                atual = raiz;
            }
        }
    }

    fclose(arquivo_entrada);
    fclose(arquivo_saida);
    printf("Arquivo '%s' descompactado com sucesso como '%s'\n", entrada, saida);
}
