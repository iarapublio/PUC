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

class Celula {
    int elemento;
    Celula esq, dir, sup, inf; // ponteiros nas 4 direções

    // Construtor padrão
    Celula() {
        this(0);
    }

    // Construtor com valor
    Celula(int elemento) {
        this.elemento = elemento;
        this.esq = this.dir = this.sup = this.inf = null;
    }
}



class Matriz {
    Celula inicio;  // célula do canto superior esquerdo
    int linha, coluna;

    // Construtor padrão (matriz 3x3)
    public Matriz() {
        this(3, 3);
    }

    // Construtor que cria matriz com dimensões específicas
    public Matriz(int l, int c) {
        this.linha = l;
        this.coluna = c;
        this.inicio = construirMatriz(l, c);
    }

    // Método que constrói a estrutura encadeada da matriz
    private Celula construirMatriz(int l, int c) {
        Celula linhaInicial, atual, aux, acima;

        // cria a primeira célula
        linhaInicial = new Celula(0);
        Celula primeira = linhaInicial;

        // Cria a primeira linha (ligando horizontalmente)
        for (int j = 1; j < c; j++) {
            atual = new Celula(0);
            linhaInicial.dir = atual;
            atual.esq = linhaInicial;
            linhaInicial = atual;
        }

        // Cria as linhas abaixo (ligando vertical e horizontalmente)
        acima = primeira;
        for (int i = 1; i < l; i++) {
            // Cria a primeira célula da nova linha
            aux = new Celula(0);
            acima.inf = aux;
            aux.sup = acima;
            linhaInicial = aux;

            // Preenche a linha
            Celula acimaAux = acima.dir;
            for (int j = 1; j < c; j++) {
                atual = new Celula(0);
                linhaInicial.dir = atual;
                atual.esq = linhaInicial;
                // liga verticalmente
                atual.sup = acimaAux;
                acimaAux.inf = atual;
                // avança
                linhaInicial = atual;
                acimaAux = acimaAux.dir;
            }

            acima = acima.inf; // desce uma linha
        }

        return primeira;
    }
}


// Inserção de elementos 

public void setElemento(int i, int j, int valor) {
    Celula tmp = this.inicio;
    for (int x = 0; x < i; x++) tmp = tmp.inf;
    for (int y = 0; y < j; y++) tmp = tmp.dir;
    tmp.elemento = valor;
}

public int getElemento(int i, int j) {
    Celula tmp = this.inicio;
    for (int x = 0; x < i; x++) tmp = tmp.inf;
    for (int y = 0; y < j; y++) tmp = tmp.dir;
    return tmp.elemento;
}




// diagonal principal   e secundária

public void mostrarDiagonalPrincipal() {
    Celula tmp = this.inicio;
    while (tmp != null) {
        System.out.print(tmp.elemento + " ");
        if (tmp.inf != null && tmp.dir != null)
            tmp = tmp.inf.dir;
        else
            break;
    }
    System.out.println();
}

public void mostrarDiagonalSecundaria() {
    // ir até o canto superior direito
    Celula tmp = this.inicio;
    while (tmp.dir != null)
        tmp = tmp.dir;

    // descer diagonalmente para esquerda
    while (tmp != null) {
        System.out.print(tmp.elemento + " ");
        if (tmp.inf != null && tmp.esq != null)
            tmp = tmp.inf.esq;
        else
            break;
    }
    System.out.println();
}







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


 // classe arvore 
class ArvoreBinaria {
    private No raiz;

    public ArvoreBinaria() {
        raiz = null;
    }

    // Metodos Inserir 
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


//inserir com passagem de pai 
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

// iserir iterativo 
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

//--------------------ARVORE AVL -------------------------------

/**
 * Arvore binaria de pesquisa
 * @author Max do Val Machado
 */

public class AVL {
	private No raiz; // Raiz da arvore.

	/**
	 * Construtor da classe.
	 */
	public AVL() {
		raiz = null;
	}

