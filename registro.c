#include "registro.h"

void PreencheVetorRegistros(registro *v, FILE *arqEntrada) {

    int posicao_no_vetor = 0;       // Armazena a posição atual do vetor
    int i = 0;                      // Variável auxiliar
    int cont = 0;                   // Contador de ocorrências do caracter espaço, por linha
    int Primeira_Palavra_Linha = 1; // Flag indicando se a palavra lida é a primeira da string
    char *pch;                      // Variável auxiliar para se utilizar a função STRTOK
    char *a;                        // Variável que vai conter a chave lida do arquivo, sem espaços
    char b[MAX];                    // Variável auxiliar
    char s[MAX];                    // Variável que contém a linha lida do arquivo
    TipoLista lista;
    TipoPagina pagina;
    FazListaPaginasVazia(&lista);

    /* Método para preencher o vetor de registros*/
    while(fgets(s, MAX, arqEntrada) != NULL && s[1] != '\n') {
        // Divisão do arquivo pelo separador vírgula, transformando em um vetor de strings
        pch = strtok(s, ",");
        // Percorrer o vetor de strings
        while (pch != NULL) {
            // Se for a primeira palavra é necessário retirar e contar o número de espaços
            if(Primeira_Palavra_Linha ==  1) {
                for(i = 0; i < strlen(pch); i++) {
                    if(pch[i] == ' ') cont ++;
                    Primeira_Palavra_Linha++;
                }
                strcpy(b, pch);
            }
            else {
                pagina.numeroDaPagina = atoi(pch);
                InsereItemNaListaPaginas(pagina, &lista);
            }
            pch = strtok (NULL, ", ");
        }
        // Após ter lido a linha, o contador é reiniciado para a primeira palavra
        Primeira_Palavra_Linha = 1;
        a =  strtok(b, " ");

        // Aloca espaço para uma nova palavra
        v[posicao_no_vetor].chave = (char *)malloc(MAX * sizeof(char));

        // Preenche a estrutura
        strcpy(v[posicao_no_vetor].chave, a);
        v[posicao_no_vetor].listaPaginas = lista;
        v[posicao_no_vetor].qut_espacos = cont;

        // Incrementa para a próxima posição no vetor
        posicao_no_vetor ++;

        // Reinicia o contador de espaços e faz uma nova lista
        cont = 0;
        FazListaPaginasVazia(&lista);
    }
    /* Fim do método*/

}

void PreencheVetorUltimoElemento(registro *ultimos_por_nivel, int pos, registro *vetor_registros) {

    ultimos_por_nivel[vetor_registros[pos].qut_espacos] = vetor_registros[pos];
}

registro *CaminhoParaInsercao(registro *ultimos_por_nivel, int pos, registro *vetor_registros) {

    // Faz a atualização do mapa chamando a função abaixo
    PreencheVetorUltimoElemento(ultimos_por_nivel, pos, vetor_registros);
    // Retorna o mapa atualizado
    return ultimos_por_nivel;
}

void FazPilhaRegistroVazia(TipoPilhaRegistros *Pilha){
    Pilha->Topo = (registro*) malloc(sizeof(registro));
    Pilha->Fundo = Pilha->Topo;
    Pilha->Topo->Prox = NULL;
    Pilha->Tamanho = 0;
}

int VerificaPilhaRegistrosVazia(TipoPilhaRegistros Pilha){
    return (Pilha.Topo == Pilha.Fundo);
}

void EmpilhaRegistro(registro x, TipoPilhaRegistros *Pilha) {
    registro *Aux;
    Aux = (registro*) malloc(sizeof(registro));
    Pilha->Topo->chave = (char *)malloc(MAX * sizeof(char));
    strcpy(Pilha->Topo->chave, x.chave);
    Pilha->Topo->listaPaginas = x.listaPaginas;
    Pilha->Topo->qut_espacos = x.qut_espacos;
    Aux->Prox = Pilha->Topo;
    Pilha->Topo = Aux;
    Pilha->Tamanho++;
}

