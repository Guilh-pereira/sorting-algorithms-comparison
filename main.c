#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "ordenacao.h"

void testarAlgoritmo(const char nome[], int* (*sortFunc)(int[], int), int vetor_base[], int tam) {
    int *copia = malloc(tam * sizeof(int));
    if (copia == NULL) return;

    double soma_tempos = 0;

    // executa o algoritmo 3 vezes
    for (int i = 0; i < 3; i++)
    {
        memcpy(copia, vetor_base, tam * sizeof(int)); // copia o vetor base para um vetor auxiliar
        struct timespec inicio, fim;
        // mede o tempo
        clock_gettime(CLOCK_MONOTONIC, &inicio); 
        sortFunc(copia, tam);
        clock_gettime(CLOCK_MONOTONIC, &fim);
        // calcula o tempo gasto em segundos
        double tempo_gasto = (fim.tv_sec - inicio.tv_sec) + (fim.tv_nsec - inicio.tv_nsec) / 1e9;
        soma_tempos += tempo_gasto;

        // mostra o tempo de cada execução individualmente
        printf("Execucao %d: %.6f s\n", i + 1, tempo_gasto);
    }

    double media = soma_tempos / 3;
    printf("  %-15s -> Media: %.6f s\n", nome, media);

    free(copia);
}

int main(int argc, char const *argv[])
{
    //seed fixa para sempre gerar a mesma sequência aleatoria
    srand(42);
    int tamanhos[] = {1000, 10000, 50000, 100000, 500000};
    int qtd_tamanhos = 5;

    // looping para testar todos os algoritmos
    for (int i = 0; i < qtd_tamanhos; i++)
    {
        int tam = tamanhos[i];
        printf("\n========================================\n");
        printf("TAMANHO: N = %d\n", tam);
        printf("========================================\n");

        int *vetor_base = gerarAleatorio(tam, 0, 1000000);
        if (vetor_base == NULL) {
            printf("Erro ao gerar vetor base.\n");
            continue;
        }

        testarAlgoritmo("Bubble Sort", bubbleSort, vetor_base, tam);
        testarAlgoritmo("Insert Sort", insertSort, vetor_base, tam);
        testarAlgoritmo("Selection Sort", selectionSort, vetor_base, tam);
        testarAlgoritmo("Merge Sort", mergeSort, vetor_base, tam);
        testarAlgoritmo("Quick Sort", quickSort, vetor_base, tam);
        testarAlgoritmo("Heap Sort", heapSort, vetor_base, tam);
        testarAlgoritmo("Counting Sort", countingSort, vetor_base, tam);
        testarAlgoritmo("Radix Sort", radixSort, vetor_base, tam);
        testarAlgoritmo("Bucket Sort", bucketSort, vetor_base, tam);

        free(vetor_base);
    }
    return 0;
}