#include <stdio.h> 
#include <stdlib.h>

typedef int vertex_t; 
typedef int ret_t; 

typedef double weight_t; 

typedef enum {
	WHITE = 0, 
	GRAY, 
	BLACK 
}color_t;

typedef struct hnode{
	vnode_t *pv_node; 
	weight_t w;

	struct hnode *prev; 
	struct hnode *next;  
};  

