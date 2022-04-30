#include <stdio.h> 
#include <stdlib.h> 
#include <assert.h> 
#include <string.h> 
#include <time.h> 

/* Symbolic constants */ 
#define SEARCH_SPACE 1000 
#define NR_KEYS 300
#define BUCKET_SIZE 11 

#define SUCCESS 1 
#define TRUE 1
#define FALSE 0 

#define LIST_EMPTY 2 
#define LIST_DATA_NOT_FOUND 3
#define KEY_NOT_FOUND 4 


/* Macros */ 
#define HASH_FUNCTION(key)	(key % BUCKET_SIZE)

/* type definitions */ 
typedef int key_t; 
typedef int ret_t; 
typedef int bool; 
typedef struct hash hash_t; 
typedef struct node node_t; 
typedef node_t list_t; 

/* interface functions */ 
hash_t* create_hash(size_t bucket_size);
ret_t insert_key(hash_t* p_hash, key_t key); 
bool search_key(hash_t* p_hash, key_t key); 
ret_t remove_key(hash_t* p_hash, key_t key); 
ret_t destroy_hash(hash_t** pp_hash); 

/* hash auxillary routines */
ret_t insert_end(list_t* p_list, key_t key); 
ret_t delete_data(list_t* p_list, key_t key); 

void generic_insert(node_t* p_beg, node_t* p_mid, node_t* p_end); 
void generic_delete(node_t* p_delete_node); 
node_t* search_node(list_t* p_list, key_t key); 
node_t* get_node(key_t key); 

/* auxillary routine */ 
void* xcalloc(size_t nr_elements, size_t size_per_element); 
void fill_keys(); 
size_t fill_non_keys(); 

/* data layout */ 
struct node{
	key_t key;
	struct node* prev;
	struct node* next;  
}; 

struct hash{
	node_t* p_hash_arr; 
	size_t bucket_size; 
}; 

/* global data */ 
int keys[NR_KEYS];
int non_keys[700]; 

int main(){
	hash_t* p_hash = NULL; 
	size_t nr_non_keys; 
	ret_t ret; 
	int i; 
	bool rs; 
	int cnt; 

	fill_keys(); 
	nr_non_keys = fill_non_keys(); 

	p_hash = create_hash(BUCKET_SIZE); 
	assert(p_hash); 

	for(i = 0; i < NR_KEYS; ++i){
		ret = insert_key(p_hash, keys[i]); 
		assert(ret == SUCCESS); 
	}
	
	cnt = 0; 
	for(i = 0; i < NR_KEYS; ++i){
		rs = search_key(p_hash, keys[i]); 
		if(rs == TRUE){
			++cnt; 
			printf("%d\t%d\tis present in hash\n", cnt, keys[i]); 	
		}
	}
	
	cnt = 0; 
	for(i = 0; i < nr_non_keys; ++i){
		rs = search_key(p_hash, non_keys[i]); 
		if(rs == FALSE){
			++cnt; 
			printf("%d\t%d\tis not present in hash\n", cnt, non_keys[i]); 
		}
	}

	ret = destroy_hash(&p_hash); 
	assert(ret == SUCCESS && p_hash == NULL); 
	return (EXIT_SUCCESS); 
}

hash_t* create_hash(size_t bucket_size){
	hash_t* p_hash = NULL; 
	int i; 

	if(bucket_size == 0){
		fprintf(stderr, "Bad bucket size. Hash creation failed\n"); 
		exit(EXIT_FAILURE); 
	}

	/* allocation of hash information structure and underlying array */ 
	p_hash = (hash_t*)xcalloc(1, sizeof(hash_t)); 
	p_hash->bucket_size = bucket_size; 
	p_hash->p_hash_arr = (node_t*)xcalloc(bucket_size, sizeof(node_t)); 

	/* initialization of hash ds */ 
	for(i = 0; i < bucket_size; ++i){
		p_hash->p_hash_arr[i].prev = &p_hash->p_hash_arr[i]; 
		p_hash->p_hash_arr[i].next = &p_hash->p_hash_arr[i];
	}

	return (p_hash); 
}

