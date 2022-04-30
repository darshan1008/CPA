#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <time.h> 

void same_series(void); 
void different_series(void); 

int main(){
	
	puts("Series1:");
	same_series();
	puts("Series2:");
	different_series(); 

	return (0); 
}

void same_series(void){
	int A[10]; 
	int i; 

	memset(A, 0, 10 * sizeof(int)); 
	for(i = 0; i < 10; ++i)
		A[i] = rand(); 

	for(i = 0; i < 10; ++i)
		printf("A[%d]:%d\n", i, A[i]); 
}

void different_series(void){
	int A[10]; 
	int i; 

	srand(time(0)); 
	memset(A, 0, 10 * sizeof(int)); 
	for(i = 0; i < 10; ++i)
		A[i] = rand(); 

	for(i = 0; i < 10; ++i)
		printf("A[%d]:%d\n", i, A[i]); 
}