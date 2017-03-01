#include <stdio.h>
#include <stdlib.h>
#include "io.h"

FILE *AbreArquivo(char *nome_arquivo, char *modo) {
    FILE *arquivo;

    if(!(arquivo = fopen(nome_arquivo, modo))) {
        printf("\nErro ao abrir o arquivo\n");
        exit(0);
    }

    return arquivo;
}

void FechaArquivo(FILE *arquivo) {

    fclose(arquivo);
}
