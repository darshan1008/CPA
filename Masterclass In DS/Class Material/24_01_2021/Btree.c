#include <stdio.h>
#include <stdlib.h> 

#define SUCCESS 1 
#define TRUE 1 
#define FALSE 0 

typedef int key_t; 
typedef int bool; 

typedef struct btree_node btree_node_t; 
typedef struct btree btree_t; 

struct btree_node{
	key_t* ka; 	
	size_t kn; 
	struct btree_node** ca; 
	size_t cn;
	bool is_leaf; 
}; 

struct btree{
	btree_node_t* p_root; 
	size_t t; 	
	size_t nr_keys; 
};

btree_t* create_btree(size_t t); 
btree_node_t* get_btree_node(void); 
void btree_split_child(btree_node_t* x, int i, size_t t); 

int main(){

}

btree_t* create_btree(size_t t){
	btree_t* p_btree = NULL; 

	p_btree = (btree_t*)malloc(sizeof(btree_t)); 
	assert(p_btree); 

	p_btree->t = t; 
	p_btree->nr_keys = 0; 

	p_btree->p_root = get_btree_node(); 
	return (p_btree); 
}

btree_node_t* get_btree_node(void){
	btree_node_t* p_new_node = NULL; 

	p_new_node = (btree_node_t*)malloc(sizeof(btree_node_t)); 

	p_new_node->ka = NULL; 
	p_new_node->kn = 0; 
	
	p_new_node->ca = NULL; 
	p_new_node->cn = 0; 

	p_new_node->is_leaf = TRUE;  	

	return (p_new_node); 
}

void btree_split_child(btree_node_t* x, int i, size_t t){
	btree_node_t* z = NULL; 
	btree_node_t* y = NULL; 
	int j; 

	z = get_btree_node(); 
	y = x->ca[i]; 
	
	z->is_leaf = y->is_leaf; 
	z->kn = t - 1; 
	z->ka = (key_t*)calloc(z->kn, sizeof(key_t)); 
	 

	for(j = 0; j < t-1; ++j)
		z->ka[j] = y->ka[j+t]; 

	if(!y->is_leaf)
	{
		z->cn = t; 
		z->ca = (btree_node_t**)calloc(z->cn, sizeof(btree_node_t*));
		for(j = 0; j < t; ++j)
			z->ca[j] = y->ca[j+t]; 
	}

	y->kn = t-1; 

	/* add one child node to x */ 
	x->cn = x->cn + 1; 
	x->ca = realloc(x->ca, sizeof(btree_node_t*) * x->cn); 
	x->ca[x->cn-1] = NULL; 

	/* add one key slot to x */ 
	x->kn = x->kn+1;
	x->ka = (key_t*)realloc(x->ka, sizeof(key_t)*x->kn);

	for(j = x->cn-1; j >= i+1; --j)
		x->ca[j+1] = y->ca[j+t]; 
	x->ca[i+1] = z; 

	for(j = x->kn-1; j >= i; --j)
		x->ka[j+1] = x->ka[j]; 	
}

/* 
Precondition: x is a node which is not full and we 
have to add key k into it

if x is a leaf node then algorithm is much simplified. 
You simply have to scan through the node x, key array 
and find appropriate position for k in sorted order 
and insert k at that position. 

But if x is not a leaf node then, in x we have to find 
two consecutive keys such that x.ki <= k < x.ki+1 

And therefore, we are going to insert k into x.ci 
But if x.ci is full at the time of insertion  
then we split it first and depending on whether k is 
less than equal to or greather the median key we choose and 
appriate leaf node for inserting k 

*/ 
void btree_insert_nonfull(btree_node_t* x, key_t k, size_t t){
	int i; 

	i = x->kn-1; 	// x.n in pseudo code == x->kn-1 in real code 

	if(x->is_leaf == TRUE){
	// Find appropriate position for key k. 
		// resize the key array by 1 
		
		x->ka = (key_t*)realloc(x->ka, (x->kn+1)*sizeof(key_t)); 
		while(i >= 0 && k < x->ka[i]){
			x->ka[i+1] = x->ka[i]; 
			i = i - 1; 
		}

		x->ka[i+1] = k; 	
		x->kn = x->kn + 1; 

	}else{
		
		while(i >= 0 && k <= x->ka[i])
			i = i - 1; 
		
		i = i + 1; 

		if(x->ca[i]->kn == 2*t - 1){
			btree_split_child(x, i); 
			
			if(k > x->ka[i])
				i = i + 1; 
		}

		btree_insert_nonfull(x->ca[i], k); 
	}
}

int btree_insert(btree_t* p_btree, key_t key){

	btree_node_t* r = NULL; 
	btree_node_t* s = NULL; 

	r = p_btree->p_root; 
	if(r->kn == 2*p_btree->t - 1){
		s = get_btree_node(); 
		p_btree->p_root = s; 
		s->is_leaf = FALSE; 
		s->kn = 0; 

		s->cn = s->cn + 1; 
		s->ca = (btree_node_t**)realloc(s->ca, s->cn * sizeof(btree_node_t*)); 
		s->ca[0] = r; 
		btree_split_child(s, 0); 
		btree_insert_nonfull(s, k); 
	}else{
		btree_insert_nonfull(r, k); 
	}

	return SUCCESS; 
}
