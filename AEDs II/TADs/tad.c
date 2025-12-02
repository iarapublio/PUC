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

// função para criar lista
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

// Mostrar a lista
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



//---------------MATRIZ FLEXÍVEL-------------------------


typedef struct Celula {
    int elemento;
    struct Celula *esq;
    struct Celula *dir;
    struct Celula *sup;
    struct Celula *inf;
} Celula;


typedef struct {
    Celula *inicio; 
    int linha, coluna;
} Matriz;

Celula* novaCelula(int valor) {
    Celula *c = (Celula*) malloc(sizeof(Celula));
    c->elemento = valor;
    c->esq = c->dir = c->sup = c->inf = NULL;
    return c;
}

Celula* construirMatriz(int l, int c) {
    Celula *primeira = novaCelula(0);
    Celula *linha = primeira;
    Celula *aux, *acima;

    // ----- cria a primeira linha -----
    for(int j = 1; j < c; j++) {
        Celula *nova = novaCelula(0);
        linha->dir = nova;
        nova->esq = linha;
        linha = nova;
    }

    // ----- cria as linhas restantes -----
    acima = primeira;

    for(int i = 1; i < l; i++) {
        // primeira célula da nova linha
        aux = novaCelula(0);
        acima->inf = aux;
        aux->sup = acima;
        linha = aux;

        Celula *acimaAux = acima->dir;

        // cria o resto da linha
        for(int j = 1; j < c; j++) {
            Celula *nova = novaCelula(0);
            linha->dir = nova;
            nova->esq = linha;

            // liga vertical
            nova->sup = acimaAux;
            acimaAux->inf = nova;

            linha = nova;
            acimaAux = acimaAux->dir;
        }

        acima = acima->inf; // desce
    }

    return primeira;
}

void inicializarMatriz(Matriz *m, int l, int c) {
    m->linha = l;
    m->coluna = c;
    m->inicio = construirMatriz(l, c);
}


//------inserção de elemento------------------
void setElemento(Matriz *m, int i, int j, int valor) {
    Celula *tmp = m->inicio;

    for (int x = 0; x < i; x++) tmp = tmp->inf;
    for (int y = 0; y < j; y++) tmp = tmp->dir;

    tmp->elemento = valor;
}


int getElemento(Matriz *m, int i, int j) {
    Celula *tmp = m->inicio;

    for (int x = 0; x < i; x++) tmp = tmp->inf;
    for (int y = 0; y < j; y++) tmp = tmp->dir;

    return tmp->elemento;
}


//diagonal principal e secundária
void mostrarDiagonalPrincipal(Matriz *m) {
    Celula *tmp = m->inicio;

    while (tmp != NULL) {
        printf("%d ", tmp->elemento);

        if (tmp->inf != NULL && tmp->dir != NULL)
            tmp = tmp->inf->dir;
        else
            break;
    }

    printf("\n");
}



void mostrarDiagonalSecundaria(Matriz *m) {
    Celula *tmp = m->inicio;

    while (tmp->dir != NULL)
        tmp = tmp->dir;

    while (tmp != NULL) {
        printf("%d ", tmp->elemento);

        if (tmp->inf != NULL && tmp->esq != NULL)
            tmp = tmp->inf->esq;
        else
            break;
    }

    printf("\n");
}



// main
int main() {
    Matriz m1, m2, res;

    inicializarMatriz(&m1, 3, 3);
    inicializarMatriz(&m2, 3, 3);

    // preenchendo
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            setElemento(&m1, i, j, i + j);
            setElemento(&m2, i, j, (i + 1) * (j + 2));
        }
    }

    res = soma(&m1, &m2);

    printf("Diagonal Principal:\n");
    mostrarDiagonalPrincipal(&res);

    printf("Diagonal Secundária:\n");
    mostrarDiagonalSecundaria(&res);

    return 0;
}


//-----------------------ARVORE BINARIA --------------------
#include <stdio.h>
#include <stdlib.h>

