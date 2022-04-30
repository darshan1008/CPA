ret_t to_array(list_t* p_list, data_t** pp_array, size_t* p_size){
	data_t* p_array = NULL; 
	size_t size = 0; 
	node_t* p_run = NULL; 

	for(p_run = p_list->next; p_run != p_list; p_run = p_run->next){
		size = size + 1; 
		p_array = (data_t*)realloc(p_array, size * sizeof(data_t)); 
		p_array[size-1] = p_run->data; 
	}

	*pp_array = p_array; 
	*p_size = size; 

	return (SUCCESS); 
}

/* exercise 1 */ 

typedef struct dynamic_array{
	int* a; 
	size_t N; 
}vector_t; 

vector_t* create_vector(); 
ret_t push_back(vector_t* p_vec, data_t new_data); 
void show_vector(vector_t* p_vec); 
ret_t destroy_vector(vector_t* p_vec); 

/* C++ primer : 3rd : How Vector Grows */ 

typedef struct dynamic_array{
	int* a; 
	size_t size; 
	size_t capacity; 
}; 

vector_t* create_vector(); 
ret_t push_back(vector_t* p_vec, data_t new_data); 
void show_vector(vector_t* p_vec); 
ret_t destroy_vector(vector_t* p_vec); 


/* exercise 3 */ 

for(std::vector<int>::iterator iter = ivec.begin(); 
	iter != ivec.end(); 
	++iter){

	*iter 
}

/* 
for_each reference: 

	Understanding The Linux Kernel 
	Chapter 3 : Processes 
		Kernel Linked List 
			TABLE 
*/ 