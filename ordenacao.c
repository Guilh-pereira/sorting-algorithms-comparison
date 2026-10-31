#include "ordenacao.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct NoBucket {
    int dado;
    struct NoBucket *prox;
} NoBucket;

//Gera um vetor com números aleatórios em um intervalo determinado [min, max]
int* gerarAleatorio(int tam, int min, int max) {
    int *vetor = calloc(tam, sizeof(int));
    if (vetor == NULL)
    {
        printf("Erro ao inicializar\n");
        return NULL;
    }
    for (int i = 0; i < tam; i++)
    {
        vetor[i] = min + rand() % (max - min + 1);
    }
    return vetor;
}

// compara elementos adjacentes e os troca se estiverem fora de ordem
int* bubbleSort(int vetor[], int tam) {
    for (int i = 0; i < tam - 1; i++)
    {
        for (int j = 0; j < tam - 1 - i; j++)
        {
            // se o elemento da esqerda for maior que o da direita, troca
            if (vetor[j] > vetor[j + 1])
            {
                int temp = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = temp;
            }
            
        }
        
    }
    return vetor;   
}

// Constrói o vetor ordenado um elemento por vez, inserindo cada novo
int* insertSort(int vetor[], int tam) {
    for (int i = 1; i < tam; i++)
    {
        int temp = vetor[i]; // elemento a ser inserido na posição correta
        int j = i - 1;

        // desloca os elementos maiores que 'temp' uma posição para a direita
        while (j >= 0 && vetor[j] > temp)
        {
            vetor[j + 1] = vetor[j];
            j--;
        }
        
        vetor[j + 1] = temp; // insere o elemento na posição encontrada
    }
    return vetor;
}

/*
Procura o menor elemento do vetor e o coloca na primeira posição.
depois, procura o menor elemento do restante e o coloca na segunda, e assim por diante
*/
int* selectionSort(int vetor[], int tam) {
    for (int i = 0; i < tam - 1; i++)
    {
        int min = i; // assume inicialmente que o menor elemento está no índice 'i'

        // procura o menor elemento na parte não ordenada
        for (int j = i + 1; j < tam; j++)
        {
            if (vetor[min] > vetor[j])
            {
                min = j;
            }
        }
        
        // troca o menor elemento encontrado com a posição 'i'
        int temp = vetor[i];
        vetor[i] = vetor[min];
        vetor[min] = temp;
    }
    return vetor;
}

// Divide o vetor ao meio recursivamente e depois mescla as metades
void merge(int vetor[], int inicio, int meio, int fim) {
    int i, j, k;
    int n1 = meio - inicio + 1;
    int n2 = fim - meio;

    // vetores temporários para armazenar as duas metades
    int *esq = (int *)malloc(n1 * sizeof(int));
    int *dir = (int *)malloc(n2 * sizeof(int));

    for (i = 0; i < n1; i++)
    {
        esq[i] = vetor[inicio + i];
    }
    for (j = 0; j < n2; j++) {
        dir[j] = vetor[meio + 1 + j];
    }
    i = 0;
    j = 0;
    k = inicio;

    // compara e junta os elementos ordenados de volta no vetor original
    while (i < n1 && j < n2) {
        if (esq[i] <= dir[j]) {
            vetor[k] = esq[i];
            i++;
        } else {
            vetor[k] = dir[j];
            j++;
        }
        k++;
    }

    // copia os elementos restantes, se houver
    while (i < n1) {
        vetor[k] = esq[i];
        i++;
        k++;
    }
    while (j < n2) {
        vetor[k] = dir[j];
        j++;
        k++;
    }
    free(esq);
    free(dir);
}

// função recursiva do merge sort
void mergeSortAux(int vetor[], int inicio, int fim) {
    if (inicio < fim) {
        int meio = inicio + (fim - inicio) / 2;

        mergeSortAux(vetor, inicio, meio); // ordena a primeira metade
        mergeSortAux(vetor, meio + 1, fim); // ordena a segunda metade

        merge(vetor, inicio, meio, fim); // intercala as duas metades
    }
}

