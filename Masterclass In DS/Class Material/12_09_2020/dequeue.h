#ifndef _DEQUEUE_H 
#define _DEQUEUE_H

typedef list_t dequeue_t; 

#define DEQUEUE_EMPTY LIST_EMPTY

dequeue_t* create_dequeue(); 
ret_t enqueue_front(dequeue_t* p_dequeue, data_t new_data); 
ret_t peek_front(dequeue_t* p_dequeue, data_t* p_front_peek_data); 
ret_t dequeue_front(dequeue_t* p_dequeue, data_t* p_front_dequeue_data); 

/* replace front by rear and repeat */ 
ret_t destroy_dequeue(dequeue_t** pp_dequeue);  

#endif 