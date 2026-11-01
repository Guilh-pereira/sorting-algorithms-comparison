# Comparativo de Desempenho de Algoritmos de Ordenação em C

Projeto de pesquisa desenvolvido para analisar, comparar e registrar o tempo de execução de diferentes algoritmos de ordenação clássicos utilizando a linguagem C.

## Algoritmos Implementados
O projeto cobre nove algotitmos principais de ordenação:
1. **Bubble Sort**
2. **Insertion Sort**
3. **Selection Sort**
4. **Merge Sort**
5. **Quick Sort**
6. **Heap Sort**
7. **Counting Sort**
8. **Radix Sort**
9. **Bucket Sort**

## Restrições e Metodologia de Teste
* **Geração de Dados:** Vetores preenchidos com números inteiros aleatórios (intervalo de 0 a 1.000.000).
* **Reprodutibilidade:** Utilização de semente fixa (`srand(seed)`) e clonagem idêntica do vetor base (`memcpy`) para garantir que todos os algoritmos ordenem exatamente a mesma disposição inicial de elementos.
* **Isolamento de Tempo:** A medição de tempo (`clock_gettime` com `CLOCK_MONOTONIC`) engloba **exclusivamente** a rotina de ordenação, descartando alocações, geração de dados e cópias.
* **Validação Estatística:** Cada teste é executado 3 vezes consecutivas para o mesmo tamanho N, registrando-se a média aritmética para mitigar interferências do sistema operacional.
* **Massa de Dados (N):** Testado em múltiplos tamanhos (1.000, 10.000, 50.000, 100.000 e 500.000).

## Estrutura do Projeto
* `ordenacao.c` / `ordenacao.h`: Contém as implementações dos 9 algoritmos de ordenação e do gerador de números aleatórios.
* `main.c`: Contém a suíte de testes automatizados, controle de tamanhos, clonagem de vetores e medição precisa de tempo.

## Como Compilar e Executar
No terminal do Linux/macOS ou no MinGW do Windows, execute os seguintes comando na pasta dos arquivos:
```bash
gcc main.c ordenacao.c -o comparador_sort
```
```bash
./comparador_sort
```