// =========================
//   ESTRUTURA DO NÓ
// =========================
typedef struct No {
    int elemento;
    struct No *esq;
    struct No *dir;
} No;


// =========================
//   ESTRUTURA DA ÁRVORE
// =========================
typedef struct {
    No *raiz;
} Arvore;


// Função para criar um novo nó
No* novoNo(int x) {
    No *temp = (No*) malloc(sizeof(No));
    temp->elemento = x;
    temp->esq = NULL;
    temp->dir = NULL;
    return temp;
}


// ===============================
//   INSERIR (recursivo simples)
// ===============================
No* inserirRec(No *i, int x) {
    if (i == NULL) {
        i = novoNo(x);

    } else if (x < i->elemento) {
        i->esq = inserirRec(i->esq, x);

    } else if (x > i->elemento) {
        i->dir = inserirRec(i->dir, x);

    } else {
        printf("Erro: elemento %d já existe\n", x);
    }

    return i;
}

void inserir(Arvore *arv, int x) {
    arv->raiz = inserirRec(arv->raiz, x);
}


// ========================================
//   INSERIR COM PASSAGEM DE PAI (recursivo)
// ========================================
void inserirPaiRec(No *i, No *pai, int x) {
    if (i == NULL) {
        if (x < pai->elemento)
            pai->esq = novoNo(x);
        else
            pai->dir = novoNo(x);

    } else if (x < i->elemento) {
        inserirPaiRec(i->esq, i, x);

    } else if (x > i->elemento) {
        inserirPaiRec(i->dir, i, x);

    } else {
        printf("Erro: elemento %d já existe\n", x);
    }
}

void inserirPai(Arvore *arv, int x) {
    if (arv->raiz == NULL) {
        arv->raiz = novoNo(x);

    } else if (x < arv->raiz->elemento) {
        inserirPaiRec(arv->raiz->esq, arv->raiz, x);

    } else if (x > arv->raiz->elemento) {
        inserirPaiRec(arv->raiz->dir, arv->raiz, x);

    } else {
        printf("Erro: elemento %d já existe\n", x);
    }
}


// ============================
//   INSERIR ITERATIVO
// ============================
void inserirIterativo(Arvore *arv, int x) {
    if (arv->raiz == NULL) {
        arv->raiz = novoNo(x);
        return;
    }

    No *atual = arv->raiz;
    No *pai = NULL;

    while (atual != NULL) {
        pai = atual;

        if (x < atual->elemento) {
            atual = atual->esq;

        } else if (x > atual->elemento) {
            atual = atual->dir;

        } else {
            printf("Erro: elemento %d já existe\n", x);
            return;
        }
    }

    if (x < pai->elemento) {
        pai->esq = novoNo(x);

    } else {
        pai->dir = novoNo(x);
    }
}


//   TESTE
int main() {
    Arvore arv;
    arv.raiz = NULL;

    inserir(&arv, 10);
    inserir(&arv, 5);
    inserir(&arv, 15);

    inserirPai(&arv, 7);
    inserirIterativo(&arv, 20);

    printf("Inserções feitas com sucesso\n");

    return 0;
}





//-----------------------ARVORE AVL -------------------------------------- 

#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int elemento;
    int nivel;  // equivalente ao "altura" do Java
    struct No *esq;
    struct No *dir;
} No;

// =========================
//   FUNÇÕES AUXILIARES
// =========================

// cria um novo nó
No* novoNo(int x) {
    No *n = (No*) malloc(sizeof(No));
    n->elemento = x;
    n->esq = n->dir = NULL;
    n->nivel = 1;  // nível inicial = 1
    return n;
}

// obtém nível (altura)
int getNivel(No *n) {
    return (n == NULL ? 0 : n->nivel);
}

// atualiza nível
void setNivel(No *n) {
    if (n != NULL) {
        int esq = getNivel(n->esq);
        int dir = getNivel(n->dir);
        n->nivel = (esq > dir ? esq : dir) + 1;
    }
}

