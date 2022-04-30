#include <stdio.h> 
#include <stdlib.h> 
#include <assert.h> 
#include <string.h> 
#include <time.h> 

int main(){
	int* a; 
	int n; 
	int i; 

	printf("Enter the size of array:"); 
	scanf("%d", &n); 

	if(n <= 0){
		puts("Bad size"); 
		exit(-1); 
	}

	a = (int*)malloc(sizeof(int) * n); 
	assert(a != NULL); 
	memset(a, 0, sizeof(int) * n); 

	srand(time(0));
	for(i = 0; i < n; ++i)
		a[i] = rand(); 
	for(i = 0; i < n; ++i)
		printf("a[%d]:%d\n", i, a[i]); 

	free(a); 
	a = NULL; 

	exit(0); 
}