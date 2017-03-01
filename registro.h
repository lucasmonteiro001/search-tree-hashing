#ifndef REGISTRO_H_INCLUDED
#define REGISTRO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pagina.h"

#define MAX 256 // Tamanho máximo que uma linha poderá ter

typedef struct registro {
    char *chave;            // string que contém a palavra-chave
    int qut_espacos;        // quantidade de espaços que a palavra-chave possui, do começo da linha
    TipoLista listaPaginas; // contém as informações referentes às páginas em que a palavra chave se encontra
    struct registro *Prox;  // Usado para fila
} registro;

typedef struct TipoPilhaRegistros {
    registro *Fundo, *Topo;
    int Tamanho;
} TipoPilhaRegistros;

typedef struct TipoListaRegistros {
    registro *Primeiro, *Ultimo;
} TipoListaRegistros;

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------
Protótipo: void PreencheVetorRegistros(registro *v, FILE *arqEntrada)
Função: Preenche um vetor de registros *v com os registros lidos do arquivo
Entrada: Vetor de registros *v e o arquivo de entrada
Saída: Nenhuma
-----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void PreencheVetorRegistros(registro *v, FILE *arqEntrada);

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------
Protótipo: void PreencheVetorUltimoElemento(registro *ultimos_por_nivel, int pos, registro *vetor_registros)
Função: Preenche o vetor com os últimos elementos de cada nível
Entrada: Vetor contendo o último elementos de cada nível, a posição à ser preenchida e o vetor contendo os registros
Saída: Nenhuma
-----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void PreencheVetorUltimoElemento(registro *ultimos_por_nivel, int pos, registro *vetor_registros);

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------
Protótipo: registro *CaminhoParaInsercao(registro *ultimos_por_nivel, int pos, registro *vetor_registros)
Função: Retorna um "mapa" contendo o caminho a ser percorrido para se inserir um novo registro na árvore
Entrada: Vetor contendo o "mapa", posição da última atualização do mapa e o vetor de registros
Saída: Retorna o caminho "mapa".
-----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
registro *CaminhoParaInsercao(registro *ultimos_por_nivel, int pos, registro *vetor_registros);

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------
Protótipo: void FazPilhaRegistroVazia(TipoPilhaRegistros *Pilha)
Função: Cria uma pilha de registros
Entrada: Apontador do TipoPilhaRegistros
Saída: Nenhuma
-----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void FazPilhaRegistroVazia(TipoPilhaRegistros *Pilha);

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------
Protótipo: int VerificaPilhaRegistrosVazia(TipoPilhaRegistros Pilha)
Função: Retorna se a pilha de registros está vazia ou não
Entrada: Pilha de registros
Saída: TRUE ou FALSE
-----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
int VerificaPilhaRegistrosVazia(TipoPilhaRegistros Pilha);

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------
Protótipo: void EmpilhaRegistro(registro x, TipoPilhaRegistros *Pilha)
Função: Empilha um novo registro na pilha
Entrada: Registro a ser empilhado e pilha
Saída: Nenhuma
-----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void EmpilhaRegistro(registro x, TipoPilhaRegistros *Pilha);

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------
Protótipo: registro *DesempilhaRegistro(TipoPilhaRegistros *Pilha)
Função: Desempilha o último elemento inserido na pilha
Entrada: Pilha de registros
Saída: Retorna o registro que foi desempilhado
-----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
registro *DesempilhaRegistro(TipoPilhaRegistros *Pilha);

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------
Protótipo: void FazListaRegistroVazia(TipoListaRegistros *Lista)
Função: Cria uma lista de registros vazia
Entrada: Apontador do TipoListaRegistros
Saída: Nenhuma
-----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void FazListaRegistroVazia(TipoListaRegistros *Lista);

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------
Protótipo: int VerificaListaRegistrosVazia(TipoListaRegistros *Lista)
Função: Verifica se a lista está vazia
Entrada: Lista de registros
Saída: TRUE ou FALSE
-----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
int VerificaListaRegistrosVazia(TipoListaRegistros *Lista);

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------
Protótipo: void InsereRegistroLista(registro r, TipoListaRegistros *Lista)
Função: Insere um novo registro na lista
Entrada: Lista de registros e registro a ser inserido
Saída: Nenhuma
-----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void InsereRegistroLista(registro r, TipoListaRegistros *Lista);

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------
Protótipo: void ImprimeListaRegistros(TipoListaRegistros l, FILE *arqSaida)
Função: Imprime uma lista de registros
Entrada: Lista de registros e arquivo que conterá a impressão
Saída: Nenhuma
-----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void ImprimeListaRegistros(TipoListaRegistros l, FILE *arqSaida);

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------
Protótipo: int VerificaExistenciaRegistro(registro r, TipoListaRegistros *l)
Função: Verifica se um determinado registro existe na lista
Entrada: Lista de registros e registro que será checado
Saída: TRUE ou FALSE
-----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
int VerificaExistenciaRegistro(registro r, TipoListaRegistros *l);

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------
Protótipo: int ContaElementosNaLista(TipoListaRegistros l)
Função: Conta o número de elementos que a lista possui
Entrada: Lista de registros
Saída: Quantidade de elementos
-----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
int ContaElementosNaLista(TipoListaRegistros l);

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------
Protótipo: void OrdenaListaRegistros(TipoListaRegistros *l1, TipoListaRegistros *Lista)
Função: Insere todos os elementos da lista l1, ordenados alfabeticamente, na lista Lista
Entrada: 2 listas de registros
Saída: Nenhuma
-----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void OrdenaListaRegistros(TipoListaRegistros *l1, TipoListaRegistros *Lista);

#endif // REGISTRO_H_INCLUDED