// fator de balanceamento
int fatorBalanceamento(No *n) {
    return getNivel(n->dir) - getNivel(n->esq);
}


// =========================
//   ROTAÇÕES
// =========================

// Rotação à direita
No* rotacionarDir(No *no) {
    printf("Rotacionar DIR(%d)\n", no->elemento);

    No *noEsq = no->esq;
    No *noEsqDir = noEsq->dir;

    noEsq->dir = no;
    no->esq = noEsqDir;

    setNivel(no);
    setNivel(noEsq);

    return noEsq;
}

// Rotação à esquerda
No* rotacionarEsq(No *no) {
    printf("Rotacionar ESQ(%d)\n", no->elemento);

    No *noDir = no->dir;
    No *noDirEsq = noDir->esq;

    noDir->esq = no;
    no->dir = noDirEsq;

    setNivel(no);
    setNivel(noDir);

    return noDir;
}


// =========================
//   BALANCEAMENTO
// =========================
No* balancear(No *no) {
    if (no == NULL) return NULL;

    int fator = fatorBalanceamento(no);

    // balanceada
    if (abs(fator) <= 1) {
        setNivel(no);
        return no;
    }

    // desbalanceada para a direita
    if (fator == 2) {
        int fatorFilho = fatorBalanceamento(no->dir);
        if (fatorFilho == -1) {
            no->dir = rotacionarDir(no->dir);
        }
        return rotacionarEsq(no);
    }

    // desbalanceada para a esquerda
    if (fator == -2) {
        int fatorFilho = fatorBalanceamento(no->esq);
        if (fatorFilho == 1) {
            no->esq = rotacionarEsq(no->esq);
        }
        return rotacionarDir(no);
    }

    printf("Erro: fator de balanceamento invalido\n");
    return no;
}


// =========================
//   INSERÇÃO
// =========================
No* inserir(No *i, int x) {
    if (i == NULL) {
        return novoNo(x);
    } else if (x < i->elemento) {
        i->esq = inserir(i->esq, x);
    } else if (x > i->elemento) {
        i->dir = inserir(i->dir, x);
    } else {
        printf("Erro ao inserir: elemento existe (%d)\n", x);
        return i;
    }

    return balancear(i);
}


// =========================
//   REMOÇÃO
// =========================
No* maiorEsq(No *i, No *j) {
    if (j->dir == NULL) {
        i->elemento = j->elemento;
        No *temp = j->esq;
        free(j);
        return temp;
    }
    j->dir = maiorEsq(i, j->dir);
    return balancear(j);
}

No* remover(No *i, int x) {
    if (i == NULL) {
        printf("Erro ao remover: elemento nao encontrado (%d)\n", x);
        return NULL;
    } 
    if (x < i->elemento) {
        i->esq = remover(i->esq, x);

    } else if (x > i->elemento) {
        i->dir = remover(i->dir, x);

    } else { // achou o elemento
        if (i->dir == NULL) {
            No *temp = i->esq;
            free(i);
            return temp;

        } else if (i->esq == NULL) {
            No *temp = i->dir;
            free(i);
            return temp;

        } else {
            i->esq = maiorEsq(i, i->esq);
        }
    }

    return balancear(i);
}


// =========================
//   PESQUISA
// =========================
int pesquisar(No *i, int x) {
    if (i == NULL) return 0;
    if (x == i->elemento) return 1;
    if (x < i->elemento) return pesquisar(i->esq, x);
    return pesquisar(i->dir, x);
}


// =========================
//   CAMINHAMENTOS
// =========================
void caminharCentral(No *i) {
    if (i != NULL) {
        caminharCentral(i->esq);
        printf("%d ", i->elemento);
        caminharCentral(i->dir);
    }
}

void caminharPre(No *i) {
    if (i != NULL) {
        printf("%d(fator %d) ", i->elemento, fatorBalanceamento(i));
        caminharPre(i->esq);
        caminharPre(i->dir);
    }
}

