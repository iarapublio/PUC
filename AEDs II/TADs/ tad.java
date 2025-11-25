// ------ PILHA FLEXÍVEL --------------------------------------------------------------
class Celula {
    public int elemento;
    public Celula prox;

    public Celula() {   //construtor vazio
        this(0);
    }

    public Celula(int x) {   // construtor com dados
        this.elemento = x;  // dado
        this.prox = null;    // ponteiro pro próximo elemento
    }
}

// classe 
class Pilha {
   private Celula topo;

   public Pilha() {
      topo = null;  // No começo a pilha está vazia
   }

  // Inserção de elementos 
  public void inserir(int x) {
    Celula tmp = new Celula(x);
    tmp.prox = topo;  //aponta a nova célula pra anterior 
    topo = tmp;   //insere no topo
    tmp = null; //libera o espaço
  	}

  // Remoção de elementos
   public int remover() {
     if (topo == null)
       throw new Exception("Erro!");
     
     int elemento = topo.elemento;  //guarda o elemento a ser reitrado pra retorno
     Celula tmp = topo;   //tmp guarda o endereço do topo
     topo = topo.prox;   // a celula seguinte vira o topo
     tmp.prox = null;    // libera o espaço do antigo topo
     tmp = null; //libera o espaço do antigo topo
     return elemento;
   }

  // busca de elementos
public boolean buscar(int x) {
    for (Celula i = topo; i != null; i = i.prox) {
        if (i.elemento == x) {
            return true; // achou
        }
    }
    return false; // percorreu tudo e não achou
}


//----- FILA FLEXÍVEL  ------------------------------------------------------------------------

class Fila {
  private Celula primeiro, ultimo;
  
  public Fila () {
    primeiro = new Celula();
    ultimo = primeiro;
}

   
// Inserção de elementos 
  public void inserir(int x) {
    ultimo.prox = new Celula(x);
    ultimo = ultimo.prox;
}

// Remoção de elementos
public int remover(){
   if (primeiro == ultimo)  //fila vazia
      throw new Exception("Erro: fila vazia!");
  
  Celula tmp = primeiro;
  primeiro.prox = primeiro;
  int elemento = primeiro.elemento
  tmp.prox = null;
  tmp = null;
  return elemento;  //retorna o atual primeiro elemento da lista
}

// busca de elementos
public boolean existe(int x) {
    for (Celula i = primeiro.prox; i != null; i = i.prox) {
        if (i.elemento == x) {
            return true;
        }
    }
    return false;
}


//----- LISTA FLEXÍVEL SIMPLES -----------------------------------------------------------------
class Lista {
  private Celula primeiro, ultimo;
  
  public Lista () {
    primeiro = new Celula();
    ultimo = primeiro;
  }
  

  
// Inserção de elementos 
  public void inserir(int x, int pos) throws Exception {  //insere em uma posição específica
    int tamanho = tamanho();
      if (pos < 0 || pos > tamanho) throw new Exception("Erro!");  //celula vazia
      else if (pos == 0) inserirInicio(x);   //caso a posição dada seja a primeira
      else if (pos == tamanho) inserirFim(x);  //caso a posição seja a final
        
        else {
            Celula i = primeiro;
            for (int j = 0; j < pos; j++, i = i.prox); //percorre todas as celulas até achar a posição -1
            Celula tmp = new Celula(x);
            tmp.prox = i.prox;  //faz tmp apontar pro elemento depois de onde ele deve ser inserido  [tmp] --> [prox]
            i.prox = tmp;  //faz i apontar pra tmp [i] --> [tmp] --> [prox]
            tmp = i = null;  //libera
        }
}

  }

  
  public void inserirInicio(int x) {
    Celula tmp = new Celula(x);
    tmp.prox = primeiro.prox;   //copia o conteudo de primeiro pra tmp
    primeiro.prox = tmp;    // transforma 
    if (primeiro == ultimo) {
        ultimo = tmp;
    }
    tmp = null;
}

  }

// Remoção de elementos
  public int removerFim() throws Exception {
    if (primeiro == ultimo)    //lista vazia
        throw new Exception("Erro!");
    
    Celula i;
    for (i = primeiro; i.prox != ultimo; i = i.prox);  //chega no penúltimo elemento
    int elemento = ultimo.elemento;  //guarda o elemento a ser retirado pra retorno
    ultimo = i;   // refedine o último como o penúltimo
    i = ultimo.prox = null;  //libera i e o ponteiro do último elemento
    return elemento;
}

  }
  public int remover(int pos) throws Exception {
    int elemento, tamanho = tamanho();
    
    if (primeiro == ultimo || pos < 0 || pos >= tamanho) throw new Exception("Erro!");
    else if (pos == 0) elemento = removerInicio();
    else if (pos == tamanho - 1) elemento = removerFim();
      
    else {
        Celula i = primeiro;
        for (int j = 0; j < pos; j++, i = i.prox);
        Celula tmp = i.prox;
        elemento = tmp.elemento;
        i.prox = tmp.prox;
        tmp.prox = null;
        i = tmp = null;
    }
    return elemento;
}
 }
}
    
