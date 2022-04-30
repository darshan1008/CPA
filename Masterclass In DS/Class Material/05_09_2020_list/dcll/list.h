#ifndef _LIST_H 
#define _LIST_H 

/* Symbolic constants */ 
#define SUCCESS 			1 
#define TRUE 				1 
#define FALSE 				0 
#define LIST_DATA_NOT_FOUND 2 
#define LIST_EMPTY 			3 

/* typedefs */ 
struct node; 
typedef struct node node_t; 
typedef node_t list_t; 
typedef int data_t; 
typedef int ret_t; 
typedef int len_t; 
typedef int bool; 

/* Data layout definitions */ 
struct node{
	data_t data; 
	struct node* prev; 
	struct node* next; 
}; 

/* Interface functions : prototypes */ 
/* Resource creation */ 
list_t* create_list(void);
/* Resource usage */ 
	/* insertion */ 
ret_t insert_beg(list_t* p_list, data_t new_data); 
ret_t insert_end(list_t* p_list, data_t new_data); 
ret_t insert_after(list_t* p_list, data_t e_data, data_t new_data); 
ret_t insert_before(list_t* p_list, data_t e_data, data_t new_data); 
	/* get & pop */ 
ret_t get_beg(list_t* p_list, data_t* p_beg_data); 
ret_t get_end(list_t* p_list, data_t* p_end_data); 
ret_t pop_beg(list_t* p_list, data_t* p_beg_data); 
ret_t pop_end(list_t* p_list, data_t* p_end_data); 
	/* delete */ 
ret_t delete_beg(list_t* p_list); 
ret_t delete_end(list_t* p_list); 
ret_t delete_data(list_t* p_list, data_t d_data); 
	/* query */ 
bool is_list_empty(list_t* p_list); 
bool find_list(list_t* p_list, data_t f_data); 
	/* misc */ 
len_t get_list_length(list_t* p_list); 
void  show_list(list_t* p_list); 
	/* inter list routines */ 
list_t* concat_immutable(list_t* p_list1, list_t* p_list2); 
ret_t concat_mutable(list_t* p_list1, list_t* p_list2);
list_t* merge_lists(list_t* p_list1, list_t* p_list2); 
ret_t to_array(list_t* p_list, data_t** pp_array, size_t* p_size); 
ret_t to_list(data_t* p_array, size_t n, list_t** pp_list); 
/* Release resource */ 
	/* destruction */ 
ret_t destroy_list(list_t** pp_list); 

/* List auxillary functions : prototypes */ 
static node_t* get_node(data_t data); 
static void generic_insert(node_t* p_beg, node_t* p_mid, node_t* p_end); 
static void generic_delete(node_t* p_delete_node); 
static node_t* search_node(list_t* p_list, data_t s_data); 

/* Auxillary functions : prototypes */ 
static void* xcalloc(size_t nr_elements, size_t size_per_element); 

#endif /* _LIST_H */ 



