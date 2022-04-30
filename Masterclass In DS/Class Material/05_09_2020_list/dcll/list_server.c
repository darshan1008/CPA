#include <stdio.h> 
#include <stdlib.h>
#include <assert.h> 
#include <string.h> 
#include "list.h"

/* Interface functions : prototypes */ 
/* Resource creation */ 
list_t* create_list(void){
	list_t* p_new_list = NULL; 

	p_new_list = get_node(-1);

	/* critical! */  
	p_new_list->prev = p_new_list; 
	p_new_list->next = p_new_list; 

	return (p_new_list); 
}
/* Resource usage */ 
	/* insertion */ 
ret_t insert_beg(list_t* p_list, data_t new_data){
	generic_insert(p_list, get_node(new_data), p_list->next); 
	return (SUCCESS); 
}

ret_t insert_end(list_t* p_list, data_t new_data){
	generic_insert(p_list->prev, get_node(new_data), p_list); 
	return (SUCCESS); 
}

ret_t insert_after(list_t* p_list, data_t e_data, data_t new_data){
	node_t* p_ext_node = search_node(p_list, e_data); 
	if(p_ext_node == NULL)
		return (LIST_DATA_NOT_FOUND); 
	generic_insert(p_ext_node, get_node(new_data), p_ext_node->next); 
	return (SUCCESS); 
}

ret_t insert_before(list_t* p_list, data_t e_data, data_t new_data){
	node_t* p_ext_node = search_node(p_list, e_data); 
	if(p_ext_node == NULL)
		return (LIST_DATA_NOT_FOUND); 
	generic_insert(p_ext_node->prev, get_node(new_data), p_ext_node); 
	return (SUCCESS); 
}
	/* get & pop */ 
ret_t get_beg(list_t* p_list, data_t* p_beg_data){
	if(is_list_empty(p_list) == TRUE)
		return (LIST_EMPTY); 
	*p_beg_data = p_list->next->data; 
	return (SUCCESS); 
}

ret_t get_end(list_t* p_list, data_t* p_end_data){
	if(is_list_empty(p_list) == TRUE)
		return (LIST_EMPTY); 
	*p_end_data = p_list->prev->data; 
	return (SUCCESS); 
}

ret_t pop_beg(list_t* p_list, data_t* p_beg_data){
	if(is_list_empty(p_list) == TRUE)
		return (LIST_EMPTY); 
	*p_beg_data = p_list->next->data; 
	generic_delete(p_list->next); 
	return (SUCCESS); 
}

ret_t pop_end(list_t* p_list, data_t* p_end_data){
	if(is_list_empty(p_list) == TRUE)
		return (LIST_EMPTY); 
	*p_end_data = p_list->prev->data; 
	generic_delete(p_list->prev); 
	return (SUCCESS); 
}
	/* delete */ 
ret_t delete_beg(list_t* p_list){
	if(is_list_empty(p_list) == TRUE)
		return (LIST_EMPTY); 
	generic_delete(p_list->next); 
	return (SUCCESS); 
}

ret_t delete_end(list_t* p_list){
	if(is_list_empty(p_list) == TRUE)
		return (LIST_EMPTY); 
	generic_delete(p_list->prev); 
	return (SUCCESS); 
}

ret_t delete_data(list_t* p_list, data_t d_data){
	node_t* p_delete_node = search_node(p_list, d_data); 
	if(p_delete_node == NULL)
		return (LIST_DATA_NOT_FOUND); 
	generic_delete(p_delete_node); 
	return (SUCCESS); 
}
	/* query */ 

bool is_list_empty(list_t* p_list){
	return (p_list->prev == p_list && p_list->next == p_list); 
}

bool find_list(list_t* p_list, data_t f_data){
	return (search_node(p_list, f_data) != NULL); 
}
	/* misc */ 

len_t get_list_length(list_t* p_list){
	len_t len = 0; 
	node_t* p_run = NULL; 

	for(p_run = p_list->next; p_run != p_list; p_run = p_run->next, ++len)
		; 

	return (len); 
}

void  show_list(list_t* p_list){
	node_t* p_run = NULL; 
	printf("[START]<->"); 
	for(p_run = p_list->next; p_run != p_list; p_run = p_run->next)
		printf("[%d]<->", p_run->data); 
	puts("[END]"); 
}

	/* inter list routines */ 