	/**
	 * Metodo publico iterativo para pesquisar elemento.
	 * @param x Elemento que sera procurado.
	 * @return <code>true</code> se o elemento existir, <code>false</code> em caso
	 *         contrario.
	 */
	public boolean pesquisar(int x) {
		return pesquisar(x, raiz);
	}

	/**
	 * Metodo privado recursivo para pesquisar elemento.
	 * @param x Elemento que sera procurado.
	 * @param i No em analise.
	 * @return <code>true</code> se o elemento existir, <code>false</code> em caso
	 *         contrario.
	 */
	private boolean pesquisar(int x, No i) {
		boolean resp;
		if (i == null) {
			resp = false;
		} else if (x == i.elemento) {
			resp = true;
		} else if (x < i.elemento) {
			resp = pesquisar(x, i.esq);
		} else {
			resp = pesquisar(x, i.dir);
		}
		return resp;
	}

	/**
	 * Metodo publico iterativo para exibir elementos.
	 */
	public void caminharCentral() {
		System.out.print("[ ");
		caminharCentral(raiz);
		System.out.println("]");
	}

	/**
	 * Metodo privado recursivo para exibir elementos.
	 * @param i No em analise.
	 */
	private void caminharCentral(No i) {
		if (i != null) {
			caminharCentral(i.esq); // Elementos da esquerda.
			System.out.print(i.elemento + " "); // Conteudo do no.
			caminharCentral(i.dir); // Elementos da direita.
		}
	}

	/**
	 * Metodo publico iterativo para exibir elementos.
	 */
	public void caminharPre() {
		System.out.print("[ ");
		caminharPre(raiz);
		System.out.println("]");
	}

	/**
	 * Metodo privado recursivo para exibir elementos.
	 * @param i No em analise.
	 */
	private void caminharPre(No i) {
		if (i != null) {
			System.out.print(i.elemento + "(fator " + (No.getNivel(i.dir) - No.getNivel(i.esq)) + ") "); // Conteudo do no.
			caminharPre(i.esq); // Elementos da esquerda.
			caminharPre(i.dir); // Elementos da direita.
		}
	}

	/**
	 * Metodo publico iterativo para exibir elementos.
	 */
	public void caminharPos() {
		System.out.print("[ ");
		caminharPos(raiz);
		System.out.println("]");
	}

	/**
	 * Metodo privado recursivo para exibir elementos.
	 * @param i No em analise.
	 */
	private void caminharPos(No i) {
		if (i != null) {
			caminharPos(i.esq); // Elementos da esquerda.
			caminharPos(i.dir); // Elementos da direita.
			System.out.print(i.elemento + " "); // Conteudo do no.
		}
	}

	/**
	 * Metodo publico iterativo para inserir elemento.
	 * @param x Elemento a ser inserido.
	 * @throws Exception Se o elemento existir.
	 */
	public void inserir(int x) throws Exception {
		raiz = inserir(x, raiz);
	}

	/**
	 * Metodo privado recursivo para inserir elemento.
	 * @param x Elemento a ser inserido.
	 * @param i No em analise.
	 * @return No em analise, alterado ou nao.
	 * @throws Exception Se o elemento existir.
	 */
	private No inserir(int x, No i) throws Exception {
		if (i == null) {
			i = new No(x);
		} else if (x < i.elemento) {
			i.esq = inserir(x, i.esq);
		} else if (x > i.elemento) {
			i.dir = inserir(x, i.dir);
		} else {
			throw new Exception("Erro ao inserir!");
		}
		return balancear(i);
	}

	/**
	 * Metodo publico iterativo para remover elemento.
	 * @param x Elemento a ser removido.
	 * @throws Exception Se nao encontrar elemento.
	 */
	public void remover(int x) throws Exception {
		raiz = remover(x, raiz);
	}