// busca de elementos
public boolean existe(int x) {
    for (Celula i = primeiro.prox; i != null; i = i.prox) { // começa na primeira célula real (não no nó cabeça)
        if (i.elemento == x) {
            return true; // achou o valor
        }
    }
    return false; // percorreu tudo e não achou
}

    
//----- LISTA FLEXÍVEL ENCADEADA ---------------------------------------------------------------
class CelulaDupla {
   public int elemento;
   public CelulaDupla prox, ant;

   public CelulaDupla() { this(0); }

   public CelulaDupla(int x) {
      this.elemento = x;
      this.prox = this.ant = null;
   }
}

class ListaDupla {
private CelulaDupla primeiro, ultimo;
public ListaDupla () {
 primeiro = new CelulaDupla();
 ultimo = primeiro;
}

// Inserção de elementos 
public void inserirInicio(int x) { ... }
public void inserirFim(int x) { ... }
public void inserir(int x, int pos) { ... }

// Remoção de elementos
public int removerInicio() { ... }
public int removerFim() { ... }
public int remover(int pos) { ... }

// busca de elementos

//----- MATRIZ FLEXÍVEL  -----------------------------------------------------------------------

// Inserção de elementos 

// Remoção de elementos

// busca de elementos




//----- ARVORE BINARIA  -----------------------------------------------------------------------

    class No {
    public int elemento;
    public No esq, dir;

    public No(int elemento){
        this.elemento = elemento;
        esq = null;
        dir = null;
    }
        
}


 //   ---- classe arvore ---
class ArvoreBinaria {
    private No raiz;

    public ArvoreBinaria() {
        raiz = null;
    }

    //------- Metodos Inserir ----------
    public void inserir(int x) throws Exception {
        raiz = inserir(x, raiz);
    }

    
    private No inserir(int x, No i) throws Exception {
    
        if (i == null) {
            i = new No(x);
    
        } else if (x < i.elemento) {
            i.esq = inserir(x, i.esq);
    
        } else if (x > i.elemento) {
            i.dir = inserir(x, i.dir);
    
        } else {
            throw new Exception("Elemento já existente");
        }
    
        return i;
    }

    }
}


//------ inserir com passagem de pai -----
void inserirPai(int x) throws Exception {
 if (raiz == null) {
 raiz = new No(x);
 } else if (x < raiz.elemento) {
 inserirPai(x, raiz.esq, raiz);
 } else if (x > raiz.elemento) {
 inserirPai(x, raiz.dir, raiz);
 } else {
 throw new Exception(“Erro!”);
 }
 }

void inserirPai(int x, No i, No pai) throws Exception {
     if (i == null) {
         If (x < pai.elemento){
         pai.esq = new No(x);
     } else {
         pai.dir = new No(x);
     }
     } else if (x < i.elemento) {
     inserirPai(x, i.esq, i);
     } else if (x > i.elemento) {
     inserirPai(x, i.dir, i);
     } else {
     throw new Exception(“Erro!”);
     }
 }

//------------- VERSAO ITERATIVA --------------
public void inserirIterativo(int x) throws Exception {

    if (raiz == null) {
        raiz = new No(x);
        return;
    }

    No atual = raiz;
    No pai = null;

    while (atual != null) {
        pai = atual;

        if (x < atual.elemento) {
            atual = atual.esq;
        } else if (x > atual.elemento) {
            atual = atual.dir;
        } else {
            throw new Exception("Elemento já existente");
        }
    }

    if (x < pai.elemento) {
        pai.esq = new No(x);
    } else {
        pai.dir = new No(x);
    }
}

//----------ARVORE BINARIA
class ArvoreBinaria {
     No raiz;
     ArvoreBinaria() { raiz = null; }
     void inserir(int x) { }
     boolean pesquisar(int x) { }
     void remover(int x) { }
     void caminharCentral() { }
     void caminharPre() { }
     void caminharPos() { }
}





    

    
