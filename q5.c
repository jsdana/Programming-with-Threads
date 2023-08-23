#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define true 1 
#define false 0

void printArr(int* arr, int size){
    
    printf("Prime numbers under %d : ", size);
    
    for(int i=0; i<size; i++){
        if(arr[i] != 0)
            printf("%d ", i);
    }
    printf("\n");
}

void print(int* arr, int size){
    for(int i=0; i<size; i++){
        printf("%d ", arr[i]);
    }
}

void crivo(int* arr, int size){
    for(int i=0; i<size; i++){
        if(arr[i]==true){
            for(int j=i+1; j<size; j++){
                if( arr[j] && (j % i == 0))
                    arr[j] -= 1;
            }
        }
    }
}

int main(){
    int n;
    printf("Insert a natural number: ");
    scanf("%d", &n);
    int array[n];
    if(n<=1){
        array[0] = false;
        array[1] = false;
    }
    for(int i=2; i<n; i++)
        array[i] = true;
        
    crivo(array, n);
        
    printArr(array, n);
    print(array, n);
}