registro *DesempilhaRegistro(TipoPilhaRegistros *Pilha) {
    registro *q, *Item;
    if (VerificaPilhaRegistrosVazia(*Pilha)) {
        printf("Erro: lista vazia\n");
        return NULL;
    }

    q = Pilha->Topo;
    Pilha->Topo = q->Prox;
    Item = q->Prox;
    free(q);  Pilha->Tamanho--;

    return Item;
}

void FazListaRegistroVazia(TipoListaRegistros *Lista) {
    Lista->Primeiro = (registro *)malloc(sizeof(registro));
    Lista->Ultimo = Lista->Primeiro;
    Lista->Primeiro->Prox = NULL;
}

int VerificaListaRegistrosVazia(TipoListaRegistros *Lista) {
    return(Lista->Primeiro == Lista->Ultimo);
}

void InsereRegistroLista(registro r, TipoListaRegistros *Lista) {
    Lista->Ultimo->Prox = (registro *)malloc(sizeof(registro));
    Lista->Ultimo = Lista->Ultimo->Prox;
    Lista->Ultimo->chave = (char *)malloc(MAX * sizeof(char));
    Lista->Ultimo->chave = r.chave;
    Lista->Ultimo->listaPaginas = r.listaPaginas;
    Lista->Ultimo->qut_espacos = r.qut_espacos;
    Lista->Ultimo->Prox = NULL;
}

void ImprimeListaRegistros(TipoListaRegistros l, FILE *arqSaida) {

    registro *Aux;
    Aux = l.Primeiro->Prox;
    while(Aux != NULL) {
        fprintf(arqSaida, " %s\n", Aux->chave);
        Aux = Aux->Prox;
    }
}

int VerificaExistenciaRegistro(registro r, TipoListaRegistros *l) {

    registro *Aux;
    Aux = l->Primeiro->Prox;
    while(Aux != NULL) {
        // Se achou um registro igual
        if(strcmp(r.chave, Aux->chave) == 0) {
            return(1);
        }
        Aux = Aux->Prox;
    }
    return(0);
}

int ContaElementosNaLista(TipoListaRegistros l) {

    int i = 0;
    registro *Aux;

    Aux = l.Primeiro->Prox;

    while(Aux != NULL) {
        i++;
        Aux = Aux->Prox;
    }
    return i;
}

void OrdenaListaRegistros(TipoListaRegistros *l1, TipoListaRegistros *Lista) {

    registro *anterior;
    registro *Menor;
    registro *Aux;
    int tamanho = 0;

    Aux = l1->Primeiro->Prox;

    while(Aux != NULL) {
        tamanho++;
        Aux = Aux->Prox;
    }

    // Percorre a lista, ordenando com o auxílio de uma sublista
    while(tamanho > 0 && l1->Primeiro->Prox != NULL) {
        Aux = l1->Primeiro->Prox;
        Menor = Aux;
        while(Aux != NULL) {
            // acha o menor
            if(strcmp(Aux->chave, Menor->chave) < 0)
                Menor = Aux;
            Aux = Aux->Prox;
        }
        //printf("\n%s\n", Menor->chave);
        InsereRegistroLista((*Menor), Lista);

        Aux = l1->Primeiro->Prox;
        // Retira o menor
        // Se for o primeiro elemento
        if(strcmp(Menor->chave, Aux->chave) == 0) {
            l1->Primeiro->Prox = l1->Primeiro->Prox->Prox;
        }
        else {
            anterior = Aux;
            Aux = Aux->Prox;
            while(Aux != NULL) {
                // quanda achar o menor, retira
                if(strcmp(Aux->chave, Menor->chave) == 0) {
                    anterior->Prox = Aux->Prox;
                    break;
                }
                anterior = Aux;
                Aux = Aux->Prox;
            }
            tamanho--;
        }
    }
}
