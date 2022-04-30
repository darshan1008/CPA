#ifndef _LIST_H 
#define _LIST_H 

// Symbolic constants 
const int SUCCESS = 1; 

// Typedefs 
typedef int data_t; 
typedef int ret_t; 
typedef int len_t; 

// Node layout 
class node{
	friend class list; 
private: 
	data_t data; 
	node* prev; 
	node* next; 
	node(int new_data = 0); 
}; 

class list{
private: 
	node* p_head_node;

	// list auxillary routines 
	// replaces generic_insert()
	static void generic_insert(node* p_beg, node* p_mid, node* p_end); 
	// replaces generic_delete()
	static void generic_delete(node* p_delete_node); 
	// replaces search_node()
	node* search_node(data_t s_data) const; 
public: 
	// constructor -> create_list()
	list();
	// destructor -> destroy_list()  
	~list(); 
	// insert routines -> 
	// replaces insert_beg()
	ret_t insert_beg(data_t new_data); 
	// replaces insert_end()
	ret_t insert_end(data_t new_data); 
	// replaces insert_after()
	ret_t insert_after(data_t e_data, data_t new_data); 
	// replaces insert_before()
	ret_t insert_before(data_t e_data, data_t new_data); 

	// get & pop 
	// replaces get_beg()
	ret_t get_beg(data_t* p_beg_data); 
	// replaces get_end() 
	ret_t get_end(data_t* p_end_data); 
	// replaces pop_beg()
	ret_t pop_beg(data_t* p_beg_data); 
	// replaces pop_end() 
	ret_t pop_end(data_t* p_end_data); 

	// delete routine 
	// replaces delete_beg() 
	ret_t delete_beg(); 
	// replaces delete_end() 
	ret_t delete_end(); 
	// replaces delete_data() 
	ret_t delete_data(data_t d_data); 

	// Query 
	bool is_empty() const; 
	bool find(data_t f_data) const; 

	// Misc 
	// Exercise: overload cout 
	// replaces show_list()
	void show() const; 
	// replaces get_list_length()
	len_t get_length() const; 

	// interlist routines 
	// replaces concat_immutable()
	list* concat_immutable(list* other_lst); 
	// replaces concat_mutable() 
	ret_t concat_mutable(list* other_lst);
	// replaces merge_lists()
	list* merge_lists(list* other); 
	// replaces to_array()
	ret_t to_array(data_t** pp_array, size_t* p_size); 
	// replaces to_list()
	ret_t to_list(data_t* p_array, size_t size, list** pp_lst); 
}; 


#endif /* _LIST_H */ 