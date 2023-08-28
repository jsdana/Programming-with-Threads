#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define arraySize 10

typedef int semaphore;

pthread_mutex_t db = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

semaphore mutex = 1;    //Controla o acesso a "rc"
semaphore db = 1;       //Controla o acesso ao array
int rc = 0;             //nº de processos lendo ou querendo ler

int* array;

int NUM_READERS;
int NUM_WRITERS;

void up(semaphore var){
    var++;
}

void down(semaphore var){
    var--;
}

void* reader(void *threadID){
    //while(1){
    int readerID = *((int *)threadID);
    
        printf("Reader %d : wanting to read\n", readerID); 
        down(mutex);                            //Obtem acesso a rc
        rc += 1;                                //Mais um leitor
        if(rc ==1)                              //Se este for o 1º leitor ...
            down(db);
        up(mutex);                              //Libera acesso a rc
        
        //read_data_base();
        printf("Reader %d : reading\n", readerID);
        
        down(mutex);
        rc -= 1;
        
        if(!rc)
            up(db);
        up(mutex);
        
        //use_data_base
        printf("Reader %d : finished\n", readerID);
    //}
}

void* writer(void *threadID){
    //while(1){
    int writerId = *((int *)threadID);
        //think_up_data();
        printf("Writer %d : wanting to write\n", writerId);
        
        down(db);          //Obtem acesso exclusivo
        
        //write_data_base();      //Escreve no array
        printf("Writer %d : writing\n", writerId);
        
        up(db);            //Libera para outros processos
        printf("Writer %d : finished\n", writerId);
   //}
}

void makeThreads(){
    pthread_t readersT[NUM_READERS];
    int *taskids_R[NUM_READERS];
    
    pthread_t Writers[NUM_WRITERS];
    int *taskids_W[NUM_WRITERS];

    int rc_r, rc_w;   int tR, tW;   
  
    for(tR=0; tR<NUM_READERS; tR++){      
        taskids_R[tR] = (int *) malloc(sizeof(int)); 
        *taskids_R[tR] = tR;
        rc_r = pthread_create(&readersT[tR], NULL, reader, (void *) taskids_R[tR]);      
        if (rc_r){         
            printf("ERRO; código de retorno é %d\n", rc_r);         
            exit(-1); 
        }
    }   
    
    for(tW=0; tW<NUM_WRITERS; tW++){
        taskids_W[tW] = (int *) malloc(sizeof(int));
        *taskids_W[tW] = tW;
        rc_w = pthread_create(&Writers[tW], NULL, writer, (void *) taskids_W[tW]);
        if(rc_w){
            printf("ERRO; código de retorno é %d\n", rc_w);         
            exit(-1); 
        }
    }
    
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
    
    makeThreads();
    
    
    free(array);
    
    return 0;
}