	/**
	 * Metodo privado recursivo para remover elemento. 
	 * @param x Elemento a ser removido.
	 * @param i No em analise.
	 * @return No em analise, alterado ou nao.
	 * @throws Exception Se nao encontrar elemento.
	 */
	private No remover(int x, No i) throws Exception {
		if (i == null) {
			throw new Exception("Erro ao remover!");
		} else if (x < i.elemento) {
			i.esq = remover(x, i.esq);
		} else if (x > i.elemento) {
			i.dir = remover(x, i.dir);
		// Sem no a direita.
		} else if (i.dir == null) {
			i = i.esq;
		// Sem no a esquerda.
		} else if (i.esq == null) {
			i = i.dir;
		// No a esquerda e no a direita.
		} else {
			i.esq = maiorEsq(i, i.esq);
		}
		return balancear(i);
	}

	/**
	 * Metodo para trocar o elemento "removido" pelo maior da esquerda.
	 * @param i No que teve o elemento removido.
	 * @param j No da subarvore esquerda.
	 * @return No em analise, alterado ou nao.
	 */
	private No maiorEsq(No i, No j) {
		// Encontrou o maximo da subarvore esquerda.
		if (j.dir == null) {
			i.elemento = j.elemento; // Substitui i por j.
			j = j.esq; // Substitui j por j.ESQ.
		// Existe no a direita.
		} else {
			// Caminha para direita.
			j.dir = maiorEsq(i, j.dir);
		}
		return j;
	}

	private No balancear(No no) throws Exception {
		if (no != null) {
			int fator = No.getNivel(no.dir) - No.getNivel(no.esq);
			// Se balanceada
			if (Math.abs(fator) <= 1) {
				no.setNivel();
			// Se desbalanceada para a direita
			} else if (fator == 2) {
				int fatorFilhoDir = No.getNivel(no.dir.dir) - No.getNivel(no.dir.esq);
				// Se o filho a direita tambem estiver desbalanceado
				if (fatorFilhoDir == -1) {
					no.dir = rotacionarDir(no.dir);
				}
				no = rotacionarEsq(no);
			// Se desbalanceada para a esquerda
			} else if (fator == -2) {
				int fatorFilhoEsq = No.getNivel(no.esq.dir) - No.getNivel(no.esq.esq);
				// Se o filho a esquerda tambem estiver desbalanceado
				if (fatorFilhoEsq == 1) {
					no.esq = rotacionarEsq(no.esq);
				}
				no = rotacionarDir(no);
			} else {
				throw new Exception(
						"Erro no No(" + no.elemento + ") com fator de balanceamento (" + fator + ") invalido!");
			}
		}
		return no;
	}

	private No rotacionarDir(No no) {
		System.out.println("Rotacionar DIR(" + no.elemento + ")");
		No noEsq = no.esq;
		No noEsqDir = noEsq.dir;

		noEsq.dir = no;
		no.esq = noEsqDir;
		no.setNivel(); // Atualizar o nivel do no
		noEsq.setNivel(); // Atualizar o nivel do noEsq

		return noEsq;
	}

	private No rotacionarEsq(No no) {
		System.out.println("Rotacionar ESQ(" + no.elemento + ")");
		No noDir = no.dir;
		No noDirEsq = noDir.esq;

		noDir.esq = no;
		no.dir = noDirEsq;

		no.setNivel(); // Atualizar o nivel do no
		noDir.setNivel(); // Atualizar o nivel do noDir
		return noDir;
	}
}




//-------------------ARVORE DE ARVORE BINARIAS -----------------------------
//No 1

class No {
	public char elemento; // Conteudo do no.
	public No esq; // No da esquerda.
	public No dir; // No da direita.
   public No2 outro;
	
//Construtor da classe.

	No(char elemento) {
		this.elemento = elemento;
		this.esq = this.dir = null;
      this.outro = null;
	}

//Construtor da classe.
	No(char elemento, No esq, No dir) {
		this.elemento = elemento;
		this.esq = esq;
		this.dir = dir;
      this.outro = null;
	}
}

//No 2
class No2 {
	public String elemento; // Conteudo do no.
	public No2 esq; // No da esquerda.
	public No2 dir; // No da direita.
	