list_t* concat_immutable(list_t* p_list1, list_t* p_list2){
	list_t* p_cat_list = create_list(); 
	node_t* p_run = NULL; 

	for(p_run = p_list1->next; p_run != p_list1; p_run = p_run->next)
		insert_end(p_cat_list, p_run->data); 
	
	for(p_run = p_list2->next; p_run != p_list2; p_run = p_run->next)
		insert_end(p_cat_list, p_run->data); 

	return (p_cat_list); 
}	

ret_t concat_mutable(list_t* p_list1, list_t* p_list2){
	if(is_list_empty(p_list2) == TRUE)
		return (SUCCESS); 

	p_list1->prev->next = p_list2->next; 
	p_list2->next->prev = p_list1->prev; 
	
	free(p_list2); 
	p_list2 = NULL; 

	return (SUCCESS); 
}

list_t* merge_lists(list_t* p_list1, list_t* p_list2){
	node_t* p_run1 = NULL; 
	node_t* p_run2 = NULL; 

	list_t* p_merged_list = create_list(); 

	p_run1 = p_list1->next; 
	p_run2 = p_list2->next; 

	while(TRUE){
		if(p_run1 == p_list1){
			while(p_run2 != p_list2){
				insert_end(p_merged_list, p_run2->data); 
				p_run2 = p_run2->next;
			}
			break; 
		}

		if(p_run2 == p_list2){
			while(p_run1 != p_list1){
				insert_end(p_merged_list, p_run1->data); 
				p_run1 = p_run1->next; 
			}
			break; 
		}

		if(p_run1->data <= p_run2->data){
			insert_end(p_merged_list, p_run1->data); 
			p_run1 = p_run1->next; 
		}else{
			insert_end(p_merged_list, p_run2->data); 
			p_run2 = p_run2->next; 
		}
	}

	return (p_merged_list); 
}

ret_t to_array(list_t* p_list, data_t** pp_array, size_t* p_size){
	data_t* p_array = NULL; 
	size_t size = 0; 
	node_t* p_run = NULL; 
	len_t len = -1; 
	int i; 

	len = get_list_length(p_list); 
	if(len == 0){
		*pp_array = p_array; 
		*p_size = size; 
		return (SUCCESS); 
	}

	size = len; 
	p_array = (data_t*)xcalloc(size, sizeof(data_t)); 

	p_run = p_list->next; 
	i = 0; 
	while(p_run != p_list){
		p_array[i] = p_run->data; 
		i = i + 1; 
		p_run = p_run->next; 
	}

	*pp_array = p_array; 
	*p_size = size; 

	return (SUCCESS); 

}

ret_t to_list(data_t* p_array, size_t n, list_t** pp_list){
	list_t* p_new_list = NULL; 
	int i = -1; 

	p_new_list = create_list(); 
	for(i = 0; i < n; ++i)
		insert_end(p_new_list, p_array[i]); 

	*pp_list = p_new_list; 
	return (SUCCESS); 
}

/* Release resource */ 
	/* destruction */ 
ret_t destroy_list(list_t** pp_list){
	node_t* p_run; 
	node_t* p_run_next; 
	list_t* p_list = *pp_list; 
	
	p_run = p_list->next; 
	while(p_run != p_list){
		p_run_next = p_run->next; 
		free(p_run); 
		p_run = p_run_next; 
	}

	free(p_list); 
	*pp_list = NULL; 
	return (SUCCESS); 
}

/* List auxillary functions : prototypes */ 
static node_t* get_node(data_t data){
	node_t* p_new_node = NULL; 

	p_new_node = (node_t*)xcalloc(1, sizeof(node_t)); 
	p_new_node->data = data; 
	return (p_new_node); 
}

static void generic_insert(node_t* p_beg, node_t* p_mid, node_t* p_end){
	p_mid->next = p_end;
	p_mid->prev = p_beg; 
	p_beg->next = p_mid; 
	p_end->prev = p_mid; 
}

static void generic_delete(node_t* p_delete_node){
	p_delete_node->next->prev = p_delete_node->prev; 
	p_delete_node->prev->next = p_delete_node->next; 
	free(p_delete_node); 
}

static node_t* search_node(list_t* p_list, data_t s_data){
	node_t* p_run = NULL; 

	for(p_run = p_list->next; p_run != p_list; p_run = p_run->next)
		if(p_run->data == s_data)
			return (p_run); 
	return (NULL); 
}

/* Auxillary functions : prototypes */ 
static void* xcalloc(size_t nr_elements, size_t size_per_element){
	void* p = NULL; 
	p = calloc(nr_elements, size_per_element); 
	if(p == NULL){
		fprintf(stderr, "calloc:fatal:out of virtual memory\n"); 
		exit(EXIT_FAILURE); 
	}

	return (p); 
}

