#include "arvoreB.h"

sbb *Cria_No (registro reg) {
    sbb *no = (sbb *)malloc(sizeof(sbb));
    no->reg = reg;
    no->esq = NULL;
    no->dir = NULL;
    no->esqtipo = SBB_VERTICAL;
    no->dirtipo = SBB_VERTICAL;
    return no;
}

void ee(sbb **ptr) {
    sbb *no = *ptr;
    sbb *esq = no->esq;

    no->esq = esq->dir;
    esq->dir = no;
    esq->esqtipo = SBB_VERTICAL;
    no->esqtipo = SBB_VERTICAL;
    *ptr = esq;
}

void dd(sbb **ptr) {
    sbb *no = *ptr;
    sbb *dir = no->dir;

    no->dir = dir->esq;
    dir->esq = no;
    dir->dirtipo = SBB_VERTICAL;
    no->dirtipo = SBB_VERTICAL;
    *ptr = dir;
}

void ed(sbb **ptr) {
    sbb *no = *ptr;
    sbb *esq = no->esq;
    sbb *dir = esq->dir;

    esq->dir = dir->esq;
    no->esq = dir->dir;
    dir->esq = esq;
    dir->dir = no;
    esq->dirtipo = SBB_VERTICAL;
    no->esqtipo = SBB_VERTICAL;
    *ptr = dir;
}

void de(sbb **ptr) {
    sbb *no = *ptr;
    sbb *dir = no->dir;
    sbb *esq = dir->esq;

    no->dir = esq->esq;
    dir->esq = esq->dir;
    esq->esq = no;
    esq->dir = dir;
    dir->esqtipo = SBB_VERTICAL;
    no->dirtipo = SBB_VERTICAL;
    *ptr = esq;
}

void iinsere(registro reg, sbb **ptr, int *incli, int *fim) {
    /* adiciona, pois encontrou uma folha */
    if(*ptr == NULL)
        iinsere_aqui(reg, ptr, incli, fim);
    /* busca na sub-árvore esquerda */
    else if (strcmp(reg.chave, (*ptr)->reg.chave) < 0) {
        iinsere(reg, &((*ptr)->esq), &((*ptr)->esqtipo), fim);
        if (*fim) return;
        if ((*ptr)->esqtipo == SBB_VERTICAL) {
            *fim = TRUE;
        }
        else if ((*ptr)->esq->esqtipo == SBB_HORIZONTAL) {
            ee(ptr);
            *incli = SBB_HORIZONTAL;
        }
        else if ((*ptr)->esq->dirtipo == SBB_HORIZONTAL) {
            ed(ptr);
            *incli = SBB_HORIZONTAL;
        }
    }
    /* busca na sub-árvore direita */
    else if (strcmp(reg.chave, (*ptr)->reg.chave) > 0) {
        iinsere (reg, &((*ptr)->dir), &((*ptr)->dirtipo), fim);
        if (*fim) return;
        if ((*ptr)->dirtipo == SBB_VERTICAL) {
            *fim = TRUE;
        }
        else if ((*ptr)->dir->dirtipo == SBB_HORIZONTAL) {
            dd(ptr);
            *incli = SBB_HORIZONTAL;
        }
        else if ((*ptr)->dir->esqtipo == SBB_HORIZONTAL) {
            de(ptr);
            *incli = SBB_HORIZONTAL;
        }
    }
    /* chave já existe */
    else {
        printf("erro: a chave [%s] já está na árvore.\n", reg.chave);
        *fim = TRUE;
    }
}

void iinsere_aqui(registro reg, sbb **ptr, int *incli, int *fim) {
    sbb *no = malloc(sizeof(sbb));
    no->reg = reg;
    no->esq = NULL;
    no->dir = NULL;
    no->esqtipo = SBB_VERTICAL;
    no->dirtipo = SBB_VERTICAL;
    *ptr = no;
    *incli = SBB_HORIZONTAL;
    *fim = FALSE;
    //printf("Inserido: %s\n", reg.chave);
}

