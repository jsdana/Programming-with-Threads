#include <stdio.h>
#include <stdlib.h>
#include <pthread>

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

char decipherChar(char* s, int i){
    char minChar = 33;
    char maxChar = 126;
    char letra = BuscaB(s, minChar, maxChar, i);
    return letra;
}

int main(){
    pthread_t thread;
    int rc;
    rc = pthread_create(&thread, NULL, )
    
    char senha[10] = "h8dc@K0!c4";
    print(senha);
    char l = decipherChar(senha, 3);
    printf("%c", l);

    return 0;
}
