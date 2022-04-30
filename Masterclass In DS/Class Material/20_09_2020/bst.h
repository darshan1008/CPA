#ifndef _BST_H 
#define _BST_H 

/* symbolic constants */ 

#define SUCCESS 1 
#define TRUE 	1 
#define FALSE 	0 

#define BST_EMPTY 			2 
#define BST_NO_PREDECESSOR 	3 
#define BST_NO_SUCCESSOR 	4 

/* type definitions */ 
typedef struct bst_node bst_node_t; 
typedef struct bst bst_t; 
typedef int data_t; 
typedef int ret_t; 

/* data layout */ 
struct bst_node{
	data_t data; 
	struct bst_node* left; 
	struct bst_node* right; 
	struct bst_node* parent; 
}; 

struct bst{
	bst_node_t* p_root_node; 
	size_t nr_elements; 
}; 

/* interface routines */ 

/* BST management */ 
bst_t* create_bst(void); 
ret_t insert_bst(bst_t* p_bst, data_t new_data); 
bool search_bst(bst_t* p_bst, data_t search_data); 
ret_t remove_bst(bst_t* p_bst, data_t remove_data); 
ret_t destroy_bst(bst_t** pp_bst); 

/* BST Traversal */ 
ret_t preorder(bst_t* p_bst); 
ret_t inorder(bst_t* p_bst); 
ret_t postorder(bst_t* p_bst); 
ret_t preorder_nrc(bst_t* p_bst); 
ret_t inorder_nrc(bst_t* p_bst); 
ret_t postorder_nrc(bst_t* p_bst); 

/* Precessor & Successor */ 
ret_t inorder_predecessor(bst_t* p_bst, data_t e_data, data_t* p_pred_data); 
ret_t inorder_successor(bst_t* p_bst, data_t e_data, data_t* p_succ_data); 

/* Min & Max */ 
ret_t max_bst(bst_t* p_bst, data_t* p_max_data); 
ret_t min_bst(bst_t* p_bst, data_t* p_min_data); 

/****************************************************************************/ 
/* bst auxillary routines */ 

void __bst_preorder(bst_node_t* p_root_node); 
void __bst_inorder(bst_node_t* p_root_node); 
void __bst_postorder(bst_node_t* p_root_node); 

bst_node_t* get_bst_node(data_t new_data); 


/* axuillary routines */ 
void* xcalloc(size_t nr_elements, size_t size_element);

