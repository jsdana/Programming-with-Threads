#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define NUM_THREADS 5

void print(char* s){
    for (int i=0; i<10; i++)
        printf("%c", s[i]);
    printf("\n");
}
/* Binary Search para decifrar o char do índice i da string */
char BuscaB(char* s, int l, int r, int i){
    if(r>=l){
        char m = (l+r)/2;
        if(m == s[i])
            return m;
        else if(s[i] < m)
            return BuscaB(s, l, m-1, i);
        else
            return BuscaB(s, m+1, r, i);
    }
    return -1;
}

void decipherString(char* s, char* destination){
    char minChar = 33;
    char maxChar = 126;
    for(int i=0; i<10;i++){
        char letra = BuscaB(s, minChar, maxChar, i);
        destination[i] = letra;
    }
}

int main(){
    char senha[10] = "h8dc@K0!c4";
    print(senha);
    char password[10];
    
    pthread_t threads[NUM_THREADS];
    int* taskids[NUM_THREADS];
    
    int rc; int t;
    
    for(t=0; t<NUM_THREADS; t++){
        taskids[t] = (int*) malloc(sizeof(int));
        *taskids[t] = t;
        
        rc = pthread_create(&threads[t], NULL, decipherString)
    }
    
    decipherString(senha, password);
    print(password);

    return 0;
}