void caminharPos(No *i) {
    if (i != NULL) {
        caminharPos(i->esq);
        caminharPos(i->dir);
        printf("%d ", i->elemento);
    }
}


// =========================
//   TESTE
// =========================
int main() {
    No *raiz = NULL;

    raiz = inserir(raiz, 10);
    raiz = inserir(raiz, 20);
    raiz = inserir(raiz, 30);
    raiz = inserir(raiz, 40);
    raiz = inserir(raiz, 50);
    raiz = inserir(raiz, 25);

    printf("\nCaminhar Central: ");
    caminharCentral(raiz);

    printf("\nCaminhar Pre: ");
    caminharPre(raiz);

    printf("\nCaminhar Pos: ");
    caminharPos(raiz);

    printf("\n\nRemovendo 40...\n");
    raiz = remover(raiz, 40);

    printf("\nCaminhar Central: ");
    caminharCentral(raiz);

    return 0;
}






//-----------------------ARVORE DE ARVORES BINARIAS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//       NO PRINCIPAL
typedef struct No2 {
    char elemento[100];
    struct No2 *esq;
    struct No2 *dir;
} No2;

typedef struct No {
    char elemento;
    struct No *esq;
    struct No *dir;
    No2 *outro;
} No;


//    FUNÇÕES DA ARVORE 2

// cria novo No2
No2* novoNo2(const char *str) {
    No2 *n = (No2*) malloc(sizeof(No2));
    strcpy(n->elemento, str);
    n->esq = n->dir = NULL;
    return n;
}

// inserir na árvore de strings
No2* inserirNo2(const char *s, No2 *i) {
    if (i == NULL) {
        i = novoNo2(s);

    } else if (strcmp(s, i->elemento) < 0) {
        i->esq = inserirNo2(s, i->esq);

    } else if (strcmp(s, i->elemento) > 0) {
        i->dir = inserirNo2(s, i->dir);

    } else {
        printf("Erro ao inserir: elemento existente!\n");
        exit(1);
    }

    return i;
}

// pesquisar na árvore de strings
int pesquisarNo2(No2 *no, const char *x) {
    if (no == NULL)
        return 0;

    if (strcmp(x, no->elemento) < 0)
        return pesquisarNo2(no->esq, x);

    else if (strcmp(x, no->elemento) > 0)
        return pesquisarNo2(no->dir, x);

    return 1;
}

// contar palavras na árvore de strings
int contPalavraNo2(No2 *i) {
    if (i == NULL) return 0;
    return 1 + contPalavraNo2(i->esq) + contPalavraNo2(i->dir);
}

// mostrar palavras
void mostrarNo2(No2 *i) {
    if (i != NULL) {
        mostrarNo2(i->esq);
        printf("%s\n", i->elemento);
        mostrarNo2(i->dir);
    }
}

//     FUNÇÕES ARVORE 1

// criar No principal
No* novoNo(char letra) {
    No *n = (No*) malloc(sizeof(No));
    n->elemento = letra;
    n->esq = n->dir = NULL;
    n->outro = NULL;
    return n;
}

// inserir letra (igual ABB padrão)
No* inserirLetra(No *i, char letra) {
    if (i == NULL) {
        i = novoNo(letra);

    } else if (letra < i->elemento) {
        i->esq = inserirLetra(i->esq, letra);

    } else if (letra > i->elemento) {
        i->dir = inserirLetra(i->dir, letra);
    }

    return i;
}



//ARVORE ARVORE

typedef struct {
    No *raiz;
} ArvoreArvore;


// construtor
void initArvore(ArvoreArvore *a) {
    a->raiz = NULL;

    // inserir manualmente como no Java
    a->raiz = inserirLetra(a->raiz, 'M');
    a->raiz = inserirLetra(a->raiz, 'T');
    a->raiz = inserirLetra(a->raiz, 'F');
    // ... inserir outras letras A–Z
}


