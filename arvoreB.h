#ifndef ARVOREB_H_INCLUDED
#define ARVOREB_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "registro.h"

#define SBB_VERTICAL 0
#define SBB_HORIZONTAL 1
#define TRUE 1
#define FALSE 0

typedef struct sbb {
    registro reg;
    struct sbb *esq;        // apontador para uma nova sub-árvore
    struct sbb *dir;        // apontador para uma nova sub-árvore
    int esqtipo;            // tipo do apontador, vertical ou horizontal
    int dirtipo;            // tipo do apontador, vertical ou horizontal
    struct sbb *subarvore;  // especifica uma nova sub ́arvore
} sbb;

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------
Protótipo: sbb *Cria_No (registro reg)
Função: Recebe um registro e a partir dele cria um nó que será adicionado na árvore
Entrada: Registro que será inserido na árvore
Saída: Retorna o nó que foi inserido na árvore
-----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
sbb *Cria_No (registro reg);

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------
Protótipo: void ee(sbb *ptr);
Função: Transformações para manter propriedadas da árvore SBB quando há dois apontadores horizontais para a esquerda seguidos
Entrada: Recebe um nó da árvore
Saída: Nenhuma
-----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void ee(sbb **ptr);

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------
Protótipo: void dd(sbb *ptr);
Função: Transformações para manter propriedadas da árvore SBB quando há dois apontadores horizontais para a direita seguidos
Entrada: Recebe um nó da árvore
Saída: Nenhuma
-----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void dd(sbb **ptr);

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------
Protótipo: void ee(sbb *ptr);
Função: Transformações para manter propriedadas da árvore SBB quando há dois apontadores horizontais seguidos, um para a esquerda e outro para a direita
Entrada: Recebe um nó da árvore
Saída: Nenhuma
-----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void ed(sbb **ptr);

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------
Protótipo: void ee(sbb *ptr);
Função: Transformações para manter propriedadas da árvore SBB quando há dois apontadores horizontais seguidos, um para a direita e outro para a esquerda
Entrada: Recebe um nó da árvore
Saída: Nenhuma
-----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void de(sbb **ptr);

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------
Protótipo: void iinsere(registro reg, sbb **ptr, int *incli, int *fim)
Função: Busca local de inserção do registro na árvore
Entrada: Registro que será inserido na árvore, além da inclinação e de um valor identificando o fim
Saída: Nenhuma
-----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void iinsere(registro reg, sbb **ptr, int *incli, int *fim);

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------
Protótipo: void iinsere_aqui(registro reg, sbb **ptr, int *incli, int *fim)
Função: Insere o registro na posição dada por sbb **ptr
Entrada: Registro que será inserido na árvore (que é o ponteiro **ptr), além da inclinação e de um valor identificando o fim
Saída: Nenhuma
-----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void iinsere_aqui(registro reg, sbb **ptr, int *incli, int *fim);

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------
Protótipo: void insere(registro reg, sbb **raiz, registro *caminho, int flag)
Função: Função que faz chamadas para se localizar o local de inserção de um determinado registro na árvore
Entrada: Registro que será inserido na árvore (que é o ponteiro **raiz), além do caminho que será necessário para inseri-lo e uma flag indicando se é o primeiro registro
Saída: Nenhuma
-----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void insere(registro reg, sbb **raiz, registro *caminho, int flag);

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------
Protótipo: void InsereNovo(registro filho, sbb **raiz, registro pai)
Função: Função que faz chamadas para se localizar o local de inserção de um determinado registro na árvore
Entrada: Registro que será inserido na árvore (que é o ponteiro **raiz), além do pai desse registro
Saída: Nenhuma
-----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void InsereNovo(registro filho, sbb **raiz, registro pai);

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------
Protótipo: void inicializa(sbb **raiz)
Função: Inicializa a árvore
Entrada: Registro que será inserido na árvore (que é o ponteiro **ptr), além da inclinação e de um valor identificando o fim
Saída: Nenhuma
-----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void inicializa(sbb **raiz);

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------
Protótipo: void ContaChavesEmPaginasImpares(sbb *raiz, TipoListaRegistros *l)
Função: Conta o número de chaves que aparecem em páginas ímpares. Não conta chaves repetidas
Entrada: Raiz da árvore mais uma lista que conterá todos os registros que aparecem em páginas ímpares
Saída: Nenhuma
-----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void ContaChavesEmPaginasImpares(sbb *raiz, TipoListaRegistros *l);

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------
Protótipo: int SalvaCaminho(sbb *raiz, registro chave, int *flag, TipoPilhaRegistros *p)
Função: Salva o caminho que foi feito da raiz da árvore até uma chave na pilha de registros p
Entrada: Raiz da árvore, registro procurado, uma flag e uma pilha de registros que conterá o caminho
Saída: Retorna -1 se o valor não foi encontrado
-----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
int SalvaCaminho(sbb *raiz, registro chave, int *flag, TipoPilhaRegistros *p);

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------
Protótipo: void SalvaRegistrosEmIntervaloDePaginas(TipoListaRegistros *v, int pag1, int pag2, sbb *raiz)
Função: Cria uma lista contendo todos os registros que estão localizados em um dado intervalo de páginas
Entrada: Raiz da árvore, intervalo de páginas e lista que vai conter todas as páginas nesse intervalo
Saída: Nenhuma
-----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void SalvaRegistrosEmIntervaloDePaginas(TipoListaRegistros *v, int pag1, int pag2, sbb *raiz);

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------
Protótipo: void CaminhoEntreDoisNos(sbb *raiz, registro reg1, registro reg2, FILE *arqSaida)
Função: Imprime o caminho entre dois nós
Entrada: Raiz da árvore, nós e o arquivo que conterá a impressão do caminho
Saída: Nenhuma
-----------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void CaminhoEntreDoisNos(sbb *raiz, registro reg1, registro reg2, FILE *arqSaida);

#endif // ARVOREB_H_INCLUDED
