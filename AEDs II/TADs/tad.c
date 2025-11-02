// ------ PILHA FLEXÍVEL ----------------------------------------------------------------------
typedef struct Celula {
    int elemento;
    struct Celula *prox;
} Celula;

typedef struct {
    Celula *topo;
} Pilha;

void iniciar(Pilha *p) {
    p->topo = NULL; // pilha começa vazia
}


// Inserção de elementos 
void inserir(Pilha *p, int x) {
    Celula *tmp = (Celula*) malloc(sizeof(Celula));
    tmp->elemento = x;
    tmp->prox = p->topo; // novo aponta para o antigo topo
    p->topo = tmp;       // agora esse é o topo da pilha
}

// Remoção de elementos
int remover(Pilha *p) {
    if (p->topo == NULL) {
        printf("ERRO: pilha vazia!\n");
        exit(1);
    }

    Celula *tmp = p->topo;
    int resp = tmp->elemento;
    p->topo = tmp->prox;
    free(tmp);
    return resp;
}

// busca de elementos
int buscar(Pilha *p, int x) {
    Celula *i;
    for(i = p->topo; i != NULL; i = i->prox) {
        if(i->elemento == x) {
            return 1; // encontrou
        }
    }
    return 0; // não encontrou
}



//----- FILA FLEXÍVEL  ------------------------------------------------------------------------
typedef struct Celula {
    int elemento;
    struct Celula *prox;
} Celula;

typedef struct Fila {
    Celula *primeiro; 
    Celula *ultimo;
} Fila;

void criarFila(Fila *f) {
    f->primeiro = (Celula*) malloc(sizeof(Celula));
    f->primeiro->prox = NULL;
    f->ultimo = f->primeiro;
}

// Inserção de elementos 
void inserir(Fila *f, int x) {
    f->ultimo->prox = (Celula*) malloc(sizeof(Celula));
    f->ultimo = f->ultimo->prox;
    f->ultimo->elemento = x;
    f->ultimo->prox = NULL;
}


// Remoção de elementos
int remover(Fila *f) {
    if (f->primeiro == f->ultimo) {
        printf("Erro: fila vazia!\n");
        exit(1);
    }

    Celula *tmp = f->primeiro->prox; // primeiro elemento real
    int elemento = tmp->elemento;

    f->primeiro->prox = tmp->prox;

    if (tmp == f->ultimo) {
        f->ultimo = f->primeiro; 
    }

    free(tmp);
    return elemento;
}


// busca de elementos

int existe(Fila *f, int x) {
    Celula *i;
    for (i = f->primeiro->prox; i != NULL; i = i->prox) {
        if (i->elemento == x) {
            return 1; // encontrado
        }
    }
    return 0; // não encontrado
}



//----- LISTA FLEXÍVEL SIMPLES -----------------------------------------------------------------
typedef struct Celula {
    int elemento;
    struct Celula* prox;
} Celula;

typedef struct Lista {
    Celula* primeiro;
    Celula* ultimo;
} Lista;

// ---------------------------
// Função para criar lista
// ---------------------------
void start(Lista* l) {
    l->primeiro = (Celula*) malloc(sizeof(Celula));
    l->primeiro->prox = NULL;
    l->ultimo = l->primeiro;
}

// Inserção de elementos 
void inserirInicio(Lista* l, int x) {
    Celula* tmp = (Celula*) malloc(sizeof(Celula));
    tmp->elemento = x;
    tmp->prox = l->primeiro->prox;
    l->primeiro->prox = tmp;

    if (l->primeiro == l->ultimo) {
        l->ultimo = tmp;
    }
}

void inserirFim(Lista* l, int x) {
    Celula* tmp = (Celula*) malloc(sizeof(Celula));
    tmp->elemento = x;
    tmp->prox = NULL;

    l->ultimo->prox = tmp;
    l->ultimo = tmp;
}


// Remoção de elementos

int removerInicio(Lista* l) {
    if (l->primeiro == l->ultimo) {
        printf("Erro: lista vazia!\n");
        exit(1);
    }

    Celula* tmp = l->primeiro->prox;
    int elemento = tmp->elemento;

    l->primeiro->prox = tmp->prox;
    if (tmp == l->ultimo)
        l->ultimo = l->primeiro;

    free(tmp);
    return elemento;
}

int removerFim(Lista* l) {
    if (l->primeiro == l->ultimo) {
        printf("Erro: lista vazia!\n");
        exit(1);
    }

    Celula* i;
    for (i = l->primeiro; i->prox != l->ultimo; i = i->prox);

    int elemento = l->ultimo->elemento;
    free(l->ultimo);
    l->ultimo = i;
    l->ultimo->prox = NULL;

    return elemento;
}

