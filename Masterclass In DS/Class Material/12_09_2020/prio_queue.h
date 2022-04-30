#ifndef _PRIO_QUEUE_H 
#define _PRIO_QUEUE_H

typedef list_t prio_queue_t; 

prio_queue_t* create_prio_queue(); 
ret_t enqueue_prio_queue(prio_queue_t* p_prio_queue, data_t new_data); 
ret_t dequeue_prio_max(prio_queue_t* p_prio_queue, data_t* p_max_data); 
ret_t dequeue_prio_min(prio_queue_t* p_prio_queue, data_t* p_min_data); 
ret_t peek_prio_max(prio_queue_t* p_prio_queue, data_t* p_min_data);
ret_t peek_prio_min(prio_queue_t* p_prio_queue, data_t* p_min_data);
ret_t destroy_prio_queue(prio_queue_t** pp_prio_queue)

#endif 