// inserir string
void inserirString(ArvoreArvore *a, const char *s, No *i) {
    if (i == NULL) {
        printf("Erro ao inserir: caractere invalido!\n");
        exit(1);

    } else if (s[0] < i->elemento) {
        inserirString(a, s, i->esq);

    } else if (s[0] > i->elemento) {
        inserirString(a, s, i->dir);

    } else {
        i->outro = inserirNo2(s, i->outro);
    }
}

void inserir(ArvoreArvore *a, const char *s) {
    inserirString(a, s, a->raiz);
}


//============================
//     PESQUISAR STRING
//============================
int pesquisarAux(No *no, const char *x) {
    if (no == NULL)
        return 0;

    if (x[0] < no->elemento)
        return pesquisarAux(no->esq, x);

    else if (x[0] > no->elemento)
        return pesquisarAux(no->dir, x);

    return pesquisarNo2(no->outro, x);
}

int pesquisar(ArvoreArvore *a, const char *x) {
    return pesquisarAux(a->raiz, x);
}



//          MOSTRAR

void mostrarAux(No *i) {
    if (i != NULL) {
        mostrarAux(i->esq);
        mostrarNo2(i->outro);
        mostrarAux(i->dir);
    }
}

void mostrar(ArvoreArvore *a) {
    mostrarAux(a->raiz);
}


//     CONTAR PALAVRAS
int contPalavraAux(char letra, No *i) {
    if (i == NULL) {
        printf("Erro ao pesquisar: caractere invalido!\n");
        exit(1);

    } else if (letra < i->elemento)
        return contPalavraAux(letra, i->esq);

    else if (letra > i->elemento)
        return contPalavraAux(letra, i->dir);

    return contPalavraNo2(i->outro);
}

int contPalavra(ArvoreArvore *a, char letra) {
    return contPalavraAux(letra, a->raiz);
}

//MAIN

int main() {
    ArvoreArvore a;
    initArvore(&a);

    inserir(&a, "MEL");
    inserir(&a, "MACA");
    inserir(&a, "TIGRE");
    inserir(&a, "FADA");

    printf("Mostrar árvore:\n");
    mostrar(&a);

    printf("Pesquisar MEL → %d\n", pesquisar(&a, "MEL"));
    printf("Pesquisar TUBARAO → %d\n", pesquisar(&a, "TUBARAO"));

    printf("Palavras com M: %d\n", contPalavra(&a, 'M'));

    return 0;
}


//----------------------- HASH ------------------------------
//----------Hash com rehash ----
#include <stdio.h>

#define NULO -1

typedef struct {
    int *tabela;
    int m;
} Hash;

// Construtor "padrão"
void Hash_init_default(Hash *h) {
    Hash_init(h, 13);
}

// Construtor com parâmetro m
void Hash_init(Hash *h, int m) {
    h->m = m;
    h->tabela = (int*) malloc(sizeof(int) * m);

    for (int i = 0; i < m; i++) {
        h->tabela[i] = NULO;
    }
}

//  hash principal
int h(Hash *hash, int elemento) {
    return elemento % hash->m;
}

// Rehash 
int reh(Hash *hash, int elemento) {
    return (++elemento) % hash->m;
}

// Inserir 
int inserir(Hash *hash, int elemento) {
    int resp = 0;

    if (elemento != NULO) {
        int pos = h(hash, elemento);

        if (hash->tabela[pos] == NULO) {
            hash->tabela[pos] = elemento;
            resp = 1;
        } else {
            pos = reh(hash, elemento);
            if (hash->tabela[pos] == NULO) {
                hash->tabela[pos] = elemento;
                resp = 1;
            }
        }
    }

    return resp;
}

// Pesquisar
int pesquisar(Hash *hash, int elemento) {
    int resp = 0;
    int pos = h(hash, elemento);

    if (hash->tabela[pos] == elemento) {
        resp = 1;
    } 
    else if (hash->tabela[pos] != NULO) {
        pos = reh(hash, elemento);
        if (hash->tabela[pos] == elemento) {
            resp = 1;
        }
    }

    return resp;
}

