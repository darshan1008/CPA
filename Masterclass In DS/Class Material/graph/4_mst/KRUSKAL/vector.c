#include <stdio.h> 
#include <stdlib.h> 
#include <assert.h>

#define TRUE 1 
#define SUCCESS 1 

typedef struct vector_int vector_int_t; 

struct vector_int{
	int *p_arr; 
	int size; 
}; 

// API 

vector_int_t *create_vector_int(); 
int push_back(vector_int_t *p_vec_int, int new_element); 
int get_vec_element(vector_int_t*, int index, int *p_data); 
int get_vec_size(vector_int_t*); 
int destroy_vector_int(vector_int_t *p_vec_int); 


int main(){
	vector_int_t *p_vec_int = NULL; 
	int n; 
	int choice; 
	int i; 

	p_vec_int = create_vector_int(); 	

	while(TRUE){
		printf("Do you want to enter a number? [1/0]:"); 
		scanf("%d", &choice); 
		if(choice == 0)
		 	break; 
		printf("Enter an integer:"); 
		scanf("%d", &n); 
		push_back(p_vec_int, n); 		
	}

	for(i = 0; i < get_vec_size(p_vec_int); ++i){
		get_vec_element(p_vec_int, i, &n); 
		printf("vec[%d]:%d\n", i, n); 
	}

	destroy_vector_int(p_vec_int); 
	p_vec_int = NULL; 

	return (EXIT_SUCCESS); 
}

vector_int_t *create_vector_int(){
	vector_int_t *p_vec_int = (vector_int_t*)malloc(sizeof(vector_int_t)); 
	assert(p_vec_int); 
	p_vec_int->p_arr = NULL; 
	p_vec_int->size = 0; 
	return (p_vec_int); 
}

int push_back(vector_int_t *p_vec_int, int new_element){
	p_vec_int->size++; 
	p_vec_int->p_arr = (int*)realloc(p_vec_int->p_arr, p_vec_int->size * sizeof(int));
	assert(p_vec_int->p_arr); 
	p_vec_int->p_arr[p_vec_int->size - 1] = new_element; 
	return (SUCCESS);  
}

int get_vec_element(vector_int_t *p_vec_int, int index, int *p_data){
	*p_data = p_vec_int->p_arr[index]; 
	return (SUCCESS); 
}

int get_vec_size(vector_int_t *p_vec_int){
	return (p_vec_int->size); 
}

int destroy_vector_int(vector_int_t *p_vec_int){
	free(p_vec_int->p_arr); 
	free(p_vec_int); 
	return (SUCCESS); 
}