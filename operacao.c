#include "operacao.h"

void FazListaOperacoesVazia(TipoListaOperacoes *Lista) {
    Lista->Primeiro = (TipoOperacao *)malloc(sizeof(TipoOperacao));
    Lista->Ultimo = Lista->Primeiro;
    Lista->Primeiro->Prox = NULL;
}

int VerificaListaOperacoesVazia(TipoListaOperacoes *Lista) {
    return(Lista->Primeiro == Lista->Ultimo);
}

void InsereOperacao(TipoOperacao operacao, TipoListaOperacoes *Lista) {
    Lista->Ultimo->Prox = (TipoOperacao *)malloc(sizeof(TipoOperacao));

    // Método que descobre qual será a operação e seus respectivos parâmetros
    // retira o \n da posição final da string
    operacao.operacao[strlen(operacao.operacao)-2] = '\0';

    int cont = 1;
    char *pch;
    pch = strtok(operacao.operacao, " ");
    while(pch != NULL) {
        if(cont == 1) {
            strcpy(Lista->Ultimo->Prox->operacao, pch);
            cont++;
        }
        else {
            strcat(Lista->Ultimo->Prox->parametros, pch);
            if(pch != NULL)
                strcat(Lista->Ultimo->Prox->parametros, " ");
        }
        pch = strtok (NULL, " ,");
    }

    Lista->Ultimo = Lista->Ultimo->Prox;
    Lista->Ultimo->Prox = NULL;
}

TipoOperacao *RemovePrimeiro(TipoListaOperacoes *Lista) {
    TipoOperacao *Aux;
    if(!VerificaListaOperacoesVazia(Lista)) {
        Aux = Lista->Primeiro->Prox;
        Lista->Primeiro->Prox = Aux->Prox;
        return Aux;
    }
    return NULL;
}
