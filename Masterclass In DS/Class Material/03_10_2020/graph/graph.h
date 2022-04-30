#ifndef _GRAPH_H 
#define _GRAPH_H 

#define SUCCESS 		 	1 
#define TRUE 			 	1 
#define FALSE 				0
#define G_VERTEX_EXISTS  	2 
#define G_EDGE_EXISTS 		3
#define G_INVALID_VERTEX 	4 
#define G_INVALID_EDGE 		5
#define G_SELF_EDGE 		6 


/* Typedefs */ 
typedef struct hnode hnode_t;
typedef hnode_t hlist_t;  
typedef struct vnode vnode_t;
typedef vnode_t vlist_t;  
typedef struct graph graph_t; 
typedef enum color color_t; 

typedef int vertex_t; 
typedef int ret_t; 

/* Data Layout */  
struct hnode{
	vertex_t v; 
	struct hnode* prev; 
	struct hnode* next; 
}; 

struct vnode{
	vertex_t v; 
	hlist_t* ph_list; 

	struct vnode* prev; 
	struct vnode* next; 
}; 

struct graph{
	vlist_t *pv_list; 
	size_t nr_vertices; 
	size_t nr_edges; 
}; 

enum color{
	WHITE = 0, 
	GREY, 
	BLACK
};  

/* Interface routines prototypes */ 

/* Graph management routines */ 
graph_t* create_graph(void);
ret_t add_vertex(graph_t* g, vertex_t v); 
ret_t add_edge(graph_t* g, vertex_t v_start, vertex_t v_end); 
ret_t remove_vertex(graph_t* g, vertex_t v); 
ret_t remove_edge(graph_t* g, vertex_t v_start, vertex_t v_end); 
void print_graph(graph_t* g); 
size_t get_nr_vertices(graph_t* g); 
size_t get_nr_edges(graph_t* g); 
ret_t destroy_graph(graph_t** pp_g); 

/* Horizontal List Management */ 

hlist_t* h_create_list(); 
ret_t h_insert_end(hlist_t* ph_list, vertex_t v); 

hnode_t* h_search_node(hlist_t* ph_list, vertex_t v); 
void h_generic_insert(hnode_t* p_beg, hnode_t* p_mid, hnode_t* p_end); 
void h_generic_delete(hnode_t* p_delete_node); 
hnode_t* h_get_node(vertex_t v); 

/* Vertical List Management */ 
vlist_t* v_create_list(); 
ret_t v_insert_end(vlist_t* pv_list, vertex_t v); 

vnode_t* v_search_node(vlist_t* pv_list, vertex_t v); 
void v_generic_insert(vnode_t* p_beg, vnode_t* p_mid, vnode_t* p_end); 
void v_generic_delete(vnode_t* p_delete_node); 
vnode_t* v_get_node(vertex_t v); 

/* Auxillary Routines */ 
void *xcalloc(size_t nr_elements, size_t size_per_element); 

#endif /* _GRAPH_H */ 