   //Construtor da classe.

	No2(String elemento) {
		this.elemento = elemento;
		this.esq = this.dir = null;
	}

	//Construtor da classe.

	No2(String elemento, No2 esq, No2 dir) {
		this.elemento = elemento;
		this.esq = esq;
		this.dir = dir;
	}
}

public class ArvoreArvore {
	private No raiz; // Raiz da arvore.

	/**
	 * Construtor da classe.
	 */
	public ArvoreArvore() {
		raiz = null;
      inserir('M');
      inserir('T');
      inserir('F');
      //os outros 23 caracteres.
	}

   public void inserir(char letra){
      //igualzinho (mesmo, de verdade) ao da árvore binária padrão!!!
   }


   public void inserir(String s){
      inserir(s, raiz);
   }

   public void inserir(String s, No i) throws Exception {
		if (i == null) {
         throw new Exception("Erro ao inserir: caractere invalido!");

      } else if (s.charAt(0) < i.elemento) {
         inserir(x, i.esq);

      } else if (s.charAt(0) > i.elemento) {
         inserir(x, i.dir);

      } else {
         i.outro = inserir(s, i.outro);
      }
   }


	private No2 inserir(String s, No2 i) throws Exception {
		if (i == null) {
         i = new No2(x);

      } else if (s.compareTo(i.elemento) < 0) {
         i.esq = inserir(x, i.esq);

      } else if (s.compareTo(i.elemento) > 0) {
         i.dir = inserir(x, i.dir);

      } else {
         throw new Exception("Erro ao inserir: elemento existente!");
      }

		return i;
	}


   public void mostrar(){
      mostrar(raiz);
   }

   public void mostrar(No i){
      if (i != null){
         mostrar(i.esq);
         //System.out.println("Letra: " + i.elemento);
         mostrar(i.outra);
         mostrar(i.dir);
      }
   }

   public void mostrar(No2 i){
      if (i != null){
         mostrar(i.esq);
         System.out.println(i.elemento);
         mostrar(i.dir);
      }
   }



   public boolean hasStringTam10(){
      return hasStringTam10(raiz);
   }

   public boolean hasStringTam10(No i){
      boolean resp = false;
      if(i != null){
         resp = hasStringTam10(i.outro) || hasStringTam10(i.esq) || hasStringTam10(i.dir);
      }
      return resp;
   }

   public boolean hasStringTam10(No2 i){
      boolean resp = false;
      if(i != null){
         resp = i.elemento.length() == 10 || hasStringTam10(i.esq) || hasStringTam10(i.dir);
      }
      return resp;
   }


   public boolean hasStringTam10(char c){
      return hasStringTam10(raiz, c);
   }

   public boolean hasStringTam10(No i, char c){
      boolean resp;
		if (i == null) { 
         resp = false;

      } else if (c < i.elemento) { 
         resp = hasStringTam10(i.esq, c); 

      } else if (c > i.elemento) { 
         resp = hasStringTam10(i.dir, c); 
      
      } else { 
         resp = hasStringTam10(i.outro); 
      }
      return resp;
   } 


//pesquisar
	public boolean pesquisar(String elemento) {
		return pesquisar(raiz, elemento);
	}

	private boolean pesquisar(No no, String x) {
      boolean resp;
		if (no == null) { 
         resp = false;

      } else if (x.charAt(0) < no.elemento) { 
         resp = pesquisar(no.esq, x); 

      } else if (x.charAt(0) > no.elemento) { 
         resp = pesquisar(no.dir, x); 
      
      } else { 
         resp = pesquisarSegundaArvore(no.outro, x); 
      }
      return resp;
	}

