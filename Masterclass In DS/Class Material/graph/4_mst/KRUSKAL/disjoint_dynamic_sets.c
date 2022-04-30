#include <stdio.h> 
#include <stdlib.h>
#include <assert.h>

#define TRUE 1 
#define SUCCESS 1 
#define DD_DATA_NOT_FOUND 2

/* vector declarations and interface */ 
typedef struct vector_int vector_int_t; 

struct vector_int{
	int *p_arr; 
	int size; 
}; 

vector_int_t *create_vector_int(); 
int push_back(vector_int_t *p_vec_int, int new_element); 
int get_vec_element(vector_int_t*, int index, int *p_data); 
int get_vec_size(vector_int_t*); 
int destroy_vector_int(vector_int_t *p_vec_int); 

/* disjoint dynamic sets */ 

struct node{
	struct vector_int *p_vec; 
	struct node *prev; 
	struct node *next; 
}; 

typedef struct node disjoint_set_t; 

disjoint_set_t *create_disjoint_dynamic_collection(); 
int make_set(disjoint_set_t *p_dd_collection, int n); 
int take_union(disjoint_set_t *p_dd_collection, int x, int y); 
struct node *find_set(disjoint_set_t *p_dd_collection, int x); 
void print_dd(disjoint_set_t *p_dd_collection); 
void destroy_disjoint_dynamic_collection(disjoint_set_t *p_dd_collection); 

void generic_insert(struct node *p_beg, struct node *p_mid, struct node *p_end); 
void generic_delete(struct node *p_delete_node); 
struct node *search_node(struct node *p_dd_collection, int n); 
struct node *get_node(); 

int main(){
	int data; 
	disjoint_set_t *p_dd_collection = create_disjoint_dynamic_collection(); 

	for(data = 1; data < 6; ++data)
		make_set(p_dd_collection, data); 

	print_dd(p_dd_collection); 
	take_union(p_dd_collection, 1, 5); 
	print_dd(p_dd_collection); 
	take_union(p_dd_collection, 5, 2); 
	print_dd(p_dd_collection); 
	take_union(p_dd_collection, 2, 4); 
	print_dd(p_dd_collection); 
	take_union(p_dd_collection, 3, 5); 
	print_dd(p_dd_collection); 

	return (0); 
}

disjoint_set_t *create_disjoint_dynamic_collection(){
	struct node *p_new_dd_collection = NULL; 
	p_new_dd_collection = (struct node*)malloc(sizeof(struct node)); 
	p_new_dd_collection->p_vec = NULL; 
	p_new_dd_collection->prev = p_new_dd_collection; 
	p_new_dd_collection->next = p_new_dd_collection; 
	return (p_new_dd_collection); 
}

int make_set(disjoint_set_t *p_dd_collection, int n){
	struct node *p_new_node = get_node(); 
	push_back(p_new_node->p_vec, n); 
	generic_insert(p_dd_collection->prev, p_new_node, p_dd_collection); 
	return (SUCCESS); 
}

int take_union(disjoint_set_t *p_dd_collection, int x, int y){
	struct node *px_set = NULL; 
	struct node *py_set = NULL; 
	struct node *p_union_set = NULL; 

	vector_int_t *px_vec = NULL; 
	vector_int_t *py_vec = NULL; 
	int i; 

	px_set = search_node(p_dd_collection, x); 
	assert(px_set != NULL); 

	py_set = search_node(p_dd_collection, y); 
	assert(py_set != NULL); 

	p_union_set = get_node(); 
	for(i = 0; i < px_set->p_vec->size; ++i)
		push_back(p_union_set->p_vec, px_set->p_vec->p_arr[i]); 
	for(i = 0; i < py_set->p_vec->size; ++i)
		push_back(p_union_set->p_vec, py_set->p_vec->p_arr[i]); 

	generic_delete(px_set); 
	generic_delete(py_set); 
	generic_insert(p_dd_collection->prev, p_union_set, p_dd_collection); 

	return (SUCCESS); 
}

struct node *find_set(disjoint_set_t *p_dd_collection, int x){
	struct node *p_run = NULL; 
	int i; 

	for(p_run = p_dd_collection->next; p_run != p_dd_collection; p_run = p_run->next)
		for(i = 0; i < p_run->p_vec->size; ++i)
			if(p_run->p_vec->p_arr[i] == x)
				return (p_run); 

	return (NULL);
}

void print_dd(disjoint_set_t *p_dd_collection){
	struct node *p_run = NULL; 
	int i; 

	for(p_run = p_dd_collection->next; p_run != p_dd_collection; p_run = p_run->next){
		printf("[SET]\t<--->\t"); 
		for(i = 0; i < p_run->p_vec->size; ++i)
			printf("[%d]<->", p_run->p_vec->p_arr[i]); 
		puts("[END]"); 
	}

	puts("***********************************************************"); 

}

void destroy_disjoint_dynamic_collection(disjoint_set_t *p_dd_collection){
	struct node *p_run = NULL; 
	struct node *p_run_next = NULL; 

	for(p_run = p_dd_collection->next; p_run != p_dd_collection; p_run = p_run_next){
		p_run_next = p_run->next; 
		destroy_vector_int(p_run->p_vec); 
		free(p_run); 
	}

	free(p_dd_collection); 
	p_dd_collection = NULL; 
}


struct node *search_node(struct node *p_dd_collection, int n){
	struct node *p_run = NULL; 
	int i; 

	for(p_run = p_dd_collection->next; p_run != p_dd_collection; p_run = p_run->next){
		for(i = 0; i < p_run->p_vec->size; ++i)
			if(p_run->p_vec->p_arr[i] == n)
				return (p_run); 
	}

	return (NULL); 
}

void generic_insert(struct node *p_beg, struct node *p_mid, struct node *p_end){
	p_mid->next = p_end; 
	p_mid->prev = p_beg; 
	p_beg->next = p_mid; 
	p_end->prev = p_mid; 
}

void generic_delete(struct node *p_delete_node){
	p_delete_node->next->prev = p_delete_node->prev; 
	p_delete_node->prev->next = p_delete_node->next; 
	destroy_vector_int(p_delete_node->p_vec); 
	free(p_delete_node); 
}

struct node *get_node(){
	struct node *p_new_node = (struct node*)malloc(sizeof(struct node)); 
	p_new_node->p_vec = create_vector_int(); 
	p_new_node->prev = NULL; 
	p_new_node->next = NULL; 
	return (p_new_node); 
}

/* vector implementation */ 
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