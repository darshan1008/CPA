#include <stdio.h> 
#include <stdlib.h> 
#include <assert.h>
#include "list.h"

int main(){
	list_t* p_list = NULL; 
	data_t data;
	data_t beg_data, end_data; 
	ret_t ret; 

	p_list = create_list(); 
	assert(p_list); 

	assert(is_list_empty(p_list) == TRUE); 
	assert(get_beg(p_list, &data) == LIST_EMPTY); 
	assert(get_end(p_list, &data) == LIST_EMPTY); 
	assert(pop_beg(p_list, &data) == LIST_EMPTY); 
	assert(pop_end(p_list, &data) == LIST_EMPTY); 
	assert(delete_beg(p_list) == LIST_EMPTY);
	assert(delete_end(p_list) == LIST_EMPTY);  
	assert(get_list_length(p_list) == 0); 

	for(data = 0; data < 5; ++data){
		ret = insert_beg(p_list, data); 
		assert(ret == SUCCESS); 
	}

	show_list(p_list); 

	for(data = 5; data < 10; ++data){
		ret = insert_end(p_list, data); 
		assert(ret);
	}

	show_list(p_list); 

	ret = insert_after(p_list, -100, 100); 
	assert(ret == LIST_DATA_NOT_FOUND); 

	ret = insert_after(p_list, 0, 100);
	assert(ret == SUCCESS);

	show_list(p_list); 

	ret = insert_before(p_list, 300, 200); 
	assert(ret == LIST_DATA_NOT_FOUND); 

	ret = insert_before(p_list, 0, 200); 
	assert(ret == SUCCESS); 

	show_list(p_list); 

	ret = get_beg(p_list, &beg_data); 
	assert(ret == SUCCESS); 
	printf("Current Beginning data = %d\n", beg_data); 

	ret = get_end(p_list, &end_data); 
	assert(ret == SUCCESS); 
	printf("Current End Data = %d\n", end_data); 

	ret = pop_beg(p_list, &beg_data); 
	assert(ret == SUCCESS); 
	show_list(p_list); 

	ret = pop_end(p_list, &end_data); 
	assert(ret == SUCCESS); 
	show_list(p_list); 

	ret = delete_beg(p_list); 
	assert(ret == SUCCESS); 
	show_list(p_list); 

	ret = delete_end(p_list); 
	assert(ret == SUCCESS); 
	show_list(p_list); 

	ret = delete_data(p_list, -5); 
	assert(ret == LIST_DATA_NOT_FOUND); 

	ret = delete_data(p_list, 0); 
	assert(ret == SUCCESS); 
	show_list(p_list); 

	assert(is_list_empty(p_list) == FALSE); 

	printf("Current Length of the list = %d\n", get_list_length(p_list)); 

	ret = destroy_list(&p_list); 
	assert(ret == SUCCESS && p_list == NULL); 

	list_t* p_list1 = NULL; 
	list_t* p_list2 = NULL; 
	list_t* p_cat_list = NULL; 
	list_t* p_merged_list = NULL; 

	/* populate p_list1 with sorted data */ 
	/* populate p_list2 with sorted data */ 
	/* apply immutable concat on p_list1 & p_list2 
		get result in p_cat_list and show all three lists */ 
	/* apply merge_lists on p_list1 & p_list2 and get 
		result in p_merged_list & show all three */ 
	/* apply concat_mutable on p_list1 and p_list2 and 
		get result in p_list1 */ 
	/* to_array on p_list1 and get result in p_array & N 
		print p_array */
	/* create a new array and apply to_list on it and get result int 
		p_list_from_array & show list */ 
	/* destroy p_list1, p_cat_list & p_merge_list */ 

	return (EXIT_SUCCESS); 
}