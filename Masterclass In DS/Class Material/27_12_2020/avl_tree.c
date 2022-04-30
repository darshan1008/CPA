#include <stdio.h> 
#include <stdlib.h>
#include <assert.h>

#define SUCCESS 1
#define TRUE 1 
#define AVL_DATA_NOT_FOUND 2 

typedef struct avl_node avl_node_t; 
typedef struct avl_tree avl_tree_t; 

typedef int ret_t; 

struct avl_node{
	int data; 
	int height; 
	struct avl_node* left; 
	struct avl_node* right; 
	struct avl_node* parent; 
};

struct avl_tree{
	struct avl_node* p_root_node; 
	unsigned int nr_elements; 
};  

/* interface routines */ 
avl_tree_t* create_avl_tree(); 
ret_t insert_avl_tree(avl_tree_t* p_avl_tree, int new_data); 
void inorder(avl_tree_t* p_avl_tree); 

/* auxillary routines */ 
void left_rotate(avl_tree_t* p_avl_tree, avl_node_t* x); 
void right_rotate(avl_tree_t* p_avl_tree, avl_node_t* x); 
void* xmalloc(size_t size); 
int get_height(avl_node_t* p_node); 
int get_max(int h1, int h2); 
int get_balance(avl_node_t* p_node); 
void __inorder(avl_node_t* p_root_node); 
avl_node_t* get_avl_node(int new_data); 

int main(){
	int data[] = {50, 40, 60, 30, 70, 35, 65, 37, 75}; 
	int i;  
	
	avl_tree_t* p_avl_tree = create_avl_tree(); 
	for(i = 0; i < sizeof(data) / sizeof(data[0]); ++i) 
		assert(insert_avl_tree(p_avl_tree, data[i]) == SUCCESS); 

	inorder(p_avl_tree); 
	return (EXIT_SUCCESS); 
}

avl_tree_t* create_avl_tree(){
	avl_tree_t* p_avl_tree = xmalloc(sizeof(avl_tree_t)); 
	p_avl_tree->p_root_node = NULL; 
	p_avl_tree->nr_elements = 0; 
	return p_avl_tree; 

}

void inorder(avl_tree_t* p_avl_tree){
	__inorder(p_avl_tree->p_root_node); 
}

ret_t insert_avl_tree(avl_tree_t* p_avl_tree, int new_data){
	avl_node_t* p_avl_node = get_avl_node(new_data); 
	avl_node_t* p_run = NULL; 
	if(p_avl_tree->p_root_node == NULL){
		p_avl_tree->p_root_node = p_avl_node; 
		return (SUCCESS); 
	}
	p_run = p_avl_tree->p_root_node;	
	while(TRUE){ 
		p_avl_node->height += 1; 
		if(new_data <= p_run->data){
			if(p_run->left == NULL){
				p_run->left = p_avl_node; 
				p_avl_node->parent = p_run;  
				break;  
			}
			p_run = p_run->left; 
		}
		else{
			if(p_run->right == NULL){
				p_run->right = p_avl_node; 
				p_avl_node->parent = p_run; 
				break;  
			}
			p_run = p_run->right; 
		}
	}

	printf("p_run->data = %d\np_avl_node->data = %d\n", p_run->data, p_avl_node->data); 
	return (SUCCESS); 
}

void __inorder(avl_node_t* p_root_node){
	if(p_root_node != NULL){
		__inorder(p_root_node->left); 
		printf("data:%d height:%d\n", p_root_node->data, p_root_node->height); 
		__inorder(p_root_node->right); 
	}
}

void left_rotate(avl_tree_t* p_avl_tree, avl_node_t* x){
	avl_node_t* y = NULL; 

	y = x->right; 
	x->right = y->left; 

	if(y->left != NULL)
		y->parent->left = x; 

	if(x->parent == NULL)
		p_avl_tree->p_root_node = y; 
	else if(x == x->parent->left)
		x->parent->left = y; 
	else 
		x->parent->right = y; 

	y->left = x; 
	x->parent = y; 

	x->height = get_max(get_height(x->left), get_height(x->right)) + 1; 
	y->height = get_max(get_height(y->left), get_height(y->right)) + 1; 
}

void right_rotate(avl_tree_t* p_avl_tree, avl_node_t* x){
	avl_node_t* y = NULL; 

	y = x->left; 
	x->left = y->right; 

	if(y->right != NULL)
		y->parent->right = x; 

	if(x->parent == NULL)
		p_avl_tree->p_root_node = y; 
	else if(x == x->parent->left)
		x->parent->left = y; 
	else 
		x->parent->right = y; 

	y->right = x; 
	x->parent = y; 

	x->height = get_max(get_height(x->left), get_height(x->right)) + 1; 
	y->height = get_max(get_height(y->left), get_height(y->right)) + 1; 
}

avl_node_t* get_avl_node(int new_data){
	avl_node_t* p_new_node = (avl_node_t*)xmalloc(sizeof(avl_node_t)); 
	p_new_node->data = new_data;
	p_new_node->height = 0; 
	p_new_node->left = NULL; 
	p_new_node->right = NULL; 
	p_new_node->parent = NULL; 
	return (p_new_node); 
}

int get_balance(avl_node_t* p_node){
	if(p_node == NULL)
		return (0); 
	return (get_height(p_node->left) - get_height(p_node->right)); 
}

int get_max(int h1, int h2){
	if(h1 > h2)
		return (h1); 
	else
		return (h2); 
}

int get_height(avl_node_t* p_node){
	if(p_node == NULL)
		return (0); 
	return (p_node->height); 
}

void* xmalloc(size_t size){
	void* p = malloc(size); 
	assert(p); 
	return (p); 
}