// Remover
int remover(Hash *hash, int elemento) {
    int resp = 0;
    return resp;
}

// Apenas para testar
void mostrar(Hash *h) {
    for (int i = 0; i < h->m; i++) {
        if (h->tabela[i] == NULO)
            printf("[%d] -\n", i);
        else
            printf("[%d] %d\n", i, h->tabela[i]);
    }
}

int main() {
    Hash h;
    Hash_init(&h, 13);

    inserir(&h, 5);
    inserir(&h, 18);
    inserir(&h, 26);

    mostrar(&h);

    printf("Pesquisar 18: %d\n", pesquisar(&h, 18));
    printf("Pesquisar 40: %d\n", pesquisar(&h, 40));

    free(h.tabela);
    return 0;
}


//---------Hash com tabela ------

#include <stdio.h>
#include <stdlib.h>

#define NULO -1

typedef struct {
    int *tabela;
    int m1, m2, m;
    int reserva;
} Hash;

// Construtor padrão: Hash h = Hash_default();
void Hash_default(Hash *h) {
    Hash_init(h, 13, 7);
}

// Construtor geral: Hash_init(&h, m1, m2);
void Hash_init(Hash *h, int m1, int m2) {
    h->m1 = m1;
    h->m2 = m2;
    h->m = m1 + m2;
    h->tabela = (int*) malloc(sizeof(int) * h->m);

    // Preenche SOMENTE a tabela principal com -1 (igual ao seu Java)
    for (int i = 0; i < h->m1; i++) {
        h->tabela[i] = NULO;
    }

    // A área de reserva não é inicializada no seu Java
    // portanto deixamos lixo de memória mesmo — igualzinho!
    
    h->reserva = 0;
}

// Função hash
int h_func(Hash *h, int elemento) {
    return elemento % h->m1;
}

// Inserir
int inserir(Hash *h, int elemento) {
    int resp = 0;

    if (elemento != NULO) {
        int pos = h_func(h, elemento);

        if (h->tabela[pos] == NULO) {
            h->tabela[pos] = elemento;
            resp = 1;
        }
        else if (h->reserva < h->m2) {
            h->tabela[h->m1 + h->reserva] = elemento;
            h->reserva++;
            resp = 1;
        }
    }

    return resp;
}

// Pesquisar
int pesquisar(Hash *h, int elemento) {
    int resp = 0;
    int pos = h_func(h, elemento);

    if (h->tabela[pos] == elemento) {
        resp = 1;
    }
    else if (h->tabela[pos] != NULO) {
        for (int i = 0; i < h->reserva; i++) {
            if (h->tabela[h->m1 + i] == elemento) {
                resp = 1;
                i = h->reserva; // quebra o loop (igual ao seu Java)
            }
        }
    }

    return resp;
}

// Remover (estrutura idêntica ao seu Java)
int remover(Hash *h, int elemento) {
    int resp = 0;
    // ...
    return resp;
}

// Função opcional só para visualizar a tabela
void mostrar(Hash *h) {
    printf("Tabela principal:\n");
    for (int i = 0; i < h->m1; i++) {
        printf("[%d] %d\n", i, h->tabela[i]);
    }

    printf("Reserva:\n");
    for (int i = 0; i < h->m2; i++) {
        printf("[%d] %d\n", h->m1 + i, h->tabela[h->m1 + i]);
    }
}

// Exemplo de uso
int main() {
    Hash h;
    Hash_init(&h, 13, 7);

    inserir(&h, 10);
    inserir(&h, 23);
    inserir(&h, 36);
    inserir(&h, 49);

    mostrar(&h);

    printf("Pesquisar 23: %d\n", pesquisar(&h, 23));
    printf("Pesquisar 99: %d\n", pesquisar(&h, 99));

    free(h.tabela);
    return 0;
}





//---------Hash com lista -------

#include <stdio.h>
#include <stdlib.h>

#define NULO -1

//===========================
//    LISTA (igual ao Java)
//===========================

