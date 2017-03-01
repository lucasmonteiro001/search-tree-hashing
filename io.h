#ifndef IO_H_
#define IO_H_

#include <stdio.h>
#include <stdlib.h>

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------
Protótipo: void AbreArquivosEntradaSaida(char *paramEntrada, char *paramSaida)
Função: Abre os arquivos de entrada e saida
Entrada: Nome do arquivo de entrada e nome do arquivo de saída
Saída: Nenhuma
-----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
FILE *AbreArquivo(char *nome_arquivo, char *modo_leitura);

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------
Protótipo: FILE* FechaArquivos(char *arq1, char *arq2)
Função: Fecha os arquivos abertos
Entrada: Nome dos arquivos
Saída: nenhuma
-----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void FechaArquivo(FILE *arquivo);

#endif /* IO_H_ */
