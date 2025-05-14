#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compactar.h"
#include "tabela_de_frequencias.h"
#include "arvore_huffman.h"
#include "codigo.h"
#include "tipos.h"

void escrever_arvore(Ptr_de_no_de_arvore_binaria raiz, FILE* saida) {
    if (raiz == NULL) return;

    if (raiz->esquerda == NULL && raiz->direita == NULL) {
        fputc('1', saida);
        fputc(*(raiz->informacao.byte), saida);
    } else {
        fputc('0', saida);
        escrever_arvore(raiz->esquerda, saida);
        escrever_arvore(raiz->direita, saida);
    }
}

void compactar_arquivo(const char* entrada, const char* saida) {
    FILE* arquivo_entrada = fopen(entrada, "rb");
    if (!arquivo_entrada) {
        printf("Erro ao abrir arquivo de entrada: %s\n", entrada);
        return;
    }

    // conta freq
    Tabela_de_frequencias tabela;
    nova_tabela_de_frequencias(&tabela);
    int byte_lido;
    while ((byte_lido = fgetc(arquivo_entrada)) != EOF) {
        inclua_byte((U8)byte_lido, &tabela);
    }

    // cria arvore huffman
    Ptr_de_no_de_arvore_binaria raiz = construir_arvore_huffman(&tabela);

    // gera os codigos de huffman
    Codigo* codigos[256] = { NULL };
    Codigo atual;
    novo_codigo(&atual);
    gerar_codigos(raiz, codigos, atual);
    free_codigo(&atual);

    // reabre arquivo e prepara saida
    rewind(arquivo_entrada);
    FILE* arquivo_saida = fopen(saida, "wb");
    if (!arquivo_saida) {
        printf("Erro ao criar arquivo de saída: %s\n", saida);
        fclose(arquivo_entrada);
        return;
    }

    // escreve arvore no inicio do arquivo
    escrever_arvore(raiz, arquivo_saida);
    fputc('\n', arquivo_saida); // marcador de fim da arvore

    // escreve dados compactados BIT A BIT
    U8 buffer = 0;
    int bits_preenchidos = 0;

    while ((byte_lido = fgetc(arquivo_entrada)) != EOF) {
        Codigo* cod = codigos[byte_lido];
        for (int i = 0; i < cod->tamanho; i++) {
            U8 byte_index = i / 8;
            U8 bit_index = 7 - (i % 8);
            U8 bit = (cod->byte[byte_index] >> bit_index) & 1;

            buffer = (buffer << 1) | bit;
            bits_preenchidos++;

            if (bits_preenchidos == 8) {
                fputc(buffer, arquivo_saida);
                buffer = 0;
                bits_preenchidos = 0;
            }
        }
    }

    // escrever ultimo byte se n estiver completo
    if (bits_preenchidos > 0) {
        buffer <<= (8 - bits_preenchidos);
        fputc(buffer, arquivo_saida);
    }

    // libera os recursos
    fclose(arquivo_entrada);
    fclose(arquivo_saida);

    for (int i = 0; i < 256; i++) {
        if (codigos[i]) {
            free_codigo(codigos[i]);
            free(codigos[i]);
        }
    }

    liberar_arvore(raiz);

    printf("Arquivo compactado com sucesso como '%s'\n", saida);
}