	private boolean pesquisarSegundaArvore(No2 no, String x) {
      boolean resp;
		if (no == null) { 
         resp = false;

      } else if (x.compareTo(no.elemento) < 0) { 
         resp = pesquisarSegundaArvore(no.esq, x); 

      } else if (x.compareTo(no.elemento) > 0) { 
         resp = pesquisarSegundaArvore(no.dir, x); 

      } else { 
         resp = true; 
      }
      return resp;
	}


   public int contPalavra(char letra){
      return contPalavra(letra, raiz);
   }

   public int contPalavra(char letra, No i) throws Exception {
      int resp = 0;

		if (i == null) {
         throw new Exception("Erro ao pesquisar: caractere invalido!");

      } else if (letra < i.elemento) {
         resp = contPalavra(letra, i.esq);

      } else if (letra > i.elemento) {
         resp = contPalavra(letra, i.dir);

      } else {
         resp = contPalavra(i.outro);
      }

      return resp;
   }

   public int contPalavra(No2 i){
      int resp = 0;
      if(i != null){
         resp = 1 + contPalavra(i.esq) + contPalavra(i.dir);
      }
      return resp;
   }
}





//-----------------------HASH------------------------


//-------Hash com rehash---

class HashRehash {
   int tabela[];
   int tamTabela;

   public HashRehash (int tamTabela) {
      this.tamTabela = tamTabela;
      tabela = new int[tamTabela];
      for (int i = 0; i < tamTabela; i++) {
         tabela[i] = -1;
      }
   }

   public int h(int x) {
      return (x % tamTabela);
   }

   public void inserir(int x) {
      int pos = h(x);
      while (tabela[pos] != -1) {
         pos = (pos + 1) % tamTabela; // rehash
      }
      tabela[pos] = x;
   }

   public boolean pesquisar(int x) {
      int pos = h(x);
      while (tabela[pos] != -1) {
         if (tabela[pos] == x) return true;
         pos = (pos + 1) % tamTabela;
      }
      return false;
   }
}



//--------Hash com tabela --

class Hash {
   int tabela[]; 
   int tamTabela;
   int tamReserva;
   int reservaPos;

   public Hash (int tamTabela, int tamReserva) {
      this.tamTabela = tamTabela;
      this.tamReserva = tamReserva;
      tabela = new int[tamTabela + tamReserva];
      for (int i = 0; i < tamTabela + tamReserva; i++) {
         tabela[i] = -1;
      }
      reservaPos = 0;
   }

   public int h(int x) {
      return (x % tamTabela);
   }

   public void inserir(int x) {
      int pos = h(x);
      if (tabela[pos] == -1) {
         tabela[pos] = x;
      } else if (reservaPos < tamReserva) {
         tabela[tamTabela + reservaPos] = x;
         reservaPos++;
      }
   }

   public boolean pesquisar(int x) {
      int pos = h(x);
      if (tabela[pos] == x) return true;
      for (int i = 0; i < reservaPos; i++) {
         if (tabela[tamTabela + i] == x) 
            return true;
      }
      return false;
   }
}




//-----------Hash com lista--------
public class HashIndiretoLista {
   Lista tabela[];
   int tamanho;
   final int NULO = -1;

   public HashIndiretoLista() {
      this(7);
   }

   public HashIndiretoLista(int tamanho) {
      this.tamanho = tamanho;
      tabela = new Lista[tamanho];
      for (int i = 0; i < tamanho; i++) {
         tabela[i] = new Lista();
      }
   }

   public int h(int elemento) {
      return elemento % tamanho;
   }

   boolean pesquisar(int elemento) {
      int pos = h(elemento);
      return tabela[pos].pesquisar(elemento);
   }

   public void inserirInicio(int elemento) {
      int pos = h(elemento);
      tabela[pos].inserirInicio(elemento);
   }

   public int remover(int elemento) {
      int resp = NULO;
      if (pesquisar(elemento) == false) {
         throw new Exception("Erro ao remover!");
      } else {
         int pos = h(elemento);
         resp = tabela[pos].remover(elemento);
      }
      return resp;
   }
}   
