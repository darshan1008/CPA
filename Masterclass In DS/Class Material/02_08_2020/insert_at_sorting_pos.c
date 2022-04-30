#include <stdio.h> 
#include <stdlib.h> 

#define N 10 

void output(int* a, int n); 
void insert_at_sorting_pos(int* a, int n); 

int main(){
    int a[N] = {10, 20, 30, 40 ,50, 60, 70 ,80 ,90, 35}; 
    int b[N] = {345, 47, 43, 4747, 86, 32, 58, 1, 347, 2}; 
    
    puts("a before iasp"); 
    output(a, N); 
    puts("a after iasp");
    insert_at_sorting_pos(a, N); 
    output(a, N); 

    puts("b before sort"); 
    output(b, N); 

    int i; 
    for(i = 2; i <= N; ++i)
        insert_at_sorting_pos(b, i); 

    puts("b after sort"); 
    output(b, N); 

    return (0); 

}

void insert_at_sorting_pos(int* a, int n){
    int i; 
    int key; 

    key = a[n-1]; 
    i = n - 2; 
    while(i > -1 && a[i] > key){
        a[i+1] = a[i]; 
        i = i - 1; 
    }

    a[i+1] = key; 
}

void output(int* a, int n){
    int i; 
    for(i = 0; i < n; ++i)
        printf("a[%d]:%d\n", i, a[i]); 
}