void insere(registro reg, sbb **raiz, registro *caminho, int flag) {
    int fim = FALSE;
    int inclinacao = SBB_VERTICAL;

    // Se o registro a ser inserido é o primeiro do vetor de registros
    if(flag == 1) {
        iinsere(reg, raiz, &inclinacao, &fim);
        flag = 0;
    }
    // Se o registro for o segundo ou posterior
    else {
        // Se o registro estiver no mesmo nível
        if(reg.qut_espacos == (*raiz)->reg.qut_espacos) {
            iinsere(reg, raiz, &inclinacao, &fim);
        }
        // Se os registros estão em níveis diferentes
        else {
            // Se a chave a ser inserida não está no mesmo nível da raiz, procura pelo último elemento no nível da raiz e vai para sua sub-árvore
            // Procurar pelo caminho a seguir, baseado no vetor de últimos registros
            // O registro é o último?
            if(strcmp((*raiz)->reg.chave, caminho[(*raiz)->reg.qut_espacos].chave) == 0 && reg.qut_espacos == (*raiz)->reg.qut_espacos + 1) {
                iinsere(reg, &(*raiz)->subarvore, &inclinacao, &fim);
                return;
            }
            else  if(strcmp((*raiz)->reg.chave, caminho[(*raiz)->reg.qut_espacos].chave) == 0 && (*raiz)->subarvore != NULL) {
                insere(reg, &(*raiz)->subarvore, caminho, 0);
                return;
            }
            // Se não for
            else if(strcmp((*raiz)->reg.chave, caminho[(*raiz)->reg.qut_espacos].chave) < 0) {
                insere(reg, &(*raiz)->dir, caminho, 0);
                return;
            }
            else {
                insere(reg, &(*raiz)->esq, caminho, 0);
                return;
            }
        }
    }
}

void InsereNovo(registro filho, sbb **raiz, registro pai) {
    if((*raiz) == NULL) return;
    InsereNovo(filho, &(*raiz)->esq, pai);
    // Verifica a existencia do elemento pai, se ele existe, insere na sua subarvore
    if(strcmp((*raiz)->reg.chave, pai.chave) == 0) {
        // Passar como parâmetro para para a função iinsere FALSE E SBB_VERTICAL
        filho.qut_espacos = (*raiz)->reg.qut_espacos + 1;
        int fim = FALSE;
        int inclinacao = SBB_VERTICAL;
        iinsere(filho, &(*raiz)->subarvore, &fim, &inclinacao);
    }
    InsereNovo(filho, &(*raiz)->subarvore, pai);
    InsereNovo(filho, &(*raiz)->dir, pai);
}

void inicializa(sbb **raiz) {
    *raiz = NULL;
}

void ContaChavesEmPaginasImpares(sbb *raiz, TipoListaRegistros *l) {
    int cont = 0;
    if(raiz == NULL) return;
    ContaChavesEmPaginasImpares(raiz->esq, l);
    cont = ContaPaginasImpares(raiz->reg.listaPaginas); // Se achou uma página com páginas ímpares, insere na lista
    if(cont) {
        // Verifica se a chave já está na lista de páginas ímpares
        //if(VerificaExistenciaRegistro(raiz->reg, l) == 0) { // Se o registro não existe na lista de páginas ímpares, insere na lista
            InsereRegistroLista(raiz->reg, l);
        //}
    }
    ContaChavesEmPaginasImpares(raiz->subarvore, l);
    ContaChavesEmPaginasImpares(raiz->dir, l);
}

int SalvaCaminho(sbb *raiz, registro chave, int *flag, TipoPilhaRegistros *p) {
    if(raiz == NULL) return *flag;
    if(strcmp(raiz->reg.chave, chave.chave) == 0) {
        *flag = 1;
        EmpilhaRegistro(raiz->reg, p);
        return *flag;
    }
    SalvaCaminho(raiz->esq, chave, flag, p);
    if(*flag) {
        EmpilhaRegistro(raiz->reg, p);
        return *flag;
    }
    SalvaCaminho(raiz->subarvore, chave, flag, p);
    if(*flag) {
        EmpilhaRegistro(raiz->reg, p);
        return *flag;
    }
    SalvaCaminho(raiz->dir, chave, flag, p);
    if(*flag) {
        EmpilhaRegistro(raiz->reg, p);
        return *flag;
    }
    if(*flag == 0)
        return (-1);
    else
        return (*flag);
}

