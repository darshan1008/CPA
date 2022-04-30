typedef int key_t; 

typedef enum {RED = 0, BLACK} color_t; 

struct chain_rb_node{
	key_t key; 
	color_t color; 
	struct chain_rb_node* left; 
	struct chain_rb_node* right; 
	struct chain_rb_node* parent; 
}; 

struct chain_rb_tree{ 
	struct chain_rb_node* p_root_node; 
	size_t nr_elements; 
}; 

typedef int bucket_t; 

struct bucket_rb_node{
	bucket_t bucket; 
	struct chain_rb_tree* p_chain_tree; 
	color_t color; 
	struct bucket_rb_node* left; 
	struct bucket_rb_node* right; 
	struct bucket_rb_node* parent; 
}; 

struct bucket_rb_tree{
	struct bucket_rb_node* p_root_node; 
	size_t bucket_size; 	
}; 

typedef struct bucket_rb_tree hash_t; 

hash_t* create_hash(size_t bucket_size){
	struct bucket_rb_tree* p_bucket; 
	int i; 
	p_bucket = xcalloc(1, sizeof(struct bucket_rb_tree)); 
	for(i = 0; i < bucket_size; ++i){
		bucket_rb_insert(p_bucket, i); 
	}
	return (p_bucket); 
}

struct bucket_rb_node* get_bucket_rb_node(key_t new_key){
	struct bucket_rb_node* p_bucket_node; 

	p_bucket_node = xcalloc(1, sizeof(struct rb_bucket_node)); 
	p_bucket_node->key = new_key; 
	p_bucket_node->p_chain_tree = chain_create_rb_tree(); 
	p_bucket_node->color = RED;
}

