#include <iostream>
#include <cstdlib>
#include <cassert>

#include "list.h" 
#include "list_exceptions.h"

int main(){
	list* p_list = new list; 
	data_t data; 
	ret_t ret; 

	for(data = 0; data < 5; ++data){
		ret = p_list->insert_beg(data); 
		assert(ret); 
	}

	p_list->show(); 

	for(data = 5; data < 10; ++data){
		ret = p_list->insert_end(data); 
		assert(ret); 
	}

	p_list->show(); 

	try{
		p_list->insert_after(-5, 100); 
	}catch(data_not_found& ref){
		std::cout << ref.what() << std::endl; 
	}

	ret = p_list->insert_after(0, 100); 
	assert(ret); 
	p_list->show(); 

	try{
		p_list->insert_before(-32, 100); 
	}catch(data_not_found& ref){
		std::cout << ref.what() << std::endl; 
	}

	ret = p_list->insert_before(0, 200); 
	assert(ret); 
	p_list->show(); 

	delete p_list; 
	p_list = 0; 

	return EXIT_SUCCESS;
}