typedef struct Celula {
    int elemento;
    struct Celula *prox;
} Celula;

typedef struct {
    Celula *primeiro; // sentinela
    Celula *ultimo;
} Lista;

// Inicializa a lista (com sentinela)
void Lista_init(Lista *l) {
    l->primeiro = (Celula*) malloc(sizeof(Celula));
    l->primeiro->elemento = NULO;
    l->primeiro->prox = NULL;
    l->ultimo = l->primeiro;
}

// Inserir no início
void Lista_inserirInicio(Lista *l, int x) {
    Celula *tmp = (Celula*) malloc(sizeof(Celula));
    tmp->elemento = x;
    tmp->prox = l->primeiro->prox;
    l->primeiro->prox = tmp;

    if (l->primeiro == l->ultimo) {
        l->ultimo = tmp;
    }
}

// Pesquisar elemento
int Lista_pesquisar(Lista *l, int x) {
    for (Celula *i = l->primeiro->prox; i != NULL; i = i->prox) {
        if (i->elemento == x) return 1;
    }
    return 0;
}

// Remover elemento específico
int Lista_remover(Lista *l, int x) {
    Celula *i = l->primeiro;
    while (i->prox != NULL && i->prox->elemento != x) {
        i = i->prox;
    }

    if (i->prox != NULL) {
        Celula *tmp = i->prox;
        int elemento = tmp->elemento;
        i->prox = tmp->prox;

        if (tmp == l->ultimo) {
            l->ultimo = i;
        }
        free(tmp);
        return elemento;
    }

    return NULO;
}

//===========================
//       HASH INDIRETO
//===========================

typedef struct {
    Lista *tabela;
    int tamanho;
} HashIndiretoLista;

// Construtor padrão
void HashIndiretoLista_init_default(HashIndiretoLista *h) {
    HashIndiretoLista_init(h, 7);
}

// Construtor geral
void HashIndiretoLista_init(HashIndiretoLista *h, int tamanho) {
    h->tamanho = tamanho;
    h->tabela = (Lista*) malloc(sizeof(Lista) * tamanho);

    for (int i = 0; i < tamanho; i++) {
        Lista_init(&h->tabela[i]);
    }
}

// Função hash
int h_func(HashIndiretoLista *h, int elemento) {
    return elemento % h->tamanho;
}

// Pesquisar
int Hash_pesquisar(HashIndiretoLista *h, int elemento) {
    int pos = h_func(h, elemento);
    return Lista_pesquisar(&h->tabela[pos], elemento);
}

// Inserir
void Hash_inserirInicio(HashIndiretoLista *h, int elemento) {
    int pos = h_func(h, elemento);
    Lista_inserirInicio(&h->tabela[pos], elemento);
}

// Remover
int Hash_remover(HashIndiretoLista *h, int elemento) {
    if (!Hash_pesquisar(h, elemento)) {
        printf("Erro ao remover!\n");
        exit(1);
    }

    int pos = h_func(h, elemento);
    return Lista_remover(&h->tabela[pos], elemento);
}

// Mostrar tabela (opcional)
void Hash_mostrar(HashIndiretoLista *h) {
    for (int i = 0; i < h->tamanho; i++) {
        printf("[%d] -> ", i);
        for (Celula *c = h->tabela[i].primeiro->prox; c != NULL; c = c->prox) {
            printf("%d -> ", c->elemento);
        }
        printf("NULL\n");
    }
}

//===========================
//         MAIN
//===========================

int main() {
    HashIndiretoLista h;
    HashIndiretoLista_init(&h, 7);

    Hash_inserirInicio(&h, 10);
    Hash_inserirInicio(&h, 17);
    Hash_inserirInicio(&h, 24);

    Hash_mostrar(&h);

    printf("Pesquisar 17: %d\n", Hash_pesquisar(&h, 17));
    printf("Remover 17: %d\n", Hash_remover(&h, 17));

    Hash_mostrar(&h);

    return 0;
}






