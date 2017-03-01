#ifndef OPERACAO_H_INCLUDED
#define OPERACAO_H_INCLUDED

#define MAX 256

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TipoOperacao {
    char operacao[MAX];
    char parametros[MAX];
    struct TipoOperacao *Prox;
} TipoOperacao;

typedef struct TipoListaOperacoes {
    TipoOperacao operacao;
    TipoOperacao *Primeiro, *Ultimo;
} TipoListaOperacoes;

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------
Protótipo: void FazListaOperacoesVazia(TipoListaOperacoes *Lista)
Função: Cria uma lista de operações vazia
Entrada: Apontador do tipo TipoListaOperacoes
Saída: Nenhuma
-----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void FazListaOperacoesVazia(TipoListaOperacoes *Lista);

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------
Protótipo: int VerificaListaOperacoesVazia(TipoListaOperacoes *Lista);
Função: Verifica se a lista de operações está vazia
Entrada: Lista de operações
Saída: TRUE ou FALSE
-----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
int VerificaListaOperacoesVazia(TipoListaOperacoes *Lista);

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------
Protótipo: void InsereOperacao(TipoOperacao operacao, TipoListaOperacoes *Lista)
Função: Insere uma nova operação na lista de operações
Entrada: Lista de operações e operação a ser inserida
Saída: Nenhuma
-----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void InsereOperacao(TipoOperacao operacao, TipoListaOperacoes *Lista);

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------
Protótipo: TipoOperacao *RemovePrimeiro(TipoListaOperacoes *Lista)
Função: A lista em questão funciona como uma fila. Portanto, essa função remove o primeiro elemento da fila
Entrada: Lista de operações
Saída: Operação que foi removida
-----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
TipoOperacao *RemovePrimeiro(TipoListaOperacoes *Lista);

#endif // OPERACAO_H_INCLUDED
