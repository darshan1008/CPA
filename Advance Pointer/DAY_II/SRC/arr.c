#include <stdio.h> 
#include <stdlib.h>

int A[3][5]; 

int main(){
	int (*p)[5]; 
	int i; 

	p = A;//(int (*)[5]) 1000; 
	for(i = 0; i < 3; ++i)
		printf("p+%d:%d\n", i, p+i);  

	return 0; 
}