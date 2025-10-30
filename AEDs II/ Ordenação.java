
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




// ------- QUICKSORT -------------




// ------- QUICKSORT -------------
