#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

int NUM_THREADS;
char senha[10];
char password[10];

void print(char* s){
    for (int i=0; i<strlen(s); i++)
        printf("%c", s[i]);
    printf("\n");
}
/* Binary Search para decifrar o char do índice i da string */
char BuscaB(int l, int r, int i){
    if(r>=l){
        char m = (l+r)/2;
        if(m == senha[i])
            return m;
        else if(senha[i] < m)
            return BuscaB(l, m-1, i);
        else
            return BuscaB(m+1, r, i);
    }
    return -1;
}

void *decipherString(void *threadID){
    int id = *((int *)threadID);

    char minChar = 33;
    char maxChar = 126;
    for(int i=id; i<=10;i+=NUM_THREADS){
        char letra = BuscaB(minChar, maxChar, i);
        if(letra != -1){
            password[i] = letra;
            printf("char %d at thread %d\n", i, id);
        }else
            password[i] = '\0';
    }
}

void makeThreads(){
     pthread_t threads[NUM_THREADS];
    int *taskids[NUM_THREADS];

    int rc;   int t;   
  
    for(t=0; t<NUM_THREADS; t++){      
        taskids[t] = (int *) malloc(sizeof(int)); 
        *taskids[t] = t;
        rc = pthread_create(&threads[t], NULL, decipherString, (void *) taskids[t]);      
        if (rc){         
        printf("ERRO; código de retorno é %d\n", rc);         
        exit(-1); 
        }
    }   
    
    for(int i=0; i<NUM_THREADS; i++)
        pthread_join(threads[i], NULL);
}

void getpassword(){
    printf("Number of threads: ");
    scanf("%d", &NUM_THREADS);
    printf("Password (max: 10 characters): ");
    scanf("%s", senha);
}

int main(){
    getpassword();
    makeThreads();
    
    printf("Deciphered Password: ");
    print(password);
    
    pthread_exit(NULL);
    return 0;
}
