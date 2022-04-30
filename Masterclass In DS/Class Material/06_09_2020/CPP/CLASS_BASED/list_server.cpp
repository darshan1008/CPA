#include <iostream>
#include "list.h"
#include "list_exceptions.h"

// list exceptions 
data_not_found::data_not_found() : std::runtime_error("Invalid existing data"){

}

list_empty::list_empty() : std::runtime_error("List is empty"){

}

// node constructor 
node::node(int new_data) : data(new_data), prev(0), next(0){

}

// list auxillary routines
// replaces generic_insert()
void list::generic_insert(node* p_beg, node* p_mid, node* p_end){
	p_mid->next = p_end; 
	p_mid->prev = p_beg; 
	p_beg->next = p_mid; 
	p_end->prev = p_mid; 
}

// replaces generic_delete()
void list::generic_delete(node* p_delete_node){
	p_delete_node->prev->next = p_delete_node->next; 
	p_delete_node->next->prev = p_delete_node->prev; 
	delete p_delete_node; 
} 

// replaces search_node()
node* list::search_node(data_t s_data) const {
	for(node* p_run = p_head_node->next; p_run != p_head_node; p_run = p_run->next)
		if(p_run->data == s_data)
			return (p_run); 
	return (0); 	
} 

// constructor -> create_list()
list::list(){
	p_head_node = new node; 
	p_head_node->prev = p_head_node; 
	p_head_node->next = p_head_node; 
}
// destructor -> destroy_list()  
list::~list(){
	node* p_run = 0; 
	node* p_run_next = 0; 
	for(p_run = p_head_node->next; p_run != p_head_node; p_run = p_run_next){
		p_run_next = p_run->next; 
		delete p_run; 
	}
	delete p_head_node; 
	p_head_node = 0; 
}
// insert routines -> 
// replaces insert_beg()
ret_t list::insert_beg(data_t new_data){
	generic_insert(p_head_node, new node(new_data), p_head_node->next);
	return SUCCESS; 
}
// replaces insert_end()
ret_t list::insert_end(data_t new_data){
	generic_insert(p_head_node->prev, new node(new_data), p_head_node); 
	return SUCCESS; 
}
// replaces insert_after()
ret_t list::insert_after(data_t e_data, data_t new_data){
	node* e_node = this->search_node(e_data); 
	if(e_node == 0)
		throw data_not_found(); // IMP difference 
	generic_insert(e_node, new node(new_data), e_node->next); 
	return SUCCESS; 
}

// replaces insert_before()
ret_t list::insert_before(data_t e_data, data_t new_data){
	node* e_node = search_node(e_data); 
	if(e_node == 0)
		throw data_not_found(); 
	generic_insert(e_node->prev, new node(new_data), e_node); 
	return SUCCESS; 
}

// get & pop 
// replaces get_beg()
ret_t list::get_beg(data_t* p_beg_data){
	if(is_empty() == true)
		throw list_empty(); 
	*p_beg_data = p_head_node->next->data; 
	return SUCCESS; 
}
// replaces get_end() 
ret_t list::get_end(data_t* p_end_data){
	if(is_empty())
		throw list_empty(); 
	*p_end_data = p_head_node->prev->data; 
	return SUCCESS; 	
}
// replaces pop_beg()
ret_t list::pop_beg(data_t* p_beg_data){
	if(is_empty())
		throw list_empty(); 
	*p_beg_data = p_head_node->next->data; 
	generic_delete(p_head_node->next); 
	return SUCCESS; 
}
// replaces pop_end() 
ret_t list::pop_end(data_t* p_end_data){
	if(is_empty())
		throw list_empty(); 
	*p_end_data = p_head_node->prev->data; 
	generic_delete(p_head_node->prev); 
	return SUCCESS; 
}

// delete routine 
// replaces delete_beg() 
ret_t list::delete_beg(){
	if(is_empty())
		throw list_empty(); 
	generic_delete(p_head_node->next); 
	return SUCCESS; 
}

// replaces delete_end() 
ret_t list::delete_end(){
	if(is_empty())
		throw list_empty(); 
	generic_delete(p_head_node->prev); 
	return SUCCESS; 
}

// replaces delete_data() 
ret_t list::delete_data(data_t d_data){
	node* p_ext_node = search_node(d_data); 
	if(p_ext_node == 0)
		throw data_not_found(); 
	generic_delete(p_ext_node); 
	return SUCCESS; 
}

// Query 
//	replaces -> is_list_empty()
bool list::is_empty() const{
	return p_head_node->prev == p_head_node && p_head_node->next == p_head_node; 
}

// replaces find()
bool list::find(data_t f_data) const{
	return (search_node(f_data) != 0); 	
}

// Misc 
// Exercise: overload cout 
// replaces show_list()
void list::show() const{
	std::cout << "[START]<->"; 
	for(node* p_run = p_head_node->next; p_run != p_head_node; 
		p_run = p_run->next)
		std::cout << "[" << p_run->data << "]<->"; 
	std::cout << "[END]" << std::endl; 
}

// replaces get_list_length()
len_t list::get_length() const{
	len_t len = 0; 
	for(node* p_run = p_head_node->next; 
		p_run != p_head_node; 
		p_run = p_run->next)
		++len; 
	return len; 	
}

// interlist routines 
// replaces concat_immutable()
list* list::concat_immutable(list* other_lst){
	list* p_cat_list = new list; 
	for(node* p_run = this->p_head_node->next; 
		p_run != this->p_head_node; 
		p_run = p_run->next) 
		p_cat_list->insert_end(p_run->data); 
	for(node* p_run = other_lst->p_head_node->next; 
		p_run != other_lst->p_head_node; 
		p_run = p_run->next)
		p_cat_list->insert_end(p_run->data); 
	return p_cat_list; 
}

// replaces concat_mutable() 
ret_t list::concat_mutable(list* other_lst){
	if(other_lst->is_empty())
		return SUCCESS; 
	this->p_head_node->prev->next = other_lst->p_head_node->next; 
	other_lst->p_head_node->next->prev = this->p_head_node->prev; 
	delete other_lst->p_head_node; 
	return SUCCESS; 	
}

// replaces merge_lists()
list* list::merge_lists(list* other){
	node* p_run1 = this->p_head_node->next; 
	node* p_run2 = other->p_head_node->next; 
	list* p_merged_list = new list; 

	while(true){

		if(this->is_empty()){
			while(p_run2 != other->p_head_node){
				p_merged_list->insert_end(p_run2->data); 
				p_run2 = p_run2->next; 
			}
			break; 
		}

		if(other->is_empty()){
			while(p_run1 != this->p_head_node){
				p_merged_list->insert_end(p_run1->data); 
				p_run1 = p_run1->next; 
			}
			break; 
		}

		if(p_run1->data <= p_run2->data){
			p_merged_list->insert_end(p_run1->data); 
			p_run1 = p_run1->next; 
		}else{
			p_merged_list->insert_end(p_run2->data); 
			p_run2 = p_run2->next; 
		}
	}
	return p_merged_list; 
}

// replaces to_array()
ret_t list::to_array(data_t** pp_array, size_t* p_size){
	
}
// replaces to_list()
ret_t list::to_list(data_t* p_array, size_t size, list** pp_lst){
	
} 