// interface principal para o merge sort
int* mergeSort(int vetor[], int tam) {
    mergeSortAux(vetor, 0, tam-1);
    return vetor;
}

/*
Escolhe um elemento como 'pivô' e particiona o vetor de modo que os
elementos menores fiquem à esquerda e os maiores à direita
*/
int partition(int vetor[], int inicio, int fim) {
    int pivot = vetor[fim]; // escolhe o último elemento como pivot
    int i = inicio - 1;

    for (int j = inicio; j <= fim - 1; j++) {
        if (vetor[j] < pivot) {
            i++;
            int temp = vetor[i];
            vetor[i] = vetor[j];
            vetor[j] = temp;
        }
    }
    i++;
    int temp = vetor[i];
    vetor[i] = vetor[fim];
    vetor[fim] = temp;
    return i; // retorna o índice onde o pivô ficou posicionado
}

// função recursiva do quick sort
void quickSortAux(int vetor[], int inicio, int fim) {
    if (fim <= inicio) return;

    int pivot = partition(vetor, inicio, fim);
    quickSortAux(vetor, inicio, pivot - 1); // ordena os elementos antes do pivot
    quickSortAux(vetor, pivot + 1, fim); // ordena os elementos depois do pivot
}

// interface principal para o quick sort
int* quickSort(int vetor[], int tam) {
    quickSortAux(vetor, 0, tam - 1);
    return vetor;
}

/*
Converte o vetor em uma árvore Max-Heap (onde a raiz é o maior elemento), remove a raiz repetidamente e reconstrói a heap
*/
// função auxiliar para reorganizar uma subárvore mantendo a propriedade de Max-Heap
void heapify(int vetor[], int n, int i) {
    int maior = i; // inicializa o maior como raiz
    int esq = 2 * i + 1; // filho da esquerda
    int dir = 2 * i + 2; // filho da direita

    // se o filho da esquerda for maior que a raiz
    // a raiz passa a ser o filho da esquerda
    if (esq < n && vetor[esq] > vetor[maior]) maior = esq;

    // se o filho da direita for maior que a raiz
    // a raiz passa a ser o filho da direita
    if (dir < n && vetor[dir] > vetor[maior]) maior = dir;

    // se o maior for diferente da raiz, troca e continua o heapify
    if (maior != i) {
        int temp = vetor[i];
        vetor[i] = vetor[maior];
        vetor[maior] = temp;
        heapify(vetor, n, maior);
    }
    
}

// interface principal para o heap sort
int* heapSort(int vetor[], int tam) {
    // constrói a heap
    for (int i = (tam - 1) / 2; i >= 0; i--) {
        heapify(vetor, tam, i);
    } 

    // extrai os elementos da heap um por um
    for (int i = tam - 1; i > 0; i--)
    {
        // move o maior elemento atual (raiz) para o final do vetor
        int temp = vetor[0];
        vetor[0] = vetor[i];
        vetor[i] = temp;

        heapify(vetor, i, 0); // reconstroi a heap
    }
    return vetor;
}

/*
Conta a frequência de ocorrência de cada valor
e usa contagem acumulada para posicionar os elementos diretamente
*/
int* countingSort(int vetor[], int tam) {
    if (tam <= 0) return vetor;

    // encontra o maior elemento do vetor para definir o tamanho máximo do vetor de contagem
    int max = vetor[0];
    for (int i = 0; i < tam; i++)
    {
        if (vetor[i] > max)
        {
            max = vetor[i];
        }
    }
    
    // aloca o vetor de contagem e o auxiliar de saída
    int *contador = calloc(max + 1, sizeof(int));
    int *saida = calloc(tam, sizeof(int));

    if (contador == NULL || saida == NULL) {
        free(contador);
        free(saida);
        return vetor;
    }

    // armazena a frequência de cada elemento
    for (int i = 0; i < tam; i++)
    {
        contador[vetor[i]]++;
    }

    // acumula as contagens
    for (int i = 1; i <= max; i++)
    {
        contador[i] += contador[i - 1];
    }
    
    // constrói o vetor de saída
    for (int i = tam - 1; i >= 0; i--)
    {
        saida[contador[vetor[i]] - 1] = vetor[i];
        contador[vetor[i]]--;
    }
    
    // copia o vetor de saída para o vetor original
    for (int i = 0; i < tam; i++)
    {
        vetor[i] = saida[i];
    }

    free(contador);
    free(saida);
    return vetor;
}

