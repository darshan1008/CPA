#ifndef _QUEUE_H 
#define _QUEUE_H

#define QUEUE_EMPTY LIST_EMPTY

typedef list_t queue_t; 

queue_t* create_queue(); 
ret_t enqueue(queue_t* p_queue, data_t new_data); 
ret_t dequeue(queue_t* p_queue, data_t* p_dequeue_data); 
ret_t peek(queue_t* p_queue, data_t* p_peeked_data); 
ret_t destroy_queue(queue_t** pp_queue); 

#endif /* _QUEUE_H */ 