void SalvaRegistrosEmIntervaloDePaginas(TipoListaRegistros *v, int pag1, int pag2, sbb *raiz) {
    if(raiz == NULL) return;
    SalvaRegistrosEmIntervaloDePaginas(v, pag1, pag2, raiz->esq);
    // Verifica se a chave está no intervalo de páginas
    if(VerificaPaginaIntervalo(raiz->reg.listaPaginas, pag1, pag2) == 1) {
        // Se a chave está no intervalo de páginas, insere ela em uma lista
        InsereRegistroLista(raiz->reg, v);
    }
    SalvaRegistrosEmIntervaloDePaginas(v, pag1, pag2, raiz->subarvore);
    SalvaRegistrosEmIntervaloDePaginas(v, pag1, pag2, raiz->dir);
}

void CaminhoEntreDoisNos(sbb *raiz, registro reg_1, registro reg_2, FILE *arqSaida) {


    TipoPilhaRegistros p; FazPilhaRegistroVazia(&p);
    TipoPilhaRegistros q; FazPilhaRegistroVazia(&q);

    int flag = 0;

    // Guarda o caminho que foi feita para se chegar do nó raiz principal da árvore até nó desejado
    SalvaCaminho(raiz, reg_1, &flag, &p);
    // Reinicia a flag para zero, com o objetivo de guardar um novo caminho
    flag = 0;
    // Guarda o caminho que foi feita para se chegar do nó raiz principal da árvore até nó desejado
    SalvaCaminho(raiz, reg_2, &flag, &q);

    // Criação de registros auxiliares
    registro *reg1, *reg2, *reg3;

    // Atribui o primeiro elemento da pilha p (a primeira a ser preenchida) para reg1
    reg1 = DesempilhaRegistro(&p);

    // Atribui o primeiro elemento da pilha q (a segunda e última a ser preenchida) para reg2
    reg2 = DesempilhaRegistro(&q);

    // Registro auxiliar
    reg3 = (registro *)malloc(sizeof(registro));

    reg3->chave = (char *)malloc(MAX * sizeof(char));

    TipoPilhaRegistros inversa; FazPilhaRegistroVazia(&inversa);

    // Percorre as duas pilhas ao mesmo tempo, enquanto o registro das duas, na mesma posião, forem iguais, vai desempilhando e
    // para somente quando os registros são diferentes.
    while(!VerificaPilhaRegistrosVazia(p) && !VerificaPilhaRegistrosVazia(q) && strcmp(reg1->chave, reg2->chave) == 0) {
        // Armazena sempre o último registro lido em um registro auxiliar reg3
        strcpy(reg3->chave, reg1->chave);

        // Continua a desempilhar
        reg1 = DesempilhaRegistro(&p);
        reg2 = DesempilhaRegistro(&q);
    }

    // Como a ordem de impressão é da chave da esquerda para a chave da direita, imprime último registro lido reg1 (que será o primeiro diferente) em uma pilha,
    // que terá a ordem inversa do caminho original para se chegar de um nó a um outro
    if(strcmp(reg1->chave, reg2->chave) != 0)
        EmpilhaRegistro(*reg1, &inversa);

    // Empilha os registros de reg1 em ordem inversa
     while(!VerificaPilhaRegistrosVazia(p)) {
        EmpilhaRegistro(*DesempilhaRegistro(&p), &inversa);
    }

    // Se a pilha inversa não estiver vazia, desempilha ela e imprime todos os elementos. (Elementos da subárvore da esquerda)
    while(!VerificaPilhaRegistrosVazia(inversa)) {
        fprintf(arqSaida, " %s\n", DesempilhaRegistro(&inversa)->chave);
    }

    // Último registro lido igual nas duas pilhas anteriores, portanto, é o nó que conecta as duas subárvores. (Ponto de ligação do caminho)
    if(strcmp(reg1->chave, reg2->chave) != 0) {
        fprintf(arqSaida, " %s\n", reg3->chave);
    }

    // Imprime o primeiro registro diferente na subárvore da direita
    fprintf(arqSaida, " %s\n", reg2->chave);

    // Se a subárvore da direita não estiver vazia, desempilha e imprime todos os seus elementos.
    while(!VerificaPilhaRegistrosVazia(q)) {
        fprintf(arqSaida, " %s\n", DesempilhaRegistro(&q)->chave);
    }
}
