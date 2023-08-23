#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define true 1 
#define false 0

int NUM_THREADS;
int N;
int* primeNumbers;
int* mutex;

void printArr(){
    
    printf("Prime numbers under %d : ", N);
    
    for(int i=0; i<N; i++){
        if(primeNumbers[i] > 0)
            printf("%d ", i);
    }
    printf("\n");
}

void print(){
    for(int i=0; i<N; i++){
        printf("%d ", primeNumbers[i]);
    }
}

void* crivo(void *threadID){
    int id = *((int *)threadID);
    for(int i= id+2; i<N; i++){
            if(mutex[i]==false && primeNumbers[i]){
                mutex[i] = true;
                printf("Number %d at thread %d\n", i, id);
                for(int j=i+1; j<N; j++){
                    if( primeNumbers[j] && (j % i == 0))
                        primeNumbers[j] -= 1;
                }
            }
    }
}

void makeThreads(){
    pthread_t threads[NUM_THREADS];
    int *taskids[NUM_THREADS];

    int rc;   int t;   
  
    for(t=0; t<NUM_THREADS; t++){      
        taskids[t] = (int *) malloc(sizeof(int)); 
        *taskids[t] = t;
        rc = pthread_create(&threads[t], NULL, crivo, (void *) taskids[t]);      
        if (rc){         
            printf("ERRO; código de retorno é %d\n", rc);         
            exit(-1); 
        }
    }   
    
    for(int i=0; i<NUM_THREADS; i++)
        pthread_join(threads[i], NULL);
}

int main(){
    printf("Insert a natural number: ");
    scanf("%d", &N);
    primeNumbers = (int*) malloc(N * sizeof(int));
    mutex = (int*) malloc(N * sizeof(int));
    if(N<=1){
        primeNumbers[0] = false;
        primeNumbers[1] = false;
        mutex[0] = false;
        mutex[1] = false;
    }
    for(int i=2; i<N; i++){
        primeNumbers[i] = true;
        mutex[i] = false;
    }
    printf("Number of threads: ");
    scanf("%d", &NUM_THREADS);
        
    makeThreads();
        
    printArr();
    print();
    pthread_exit(NULL);
    free(primeNumbers);
    free(mutex);
}