ret_t insert_key(hash_t* p_hash, key_t key){
	int index; 

	index = HASH_FUNCTION(key); 
	insert_end(&p_hash->p_hash_arr[index], key);
   	return (SUCCESS); 	
}

bool search_key(hash_t* p_hash, key_t key){
	int index; 
	node_t* p_node = NULL; 

	index = HASH_FUNCTION(key); 
	p_node = search_node(&p_hash->p_hash_arr[index], key); 

	return (p_node != NULL); 
}

ret_t remove_key(hash_t* p_hash, key_t key){
	int index; 
	node_t* p_node = NULL; 

	index = HASH_FUNCTION(key); 
	p_node = search_node(&p_hash->p_hash_arr[index], key); 
	if(p_node == NULL)
		return (KEY_NOT_FOUND); 
	
	generic_delete(p_node); 
	return (SUCCESS); 
}

ret_t destroy_hash(hash_t** pp_hash){
	hash_t* p_hash = *pp_hash; 
	node_t* p_run, *p_run_next; 
	int i; 
	
	/* iteratively delete all chains */ 
	for(i = 0; i < p_hash->bucket_size; ++i){
		p_run = p_hash->p_hash_arr[i].next; 
		while(p_run != &p_hash->p_hash_arr[i]){
			p_run_next = p_run->next; 
			free(p_run); 
			p_run = p_run_next; 
		}
	}

	/* delete bucket */ 
	free(p_hash->p_hash_arr);
   /* delete hash information structure */ 	
	free(p_hash); 
	*pp_hash = NULL; 

	return (SUCCESS); 
}

/* hash auxillary routines */
ret_t insert_end(list_t* p_list, key_t key){
	generic_insert(p_list->prev, get_node(key), p_list); 
	return (SUCCESS); 
}

ret_t delete_data(list_t* p_list, key_t key){
	node_t* p_delete_node = search_node(p_list, key); 
	if(p_delete_node == NULL)
		return (LIST_DATA_NOT_FOUND); 
	generic_delete(p_delete_node); 
	return (SUCCESS); 
}

void generic_insert(node_t* p_beg, node_t* p_mid, node_t* p_end){
	p_mid->next = p_end; 
	p_mid->prev = p_beg; 
	p_beg->next = p_mid; 
	p_end->prev = p_mid; 
}

void generic_delete(node_t* p_delete_node){
	p_delete_node->prev->next = p_delete_node->next; 
	p_delete_node->next->prev = p_delete_node->prev; 
	free(p_delete_node); 
}

node_t* search_node(list_t* p_list, key_t key){
	node_t* p_run; 

	for(p_run = p_list->next; p_run != p_list; p_run = p_run->next)
		if(p_run->key == key)
			return (p_run); 

	return (NULL); 
}

node_t* get_node(key_t key){
	node_t* p_node = (node_t*)xcalloc(1, sizeof(node_t)); 
	p_node->key = key; 
	return (p_node); 
}

/* auxillary functions */ 

void* xcalloc(size_t nr_elements, size_t size_per_element){
	void* p = calloc(nr_elements, size_per_element); 
	if(p == NULL){
		fprintf(stderr, "calloc:out of virtual memory\n"); 
		exit(EXIT_FAILURE); 
	}
	
	return (p); 
}

void fill_keys(){
	int i; 
	srand(time(0)); 
	for(i = 0; i < NR_KEYS;  ++i)
		keys[i] = rand() % SEARCH_SPACE; 
}

size_t fill_non_keys(){
	int i; 
	int j; 
	int k;
   		
	k = 0; 
	for(i = 0; i < SEARCH_SPACE; ++i){
		for(j = 0; j < NR_KEYS; ++j){
			if(i == keys[j])
				break; 
		}
		if(j == NR_KEYS){
			non_keys[k] = i; 
			k++; 
		}		
	}

	return (k); 
}
