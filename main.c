#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arvoreB.h"
#include "io.h"
#include "operacao.h"

#define MAX 256

int main(int argc, char *argv[]) {

    //  Abertura do arquivo de entrada e do de saída
    FILE *arqEntrada = AbreArquivo(argv[1], "r");
    FILE *arqSaida = AbreArquivo(argv[2], "w");

    char s[MAX];                // Variável que armazenará a linha
    int linhas_arquivo = 0;     // Variável que armazenará o tamanho (em linhas) do arquivo
    registro *vetor_registros;  // Vetor que será alocado dinamicamente, contendo todos os registros que estão no arquivo
    int i = 0;                  // Variável auxiliar
    sbb *raiz;                  // Raiz principal da árvore

    // Conta o número de linhas que o arquivo possui até achar a primeira linha em branco
    while(fgets(s, MAX, arqEntrada) != NULL && s[1] != '\n') {linhas_arquivo++;}

    // Retorna para o início do arquivo
    fseek(arqEntrada, 0, SEEK_SET);

    // Aloca o tamanho do vetor de registros
    vetor_registros = (registro *)malloc(linhas_arquivo * sizeof(registro));
    // Preenche o vetor com os registros lidos do arquivo
    PreencheVetorRegistros(vetor_registros, arqEntrada);

    // Descobre o local de inserção e retorna o caminho de todos os últimos níveis
    registro *aux;
    registro *ultimos_por_nivel; aux = (registro *)malloc(linhas_arquivo * sizeof(registro));
    ultimos_por_nivel = CaminhoParaInsercao(aux, i, vetor_registros);

    // Inicializa a árvore
    inicializa(&raiz);

    // Insere o primeiro item do vetor de registros na árvore
    // (1) é uma flag indicativa de primeiro item
    insere(vetor_registros[0], &raiz, ultimos_por_nivel, 1);
    // Insere todas as chaves lidas do arquivo na árvore
    for(i = 1; i < linhas_arquivo; i ++) {
            insere(vetor_registros[i], &raiz, ultimos_por_nivel, 0);
            ultimos_por_nivel = CaminhoParaInsercao(ultimos_por_nivel, i, vetor_registros);
    }

    // Agora, é necessário saber quais as operações serão realizadas. Portanto, faz-se a leitura do arquivo armazenando todas as operações, com seus
    // parâmetros, em uma lista de operações, a qual funcionará como uma fila.
    TipoListaOperacoes l;FazListaOperacoesVazia(&l); // Lista que conterá as operações quer serão realizadas
    TipoOperacao o; // Variavel que vai conter a operação e seus parâmetros

    // Lẽ as operações que serão realizadas
    while(fgets(s, MAX, arqEntrada) != NULL) {
        strcpy(o.operacao, s);
        InsereOperacao(o, &l);
    }

    // A partir do momento que temos a lista de operações é necessária esvaziá-la, realizando cada operação que sai da lista
    TipoOperacao *Aux; // Variável que vai conter sempre o ultimo item retirado da lista

    while(!(VerificaListaOperacoesVazia(&l)) && l.Primeiro->Prox != NULL) {

        Aux = RemovePrimeiro(&l); // Remoção do primeiro elemento da lista de operações

        // Se a operação for busca
        if(strcmp(Aux->operacao, "busca") == 0) {

            TipoPilhaRegistros p; FazPilhaRegistroVazia(&p);    // Pilha que vai conter o caminho
            registro aux, aux1;                                 // Registros auxiliares
            int flag = 0, i = 0;                                // Flag para ser auxiliar no busca do caminho e i (variável auxiliar)

            // Variáveis auxiliares para guardar o nome da chave que se quer fazer a busca
            aux.chave = (char *)malloc(MAX * sizeof(char));
            aux1.chave = (char *)malloc(MAX * sizeof(char));

            // Copia a chave que se quer buscar para aux
            strcpy(aux.chave, Aux->parametros);

            // Retira o último espaço
            int tamanho = strlen(aux.chave);
            if(aux.chave[tamanho - 1] == ' ') {
                for(i = 0; i < tamanho - 1; i++) {
                    aux1.chave[i] = aux.chave[i];
                }
            }

            // Salva o caminho para se chegar à chave, a partir da raiz da árvore, na pilha p
            SalvaCaminho(raiz, aux1, &flag, &p);

            fprintf(arqSaida, "busca(%s): ", aux1.chave); // Impressão no arquivo

            int virgula = 0, virgula_anterior = 0; // Variável auxiliar que vai descobrir se o nó anterior e o posterior estão no mesmo nível
            int parenteses = 1; // Variável auxiliar que vai descobrir se o nó anterior e o posterior estão no mesmo nível

            registro *Aux;

            // Se o elemento está na lista
            if(!(VerificaPilhaRegistrosVazia(p))) {

                /* Procedimento para imprimir o caminho com parênteses e vírgula*/
                Aux = DesempilhaRegistro(&p);
                fprintf(arqSaida, "(%s", Aux->chave);

                while(!VerificaPilhaRegistrosVazia(p)) {
                    Aux = DesempilhaRegistro(&p);
                    virgula = Aux->qut_espacos;

                    if(virgula != virgula_anterior) {
                        fprintf(arqSaida, "(%s", Aux->chave);
                        parenteses++;
                    }
                    else
                        fprintf(arqSaida, ",%s", Aux->chave);

                    virgula_anterior = virgula;
                }
                // Imprime parênteses restantes
                do {
                    fprintf(arqSaida, ")");
                    parenteses--;
                } while(parenteses > 0);
                fprintf(arqSaida, "\n");
            }
            // Se o elemento não está na lista
            else {
                fprintf(arqSaida, "-1\n");
            }
        }

        // Se for para buscar as chaves que estão dentro de um intervalo
        else if(strcmp(Aux->operacao, "busca_intervalo") == 0) {

            // Registros que guardarão informações das páginas
            registro aux1; aux1.chave = malloc(MAX * sizeof(char));
            registro aux2; aux2.chave = malloc(MAX * sizeof(char));

            // Atribui para as variáveis registros de quais páginas se quer o intervalo
            char *pch;
            int cont = 0;
            pch = strtok(Aux->parametros, " \n");
            while(pch != NULL) {
                if(cont == 0) {
                    strcpy(aux1.chave, pch);
                    cont ++;
                }
                else {
                    strcpy(aux2.chave, pch);
                }
                pch = strtok (NULL, " \n");
            }

            fprintf(arqSaida, "busca_intervalo(%s,%s):\n", aux1.chave, aux2.chave);

            // Imprime o caminho entre dois nós
            CaminhoEntreDoisNos(raiz, aux1, aux2, arqSaida);
        }

        // Se for para buscar as palavras que estejam num intervalo de páginas
        else if(strcmp(Aux->operacao, "buscar_chaves_paginas") == 0) {


            // Procedimento para recuperar o número das páginas
            char *pch;
            int cont = 0, aux1, aux2;
            pch = strtok(Aux->parametros, " \n");
            while(pch != NULL) {
                if(cont == 0) {
                    aux1 = atoi(pch);
                    cont ++;
                }
                else {
                    aux2 = atoi(pch);
                }
                pch = strtok (NULL, " \n");
            }

            // Lista que vai conter os registros que estejam no intervalo de páginas
            TipoListaRegistros l; FazListaRegistroVazia(&l);
            SalvaRegistrosEmIntervaloDePaginas(&l, aux1, aux2, raiz);

            fprintf(arqSaida, "buscar_chaves_paginas(%d,%d):\n", aux1, aux2);

            // Lista que vai conter os registros da Lista anterior, porém, ordenados alfabeticamente
            TipoListaRegistros l2; FazListaRegistroVazia(&l2);

            OrdenaListaRegistros(&l, &l2);

            ImprimeListaRegistros(l2, arqSaida);
        }

        // Se for para inserir um novo nó
        else if(strcmp(Aux->operacao, "inserir") == 0) {

            // Declaração dos registros que vão conter pai e filho
            registro pai; pai.chave = malloc(MAX * sizeof(char));
            registro filho; filho.chave = malloc(MAX * sizeof(char));

            // Declaração de um tipopágina e de uma lista de páginas
            TipoPagina p;
            TipoLista l; FazListaPaginasVazia(&l);

            char *pch;
            int cont = 0;
            pch = strtok(Aux->parametros, " ");

            // Atribuição dos valores
            while(pch != NULL) {
                // Se a chave lida for o pai
                if(cont == 0) {
                    strcpy(filho.chave, pch);
                    cont ++;
                }
                // Se a chave lida for o filho
                else if(cont == 1){
                    strcpy(pai.chave, pch);
                    cont++;
                }
                // Se estiver lendo as páginas
                else {
                    p.numeroDaPagina = atoi(pch);
                    InsereItemNaListaPaginas(p, &l);
                }
                pch = strtok (NULL, " ");
            }

            filho.listaPaginas = l;

            // Inseração de um novo nó na árvore
            InsereNovo(filho, &raiz, pai);

        }

        // Se for para contar o número de páginas ímpares
        else if(strcmp(Aux->operacao, "contar_impares") == 0) {

            TipoListaRegistros l; // Lista que vai conter todas as páginas que contém alguma página ímpar, não contabiliza iguais
            FazListaRegistroVazia(&l);
            int cont;

            // Salva na lista todas as páginas ímpares
            ContaChavesEmPaginasImpares(raiz, &l);

            // Contabiliza o número de elementos que estão lista de páginas ímpares
            cont = ContaElementosNaLista(l);

            fprintf(arqSaida, "contar_impares: %d\n", cont);

        }
        if(Aux->Prox != NULL)
            fprintf(arqSaida, "\n");
    }

    FechaArquivo(arqEntrada);
    FechaArquivo(arqSaida);

    return 0;
}
