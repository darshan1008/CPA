#include <stdio.h> 
#include <stdlib.h> 

int main(){
	int A[10]; 
	int i; 

	for(i = 0; i < 10; ++i){
		printf("Please enter A[%d]:", i); 
		scanf("%d", &A[i]); 
	}	

	sort(A); 	// insertion, quick, heap

	for(i = 0; i < 10; ++i){
		printf("A[%d]:%d\n", i, A[i]); 
	}

	return (0); 
}

// 1. We do not want pre decided (or statically decided array size)
// 2. We do not want data in array to be input in an interactive fashion. 

// as above program has both, we do not condone such organization of program. 