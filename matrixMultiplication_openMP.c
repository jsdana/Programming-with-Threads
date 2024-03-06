#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define SIZE 825

// Função para preencher uma matriz com valores aleatórios
void fillMatrixRandomly(int matrix[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            matrix[i][j] = rand() % 10; // Atribui um valor aleatório entre 0 e 9
        }
    }
}

// Função para exibir uma matriz
void printMatrix(int matrix[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Função para multiplicar duas matrizes 
void mulMatrix(int matrixA[SIZE][SIZE], int matrixB[SIZE][SIZE], int resultMatrix[SIZE][SIZE], int *evenCount) {
    *evenCount = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            resultMatrix[i][j] = 0;
            for (int k = 0; k < SIZE; k++)
                resultMatrix[i][j] += matrixA[i][k] * matrixB[k][j];
            

            if (resultMatrix[i][j] % 2 == 0) 
                (*evenCount)++; // Incrementa o contador se o elemento é par
        }
    }
}

// Função para multiplicar duas matrizes paralelamente
void opMPmulMatrix(int matrixA[SIZE][SIZE], int matrixB[SIZE][SIZE], int resultMatrix[SIZE][SIZE], int *evenCount) {
    int localEvenCount = 0; // Variável local para cada thread
    #pragma omp parallel for reduction(+:localEvenCount)
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            int sum = 0;

            for (int k = 0; k < SIZE; k++) {
                sum += matrixA[i][k] * matrixB[k][j];
            }
            resultMatrix[i][j] = sum;

            if (sum % 2 == 0) {
                localEvenCount++; // Incrementa a variável local se o elemento é par
            }
        }
    }
    *evenCount = localEvenCount; // Atualiza a contagem total de números pares após o loop paralelo
}

int main() {
    int matrixA[SIZE][SIZE];
    int matrixB[SIZE][SIZE];
    int resultMatrix[SIZE][SIZE];

    int evenCount;
    
    srand(time(NULL)); // Inicializa o gerador de números aleatórios com o tempo atual
    
    // Preenche as matrizes A e B com valores aleatórios
    fillMatrixRandomly(matrixA);
    fillMatrixRandomly(matrixB);
    
    //PRINTA AS MATRIZES INICIAIS A E B
    /*

    printf("Matriz A:\n");
    printMatrix(matrixA);
    
    printf("Matriz B:\n");
    printMatrix(matrixB);
    
    */

    clock_t start = clock(); // Marca o tempo de início da multiplicação
    
    // Multiplica as matrizes A e B
    mulMatrix(matrixA, matrixB, resultMatrix, &evenCount);
    
    clock_t fim = clock(); // Marca o tempo de fim da multiplicação
    
    //PRINTA A MATRIZ FINAL
    /*
    printf("resultMatrix da multiplicacao serial:\n");
    printMatrix(resultMatrix);
    */
    
    // Calcula o tempo de execução em segundos
    double exeTimeA = ((double)(fim - start)) / CLOCKS_PER_SEC;
    printf("Tempo de execucao da matriz R1 (Serial): %.6f segundos\n", exeTimeA);
    printf("Nº de Pares na Matriz R1: %d \n\n", evenCount);
    
    double startP = omp_get_wtime(); // Marca o tempo de início da multiplicação

    evenCount = 7;
    
    // Multiplica as matrizes A e B
    opMPmulMatrix(matrixA, matrixB, resultMatrix, &evenCount);
    
    double endP = omp_get_wtime(); // Marca o tempo de fim da multiplicação
    
    //printf("resultMatrix da multiplicacao paralela:\n");
    //printMatrix(resultMatrix);
    
    // Calcula o tempo de execução em segundos
    double exeTimeB = endP - startP;
    printf("Tempo de execucao da matriz R2 (Paralela): %.6f segundos\n", exeTimeB);
    printf("Nº de Pares na Matriz R2: %d \n\n", evenCount);

    return 0;
}