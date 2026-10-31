#if !defined(ORDENACAO_H)
#define ORDENACAO_H

int* gerarAleatorio(int tam, int min, int max);
int* bubbleSort(int vetor[], int tam);
int* insertSort(int vetor[], int tam);
int* selectionSort(int vetor[], int tam);
int* mergeSort(int vetor[], int tam);
int* quickSort(int vetor[], int tam);
int* heapSort(int vetor[], int tam);
int* countingSort(int vetor[], int tam);
int* radixSort(int vetor[], int tam);
int* bucketSort(int vetor[], int tam);

#endif // ORDENACAO_H
