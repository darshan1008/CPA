#ifndef _STACK_H 
#define _STACK_H

#include "list.h"

#define STACK_EMPTY LIST_EMPTY 

typedef list_t stack_t; 

stack_t* create_stack();  							/* return create_list();  */ 
ret_t push(stack_t* p_stack, data_t new_data); 		/* return insert_end(p_stack, new_data); */
ret_t top(stack_t* p_stack, data_t* p_top_data); 	/* return get_end(p_stack, p_top_data); */
ret_t pop(stack_t* p_stack, data_t* p_pop_data); 	/* return pop_end(p_stack, p_pop_data); */
ret_t destroy_stack(stack_t** pp_stack); 			/*  return destroy_list(pp_stack); */ 




#endif /* _STACK_H */ 