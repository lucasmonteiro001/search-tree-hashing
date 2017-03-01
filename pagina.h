#ifndef PAGINA_H_INCLUDED
#define PAGINA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

typedef struct TipoPagina {
    int numeroDaPagina;       // contém o número da página que contém a palavra chave
    struct TipoPagina *Prox;  // contém um apontador para a próxima página
} TipoPagina;

typedef struct TipoLista {
    TipoPagina *Primeiro, *Ultimo;  // contém os apontadores para a primeira e para a última página que contém a palavra chave
} TipoLista;

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------
Protótipo: void FazListaPaginasVazia(TipoLista *Lista);
Função: Faz uma lista vazia para armazenar as páginas
Entrada: Variável do TipoLista que armazenará as páginas
Saída: Nenhuma
-----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void FazListaPaginasVazia(TipoLista *Lista);

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------
Protótipo: int VerificaListaPaginasVazia(TipoLista Lista);
Função: Verifica se a lista está vazia
Entrada: Variável do TipoLista
Saída: Inteiro com valor 1 (se estiver vazia) ou 0 (se estiver cheia)
-----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
int VerificaListaPaginasVazia(TipoLista Lista);

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------
Protótipo: void InsereItemNaListaPaginas(TipoPagina pagina, TipoLista *Lista);
Função: Insere uma célula do TipoPagina nas lista de páginas
Entrada: Variável do TipoPagina e lista do TipoLista que receberá a variável
Saída: Nenhuma
-----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void InsereItemNaListaPaginas(TipoPagina pagina, TipoLista *Lista);

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------
Protótipo: void ContaPaginasImpares(TipoLista listaDePaginas)
Função: Retorna o número de páginas ímpares que uma determinada chave possui
Entrada: Uma lista do tipo TipoLista contendo as disciplinas que devem ser imprimidas
Saída: Nenhuma
-----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
int ContaPaginasImpares(TipoLista Lista);

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------
Protótipo: int VerificaPaginaIntervalo(TipoLista Lista, int pag1, int pag2)
Função: Verifica se uma determinada lista de páginas contém alguma página que esteja no intervalo pag1-pag2
Entrada: Uma lista de páginas e o intervalo de busca
Saída: Retorna TRUE ou FALSE, verificando se existe alguma página no intervalo de busca, ou não
-----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
int VerificaPaginaIntervalo(TipoLista Lista, int pag1, int pag2);

#endif // PAGINA_H_INCLUDED