/*
Ordena os números dígito por dígito, do menos significativo (unidades)
para o mais significativo (dezenas, centenas, etc.)
*/
void countingSortRadix(int vetor[], int tam, int exp) {
    int *saida = calloc(tam, sizeof(int));
    int contador[10] = {0};

    for (int i = 0; i < tam; i++)
    {
        contador[(vetor[i] / exp) % 10]++;
    }

    for (int i = 1; i < 10; i++)
    {
        contador[i] += contador[i - 1];
    }

    for (int i = tam - 1; i >= 0; i--)
    {
        saida[contador[(vetor[i] / exp) % 10] - 1] = vetor[i];
        contador[(vetor[i] / exp) % 10]--;
    }

    for (int i = 0; i < tam; i++)
    {
        vetor[i] = saida[i];
    }
    free(saida);
}

int* radixSort(int vetor[], int tam) {
    if (tam <= 0) return vetor;

    // encontra o maior número para saber quantos dígitos ele tem
    int max = vetor[0];
    for (int i = 0; i < tam; i++) {
        if (vetor[i] > max) {
            max = vetor[i];
        }
    }

    for (int exp = 1; max / exp > 0; exp*=10)
    {
        countingSortRadix(vetor, tam, exp);
    }

    return vetor;
}

/*
Divide o intervalo de números em vários "baldes" (subconjuntos).
Os elementos são distribuídos nos baldes, ordenados e depois coletados
*/
// insere um elemento de forma ordenada dentro da lista encadeada do balde
NoBucket* inserirOrdenado(NoBucket *inicio, int valor) {
    NoBucket *novo = malloc(sizeof(NoBucket));
    novo->dado = valor;
    novo->prox = NULL;

    if (inicio == NULL || inicio->dado >= valor) {
        novo->prox = inicio;
        return novo;
    }

    NoBucket *atual = inicio;
    while(atual->prox != NULL && atual->prox->dado < valor) {
        atual = atual->prox;
    }
    novo->prox = atual->prox;
    atual->prox = novo;
    return inicio;
}

int* bucketSort(int vetor[], int tam) {
    if (tam <= 0) return vetor;

    int numBaldes = 100; // define a quantidade de baldes
    NoBucket **baldes = calloc(numBaldes, sizeof(NoBucket*)); // aloca o vetor de baldes

    if (baldes == NULL) {
        free(baldes);
        return vetor;
    }

    // encontra o maior valor para definir o tamanho dos baldes
    int max = vetor[0];
    for (int i = 1; i < tam; i++) {
        if (vetor[i] > max) max = vetor[i];
    }
    max = (max == 0) ? 1 : max + 1;

    // distribui os elementos do vetor nos baldes correspondentes
    for (int i = 0; i < tam; i++)
    {
        int indiceBalde = (numBaldes * vetor[i]) / max;
        baldes[indiceBalde] = inserirOrdenado(baldes[indiceBalde], vetor[i]);
    }

    //coleta os elementos ordenados de volta para o vetor principal
    int indice = 0;
    for (int i = 0; i < numBaldes; i++)
    {
        NoBucket* atual = baldes[i];
        while (atual != NULL) {
            vetor[indice++] = atual->dado;
            NoBucket* temp = atual;
            atual = atual->prox;
            free(temp);
        }
    }

    free(baldes);
    return vetor;
}