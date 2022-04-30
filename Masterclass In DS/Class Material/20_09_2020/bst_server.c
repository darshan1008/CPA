#include <stdio.h> 
#include <stdlib.h> 

#include "bst.h" 

bst_t* create_bst(){
	return (bst_t*)xcalloc(1, sizeof(bst_t)); 
}

ret_t insert_bst(bst_t* p_bst, data_t new_data){
	bst_node_t* p_run = p_bst->p_root_node; 
	bst_node_t* p_new_node = NULL; 

	p_new_node = get_bst_node(new_data); 

	if(p_run == NULL){
		p_bst->p_root_node = p_new_node; 
		p_bst->nr_elements++; 
		return (SUCCESS); 
	}

	while(TRUE){
		if(p_run->data <= new_data){
			if(p_run->left == NULL){
				p_run->left = p_new_node; 
				p_new_node->parent = p_run; 
				break; 
			}
			p_run = p_run->left; 
			continue; 
		}
		else{
			if(p_run->right == NULL){
				p_run->right = p_new_node; 
				p_new_node->parent = p_run;  
				break; 
			}
			p_run = p_run->right; 
			continue;
		}
	}

	p_bst->nr_elements++; 
	return (SUCCESS); 
} 

bool search_data(bst_t* p_bst, data_t search_data){
 	return (seach_node(p_bst, search_data) != NULL); 
}

bst_node_t* get_bst_node(data_t new_data){
	bst_node_t* p_bst_node = (bst_node_t*)xcalloc(1, sizeof(bst_node_t)); 
	p_bst_node->data = new_data; 
	return (p_bst_node); 
}

bst_node_t* search_node(bst_t* p_bst, data_t search_data){
	bst_node_t* p_run = p_bst->p_root_node; 
	while(p_run != NULL){
		if(p_run->data == search_data)
			break; 
		else if(p_run->data < search_data)
			p_run = p_run->left; 
		else
			p_run = p_run->right; 
	}
	return (p_run); 
}

void __bst_preorder(bst_node_t* p_root_node){
	if(p_root_node != NULL){
		printf("[%d]<->", p_root_node->data); 
		__bst_preorder(p_root_node->left); 
		__bst_preorder(p_root_node->right); 
	}
}

ret_t bst_preorder(bst_t* p_bst){
	printf("[START]<->"); 
	__bst_preorder(p_bst->p_root_node); 
	puts("[END]"); 
}