// ---------------------------
// Mostrar a lista
// ---------------------------
void mostrar(Lista* l) {
    printf("[ ");
    for (Celula* i = l->primeiro->prox; i != NULL; i = i->prox) {
        printf("%d ", i->elemento);
    }
    printf("]\n");
}

// busca de elementos
bool existe(Lista* l, int x) {
    for (Celula* i = l->primeiro->prox; i != NULL; i = i->prox) {
        if (i->elemento == x)
            return true;
    }
    return false;
}


//----- LISTA FLEXÍVEL ENCADEADA ---------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Estrutura da célula (nó) da lista dupla
typedef struct CelulaDupla {
    int elemento;
    struct CelulaDupla *prox;
    struct CelulaDupla *ant;
} CelulaDupla;

// Estrutura da lista dupla
typedef struct {
    CelulaDupla *primeiro;
    CelulaDupla *ultimo;
} ListaDupla;

// Função para inicializar a lista
void start(ListaDupla *lista) {
    lista->primeiro = (CelulaDupla*) malloc(sizeof(CelulaDupla));
    lista->primeiro->prox = NULL;
    lista->primeiro->ant = NULL;
    lista->ultimo = lista->primeiro;
}

void inserirInicio(ListaDupla *lista, int x) {
    CelulaDupla *tmp = (CelulaDupla*) malloc(sizeof(CelulaDupla));
    tmp->elemento = x;
    tmp->ant = lista->primeiro;
    tmp->prox = lista->primeiro->prox;

    if (lista->primeiro == lista->ultimo) {
        lista->ultimo = tmp;
    } else {
        lista->primeiro->prox->ant = tmp;
    }
    lista->primeiro->prox = tmp;
}

// Inserção de elementos 
void inserirFim(ListaDupla *lista, int x) {
    CelulaDupla *nova = (CelulaDupla*) malloc(sizeof(CelulaDupla));
    nova->elemento = x;
    nova->prox = NULL;
    nova->ant = lista->ultimo;
    lista->ultimo->prox = nova;
    lista->ultimo = nova;
}

int tamanho(ListaDupla *lista) { // Inserir por posição
    int tam = 0;
    for (CelulaDupla *i = lista->primeiro->prox; i != NULL; i = i->prox)
        tam++;
    return tam;
}

void inserir(ListaDupla *lista, int x, int pos) {// Inserir por posição
    int tam = tamanho(lista);
    if (pos < 0 || pos > tam) {
        printf("Erro: posição inválida!\n");
        return;
    }

    if (pos == 0) {
        inserirInicio(lista, x);
    } else if (pos == tam) {
        inserirFim(lista, x);
    } else {
        CelulaDupla *i = lista->primeiro;
        for (int j = 0; j < pos; j++, i = i->prox);

        CelulaDupla *tmp = (CelulaDupla*) malloc(sizeof(CelulaDupla));
        tmp->elemento = x;
        tmp->ant = i;
        tmp->prox = i->prox;
        i->prox->ant = tmp;
        i->prox = tmp;
    }
}


// Remoção de elementos
int removerInicio(ListaDupla *lista) {
    if (lista->primeiro == lista->ultimo) {
        printf("Erro: lista vazia!\n");
        exit(1);
    }
    CelulaDupla *tmp = lista->primeiro->prox;
    int elemento = tmp->elemento;

    lista->primeiro->prox = tmp->prox;
    if (tmp == lista->ultimo) {
        lista->ultimo = lista->primeiro;
    } else {
        tmp->prox->ant = lista->primeiro;
    }

    free(tmp);
    return elemento;
}

int removerFim(ListaDupla *lista) {
    if (lista->primeiro == lista->ultimo) {
        printf("Erro: lista vazia!\n");
        exit(1);
    }

    int elemento = lista->ultimo->elemento;
    CelulaDupla *tmp = lista->ultimo;
    lista->ultimo = lista->ultimo->ant;
    lista->ultimo->prox = NULL;
    free(tmp);
    return elemento;
}


int remover(ListaDupla *lista, int pos) {
    int tam = tamanho(lista);
    if (pos < 0 || pos >= tam) {
        printf("Erro: posição inválida!\n");
        exit(1);
    }

    if (pos == 0) return removerInicio(lista);
    if (pos == tam - 1) return removerFim(lista);

    CelulaDupla *i = lista->primeiro->prox;
    for (int j = 0; j < pos; j++, i = i->prox);

    int elemento = i->elemento;
    i->ant->prox = i->prox;
    i->prox->ant = i->ant;
    free(i);
    return elemento;
}

// busca de elementos
bool buscarElemento(ListaDupla *lista, int x) {
    for (CelulaDupla *i = lista->primeiro->prox; i != NULL; i = i->prox) {
        if (i->elemento == x) {
            printf("Elemento %d encontrado na lista.\n", x);
            return true;
        }
    }
    printf("Elemento %d NÃO encontrado na lista.\n", x);
    return false;
}

