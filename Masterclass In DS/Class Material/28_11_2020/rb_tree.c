#include <stdio.h> 
#include <stdlib.h>
#include <assert.h> 

enum color{
	RED, 
	BLACK
}; 

struct rb_node{
	int data; 
	enum color color; 

	struct rb_node* left; 
	struct rb_node* right; 
	struct rb_node* parent; 
}; 

struct rb_tree{
	struct rb_node* p_root_node; 
	struct rb_node* p_sentinel_node; 
	int nr_elements; 
};

struct rb_tree* create_rb_tree(void); 
int destroy_rb_tree(struct rb_tree* p_rb_tree); 

static int destroy_rb_tree_by_node(struct rb_node* p_root_node); 
static struct rb_node* get_rb_node(int new_data); 

int main(){
	struct rb_tree* p_rb_tree = NULL; 

	p_rb_tree = create_rb_tree(); 


	destroy_rb_tree(p_rb_tree); 
	p_rb_tree = NULL; 
	return (EXIT_SUCCESS); 
}

struct rb_tree* create_rb_tree(void){
	struct rb_tree* p_rb_tree = NULL; 

	p_rb_tree = (struct rb_tree*)malloc(sizeof(struct rb_tree)); 
	assert(p_rb_tree); 

	p_rb_tree->p_sentinel_node = (struct rb_node*)malloc(sizeof(struct rb_node)); 
	assert(p_rb_tree->p_sentinel_node); 

	p_rb_tree->p_sentinel_node->data = -1; 
	p_rb_tree->p_sentinel_node->color = BLACK; 
	p_rb_tree->p_sentinel_node->left = NULL; 
	p_rb_tree->p_sentinel_node->right = NULL; 
	p_rb_tree->p_sentinel_node->parent = NULL; 

	p_rb_tree->p_root_node = NULL; 
	
	return (p_rb_tree); 
}

int destroy_rb_tree(struct rb_tree* p_rb_tree){
	destroy_rb_tree_by_node(p_rb_tree->p_root_node); 
	free(p_root_node->p_sentinel_node); 
	free(p_rb_tree); 
	return (SUCCESS); 
}

static void destroy_rb_tree_by_node(struct rb_node* p_root_node){
	if(p_root_node != NULL){
		destroy_rb_tree_by_node(p_root_node->left); 
		destroy_rb_tree_by_node(p_root_node->right); 
		free(p_root_node); 
	}
}

static struct rb_node* get_rb_node(struct rb_tree* p_rb_tree, int new_data){
	struct rb_node* p_new_node = NULL; 

	p_new_node = (struct rb_node*)malloc(sizeof(struct rb_node)); 
	assert(p_new_node); 

	p_new_node->data = new_data; 
	p_new_node->color = RED;	/* Will be explained at the time of insertion */  
	p_new_node->left = p_rb_tree->p_sentinel_node; 
	p_new_node->right = p_rb_tree->p_sentinel_node; 
	p_new_node->parent = p_rb_tree->p_sentinel_node; 

	return (p_new_node); 
} 

void rb_insert(struct rb_tree* p_rb_tree, int new_data){
	struct rb_node* x = NULL; 
	struct rb_node* y = NULL; 
	struct rb_node* z = NULL; 

	z = get_rb_node(new_data); 
	x = p_rb_tree->p_root_node; 
	y = p_rb_tree->p_sentinel_node; 

	while(x != p_rb_tree->p_sentinel_node){
		y = x; 
		if(z->data < x->data)
			x = x->left; 
		else
			x = x->right; 
	}

	z->parent = y; 

	if(y == p_rb_tree->p_sentinel_node)
		p_rb_tree->p_root_node = z; 
	else if(z->key < y->key)
		y->left = z; 
	else
		y->right = z; 

	rb_insert_fixup(p_rb_tree, z); 
	p_rb_tree->nr_elements++; 
	return (SUCCESS); 
}

void rb_insert_fixup(struct rb_tree* p_tree, struct rb_node* z){
	struct rb_node* y = NULL; 

	while(z->parent->color == RED)
	{
		if(z->parent == z->parent->parent->left)
		{
			y = z->parent->parent->right; 
			if(y->color == RED)
			{
				z->parent->color = BLACK; 
				y->color = BLACK; 
				z->parent->parent->color = RED; 
				z = z->parent->parent; 
			}
			else
			{
				if(z == z->parent->right)
				{
					z = z->parent; 
					left_rotate(p_rb_tree, z); 
				}
				z->parent->color = BLACK; 
				z->parent->parent->color = RED; 
				right_rotate(p_rb_tree, z->parent->parent); 
			}
		}
		else
		{
			y = z->parent->parent->left; 
			if(y->color == RED)
			{
				z->parent->color = BLACK; 
				y->color = BLACK; 
				z->parent->parent->color = RED; 
				z = z->parent->parent; 
			}
			else
			{
				if(z == z->parent->left)
				{
					z = z->parent; 
					right_rotate(p_rb_tree, z); 
				}
				z->parent->color = BLACK; 
				z->parent->parent->color = RED; 
				left_rotate(p_rb_tree, z->parent->parent); 
			}
		}
	}
	p_rb_tree->p_root_node->color = BLACK; 
}
