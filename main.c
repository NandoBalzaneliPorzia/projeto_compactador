#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compactar.h"
#include "descompactar.h"

int main() {
    int opcao;
    char arquivo_entrada[256];
    char arquivo_saida[256];

    do {
        printf("====== MENU HUFFMAN ======\n");
        printf("1. Compactar arquivo\n");
        printf("2. Descompactar arquivo\n");
        printf("0. Sair\n");
        printf("==========================\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); // Captura o ENTER após scanf

        switch (opcao) {
            case 1:
                printf("Digite o nome do arquivo de entrada: ");
                fgets(arquivo_entrada, sizeof(arquivo_entrada), stdin);
                arquivo_entrada[strcspn(arquivo_entrada, "\n")] = 0; // remove \n

                printf("Digite o nome do arquivo compactado (.huff): ");
                fgets(arquivo_saida, sizeof(arquivo_saida), stdin);
                arquivo_saida[strcspn(arquivo_saida, "\n")] = 0;

                compactar_arquivo(arquivo_entrada, arquivo_saida);
                break;

            case 2:
                printf("Digite o nome do arquivo .huff: ");
                fgets(arquivo_entrada, sizeof(arquivo_entrada), stdin);
                arquivo_entrada[strcspn(arquivo_entrada, "\n")] = 0;

                printf("Digite o nome do arquivo de saída descompactado: ");
                fgets(arquivo_saida, sizeof(arquivo_saida), stdin);
                arquivo_saida[strcspn(arquivo_saida, "\n")] = 0;

                descompactar_arquivo(arquivo_entrada, arquivo_saida);
                break;

            case 0:
                printf("Encerrando o programa...\n");
                break;

            default:
                printf("Opção inválida. Tente novamente.\n");
        }

        printf("\n");
    } while (opcao != 0);

    return 0;
}
