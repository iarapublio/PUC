// ------ BUBBLE SORT ----------------
void bubbleSort(int array[], int n) {
    int i, j, temp;
    
    // Percorre todo o vetor
    for (i = 0; i < n - 1; i++) {
        // Últimos i elementos já estarão no lugar certo a cada iteração
        for (j = 0; j < n - i - 1; j++) {
            // Compara elementos adjacentes
            if (array[j] > array[j + 1]) {
                // Troca de posição se estiverem fora de ordem
                temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}


// ------- QUICKSORT -------------
void quicksort(int array[], int low, int high) {
    if (low < high) {
        // faz a partição e obtém o índice do pivô
        int pi = partition(array, low, high);

        // ordena os elementos antes e depois do pivô
        quicksort(array, low, pi - 1);
        quicksort(array, pi + 1, high);
    }
}


// Função de partição: coloca o pivô na posição correta
int partition(int array[], int low, int high) {
    int pivot = array[high]; // escolhe o último elemento como pivô
    int i = low - 1; // índice do menor elemento

    for (int j = low; j < high; j++) {
        // se o elemento atual é menor ou igual ao pivô
        if (array[j] <= pivot) {
            i++;
            swap(&array[i], &array[j]);
        }
    }

    // coloca o pivô no lugar correto
    swap(&array[i + 1], &array[high]);
    return i + 1; // retorna o índice do pivô
}


// ------ MERGESORT ----------------

void mergesort(int array[], int esq, int dir) {
    if (esq < dir) {
        int meio = (esq + dir) / 2;

        // Divide o vetor em duas metades
        mergesort(array, esq, meio);
        mergesort(array, meio + 1, dir);

        // Conquista — intercala as metades ordenadas
        intercalar(array, esq, meio, dir);
    }
}

void intercalar(int array[], int esq, int meio, int dir) {
    int nEsq = (meio + 1) - esq;
    int nDir = dir - meio;

    int arrayEsq[nEsq], arrayDir[nDir];

    // Copiando os elementos para os subvetores auxiliares
    for (int i = 0; i < nEsq; i++) {
        arrayEsq[i] = array[esq + i];
        movimentacoes++;  // movimento ao copiar
    }
    for (int j = 0; j < nDir; j++) {
        arrayDir[j] = array[meio + 1 + j];
        movimentacoes++;
    }

    // Índices auxiliares
    int i = 0, j = 0, k = esq;

    // Intercalação ordenada
    while (i < nEsq && j < nDir) {
        comparacoes++;  // comparação entre elementos
        if (arrayEsq[i] <= arrayDir[j]) {
            array[k++] = arrayEsq[i++];
        } else {
            array[k++] = arrayDir[j++];
        }
        movimentacoes++;
    }

    // Copiando o restante do lado esquerdo (se sobrar)
    while (i < nEsq) {
        array[k++] = arrayEsq[i++];
        movimentacoes++;
    }

    // Copiando o restante do lado direito (se sobrar)
    while (j < nDir) {
        array[k++] = arrayDir[j++];
        movimentacoes++;
    }
}


// ------- INSERTION SORT -------------

#include <stdio.h>

// Função que implementa o Insertion Sort
void insertionSort(int array[], int n) {
    int i, key, j;

    // percorre o vetor a partir do segundo elemento
    for (i = 1; i < n; i++) {
        key = array[i]; // elemento a ser inserido na parte ordenada
        j = i - 1;

        // move os elementos maiores que "key" uma posição à frente
        while (j >= 0 && array[j] > key) {
            array[j + 1] = array[j];
            j = j - 1;
        }

        // insere o elemento na posição correta
        array[j + 1] = key;
    }
}

int main() {
    int array[] = {12, 11, 13, 5, 6};
    int n = sizeof(array) / sizeof(array[0]);

    printf("Array original:\n");
    for (int i = 0; i < n; i++)
        printf("%d ", array[i]);

    insertionSort(array, n);

    printf("\n\nArray ordenado com Insertion Sort:\n");
    for (int i = 0; i < n; i++)
        printf("%d ", array[i]);

    return 0;
}

