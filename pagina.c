#include "pagina.h"
#include "registro.h"

void FazListaPaginasVazia(TipoLista *Lista) {
    Lista->Primeiro = (TipoPagina *)malloc(sizeof(TipoPagina));
    Lista->Ultimo = Lista->Primeiro;
    Lista->Primeiro->Prox = NULL;
}

int VerificaListaPaginasVazia(TipoLista Lista) {
    return(Lista.Primeiro == Lista.Ultimo);
}

void InsereItemNaListaPaginas(TipoPagina pagina, TipoLista *Lista) {
    Lista->Ultimo->Prox = (TipoPagina *)malloc(sizeof(TipoPagina));
    Lista->Ultimo = Lista->Ultimo->Prox;
    Lista->Ultimo->numeroDaPagina = pagina.numeroDaPagina;
    Lista->Ultimo->Prox = NULL;
}

int ContaPaginasImpares(TipoLista Lista) {
    TipoPagina *Aux;
    Aux = Lista.Primeiro->Prox;
    int i = 0;
    while (Aux != NULL ) {
        if(Aux->numeroDaPagina % 2 != 0) {
            i ++;
        }
        Aux = Aux->Prox;
    }
    return i;
}

int VerificaPaginaIntervalo(TipoLista Lista, int pag1, int pag2) {
    TipoPagina *Aux;
    Aux = Lista.Primeiro->Prox;
    while(Aux != NULL) {
        // Se a página está no intervalo
        if(Aux->numeroDaPagina >= pag1 && Aux->numeroDaPagina <= pag2)
            return 1;
        Aux = Aux->Prox;
    }
    // Se a página não está no intervalo
    return 0;
}
