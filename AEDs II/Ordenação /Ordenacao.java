// ------- QUICKSORT -------------

void quicksort(int esq, int dir) {
  array [ ( dir + esq ) / 2 ];      
  int i esq, j dir, pivo;
  
  while (i <= j) {
    while (array[i] < pivo)  i++;   //pega  um numero maior que o pivô na metade inferior
    while (array[j] > pivo) j - -;   //valor menor que pivô na  metade superior

    if (i <= j){       //garante que dir e esq estão nos lados certos
    swap(i, j); i++;  j- -;    //coloca o valor maior na direita e o menor na esquerda do pivô
  }
  
  //chamada pra metade inferior
  if (esq < j)       
  quicksort(esq, j);
  
  //chamada pra metade superior
  if (i < dir)
  quicksort(i, dir);
}


// ------- BUBBLESORT -------------

  public void sort() {
		int n = array.length() ;
		for (int i = (n - 1); i > 0; i--) {
			for (int j = 0; j < i; j++) {
				if (array[j] > array[j + 1]) {
               swap(j, j+1);
				}
			}
		}
   }




// ------- INSERTION SORT -------------

  public void sort() {
	for (int i = 1; i < n; i++) {
	     int tmp = array[i];
           int j = i - 1;


           while ((j >= 0) && (array[j] > tmp)) {
               array[j + 1] = array[j];
               j--;
           }
          array[j + 1] = tmp;
    }
 }




// ------- SHELLORT -------------

public void shellSort(int[] array) {
    int n = array.length;


    // Começa com um gap (intervalo) grande e vai diminuindo
    for (int gap = n / 2; gap > 0; gap /= 2) {


        // Faz uma espécie de "insertion sort" com elementos distantes 'gap' posições
        for (int i = gap; i < n; i++) {
            int tmp = array[i];
            int j = i;


            // Desloca os elementos que estão 'gap' posições atrás
            while (j >= gap && array[j - gap] > tmp) {
                array[j] = array[j - gap];
                j -= gap;
            }


            // Insere o elemento na posição correta
            array[j] = tmp;
        }
    }
}        //é o insertionsort melhorado




// ------- MERGESORT ----------------------------------------
void mergesort(int esq, int dir) {      //funciona dividindo o array pela metade até chegar a subvetores unitários [95 15 42 4 23 16 8 77] --> [95] [15] [42] [4] [23] [16] [8] [77]
    if (esq < dir) {    //faz Θ(n log n)
        int meio = (esq + dir) / 2;
        mergesort(esq, meio);        // ordena metade esquerda
        mergesort(meio + 1, dir);    // ordena metade direita
        intercalar(esq, meio, dir);  // une as duas metades ordenadas
    }
}

void intercalar(int esq, int meio, int dir) {  //precisa de uma função auxiliar
    int nEsq = (meio + 1) - esq;
    int nDir = dir - meio;
    int[] arrayEsq = new int[nEsq + 1];
    int[] arrayDir = new int[nDir + 1];

    // Sentinelas (valores máximos para evitar estouro)
    arrayEsq[nEsq] = arrayDir[nDir] = 0x7FFFFFFF;

    // Copia dados das duas metades
    for (int iEsq = 0; iEsq < nEsq; iEsq++)
        arrayEsq[iEsq] = array[esq + iEsq];

    for (int iDir = 0; iDir < nDir; iDir++)
        arrayDir[iDir] = array[meio + 1 + iDir];

    // Faz a intercalação propriamente dita
    for (int iEsq = 0, iDir = 0, i = esq; i <= dir; i++) {
        array[i] = (arrayEsq[iEsq] <= arrayDir[iDir])
            ? arrayEsq[iEsq++] : arrayDir[iDir++];
    }
}


	
// ------- HEAPSORT -----------------------------------------


	
// ------- COUNTING SORT -----------------------------------

	

// ------- RADIXSORT -----------------------------------------



