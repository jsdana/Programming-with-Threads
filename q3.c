#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define arraySize 10
int RUNCICLES = 100;
int* array;
int NUM_READERS;
int NUM_WRITERS;
int NUM_THREADS;

int mutex = 1;
int db = 1;
int rc = 0;


void up(){
    mutex++;
}

void down(){
    mutex--;
}

void *reader(void *threadID){
    int id = *((int *)threadID);
    int valueRead;
    while(RUNCICLES >= 0){
        int index = rand() % arraySize;
        
        down(&mutex);
        rc++;
        if(rc == 1)
            down(&db);
        up(&mutex);
        
        valueRead = array[index];
        
        down(&mutex);
        rc--;
        if(rc == 0)
            up(&db);
        up(&mutex);
        
        printf("Reader Thread %d Reading %d at index %d \n", id, array[index], index);
        RUNCICLES--;
        
    }
}

void *writer(void *threadID){
    int id = *((int *)threadID);
    while(RUNCICLES >= 0){
        int index = rand() % arraySize;
        int value = rand() % 1000;

        down(&db);
        array[index] = value;
        up(&db);
        printf("Writer Thread %d writing %d at index %d \n", id - NUM_READERS, value, index);
        RUNCICLES--;

    }
}

void ReaderThreads(){                     //Criação das Threads
    pthread_t threads[NUM_THREADS];
    int *taskids[NUM_THREADS];

    int rc;   int t;   
  
    for(t=0; t<NUM_THREADS; t++){      
        taskids[t] = (int *) malloc(sizeof(int)); 
        *taskids[t] = t;
        if(t<NUM_READERS){
            rc = pthread_create(&threads[t], NULL, reader, (void *) taskids[t]);     
            if (rc){                        //Tratamento de erro    
                printf("ERRO; código de retorno é %d\n", rc);         
                exit(-1); 
            }
        }else{
            rc = pthread_create(&threads[t], NULL, writer, (void *) taskids[t]);     
            if (rc){                        //Tratamento de erro    
                printf("ERRO; código de retorno é %d\n", rc);         
                exit(-1); 
            }            
        }
    }   
    
    for(int i=0; i<NUM_THREADS; i++)
        pthread_join(threads[i], NULL);
        
    pthread_exit(NULL);
}

int main(){
    
    array = (int*) malloc(arraySize * sizeof(int));
    for(int i=0; i<arraySize; i++)
        array[i] = 0;
        
    printf("Number of Readers: ");
    scanf("%d", &NUM_READERS);
    printf("Number of Writers: ");
    scanf("%d", &NUM_WRITERS);
    
    NUM_THREADS = NUM_WRITERS + NUM_READERS;
    
    ReaderThreads();
    
    free(array);
    return 0;
}
