#ifndef _GRAPH_H 
#define _GRAPH_H 

#include <stdio.h> 
#include <stdlib.h> 

/* Symbolic constants */ 
#define SUCCESS 1 

#define TRUE 1 
#define FALSE 0 

#define HLIST_DATA_NOT_FOUND 2 
#define VLIST_DATA_NOT_FOUND HLIST_DATA_NOT_FOUND

#define G_VERTEX_EXISTS 	3 
#define G_EDGE_EXISTS 		4
#define G_INVALID_VERTEX 	5 
#define G_INVALID_EDGE 		6

 /* typedefs */
typedef struct graph graph_t; 
typedef struct hnode hnode_t; 
typedef hnode_t hlist_t;
typedef struct vnode vnode_t; 
typedef vnode_t vlist_t;  
typedef struct graph graph_t; 
typedef int ret_t; 
typedef int vertex_t; 

/* Internal layout  
 
 /* A node in horizontal list */ 
struct hnode{
	vertex_t v; 
	struct hnode *prev; 
	struct hnode *next; 
}; 

/* A node in vertical list */ 
struct vnode{
	vertex_t v; 
	hlist_t *ph_list; 

	struct vnode *prev; 
	struct vnode *next; 
}; 

/* A graph data structure */ 
struct graph{
	vlist_t *pv_list; 
	int nr_vertices; 
	int nr_edges; 
}; 

/* Part I : Graph management */ 

/* Graph interface routines */
graph_t *create_graph(void); 
ret_t add_vertex(graph_t *g, vertex_t v); 
ret_t remove_vertex(graph_t *g, vertex_t v); 
ret_t add_edge(graph_t *g, vertex_t v_start, vertex_t v_end); 
ret_t remove_edge(graph_t *g, vertex_t v_start, vertex_t v_end); 
void print_graph(graph_t *g, const char *msg); 
int get_nr_vertices(graph_t *g); 
int get_nr_edges(graph_t *g); 
ret_t destroy_graph(graph_t **pp_g); 

/* Graph - Auxillary routines - Part 1 - Vertical List Management */ 

vlist_t *create_list_v(void); 
ret_t insert_end_v(vlist_t *pv_list, vertex_t v_new); 
ret_t remove_vertex_v(vlist_t *pv_list, vertex_t r_vertex); 
ret_t destroy_list_v(vlist_t **pp_vlist); 

/* Vertical List - Auxillary Routines */ 
void generic_insert_v(vnode_t *p_beg, vnode_t *p_mid, vnode_t *p_end); 
void generic_delete_v(vnode_t *pv_node); 
vnode_t *search_node_v(vlist_t *pv_list, vertex_t v_search); 
vnode_t *get_node_v(vertex_t v_new); 

/* Graph - Auxillary routines - Part 2 - Horizontal List Management */ 
hlist_t *create_list_h(void); 
ret_t insert_end_h(hlist_t *ph_list, vertex_t v_new); 
ret_t remove_vertex_h(hlist_t *ph_list, vertex_t r_vertex); 
ret_t destroy_list_h(hlist_t **pp_hlist);

/* Horizontal List - Auxillary Routines */ 
void generic_insert_h(hnode_t *p_beg, hnode_t *p_mid, hnode_t *p_end); 
void generic_delete_h(hnode_t *ph_node); 
hnode_t *search_node_h(hlist_t *ph_list, vertex_t v_search); 
hnode_t *get_node_h(vertex_t v_new); 

/* Graph - Auxillary routine - Part - Misc. */ 
void *xcalloc(size_t nr_items, size_t size_per_item); 

#endif /* _GRAPH_H */ 