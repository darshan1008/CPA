#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define TRUE 1 

int main(){
	int *p_arr; 
	int size; 
	int n; 
	int choice; 
	int i; 

	p_arr = NULL; 
	size = 0; 

	while(TRUE){
		printf("Do you want to enter an integer?[Y-1/N-0]:"); 
		scanf("%d", &choice); 
		if(choice == 0)
			break; 
		printf("Enter an integer:"); 
		scanf("%d", &n); 

		size = size+1; 
		p_arr = realloc(p_arr, size * sizeof(int)); 
		assert(p_arr); 
		p_arr[size-1] = n; 
	}

	for(i = 0; i < size; ++i){
		printf("p_arr[%d]:%d\n", i, p_arr[i]); 
	}

	free(p_arr); 
	p_arr = NULL; 

	return 0; 
}