struct bst_node; 
struct bst; 
typedef struct bst_node bst_node_t; 
typedef struct bst bst_t; 

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

bst_t* create_bst(){
	bst_t* p_bst = (bst_t*)xcalloc(1, sizeof(bst_t)); 
	p_bst->p_root_node = get_bst_node(-1); 
	p_bst->nr_elements = 0; 
	return (p_bst); 
}

bst_node_t* get_bst_node(data_t new_data){
	bst_node_t* p_bst_node = (bst_node_t*)xcalloc(1, sizeof(bst_node_t)); 
	p_bst_node->data = new_data; 
	return (p_bst_node); 
}
