#include <stdio.h> 
#include <stdlib.h>
#include "graph.h"

/* Interface routines prototypes */ 

/* Graph management routines */ 
graph_t* create_graph(void){
	graph_t* g = (graph_t*)xcalloc(1, sizeof(graph_t)); 
	g->pv_list = v_create_list(); 
	return (g); 
}

ret_t add_vertex(graph_t* g, vertex_t v){
	vnode_t* pv_node = NULL; 

	pv_node = v_search_node(g->pv_list, v); 
	if(pv_node != NULL)
		return (G_VERTEX_EXISTS);

	v_insert_end(g->pv_list, v); 
	g->nr_vertices++; 
	return (SUCCESS); 
}

ret_t add_edge(graph_t* g, vertex_t v_start, vertex_t v_end){
	vnode_t* pv_start = NULL; 
	vnode_t* pv_end = NULL; 
	hnode_t* ph_start_in_end = NULL; 
	hnode_t* ph_end_in_start = NULL; 

	if(v_start == v_end)
		return (G_SELF_EDGE); 

	pv_start = v_search_node(g->pv_list, v_start); 
	pv_end = v_search_node(g->pv_list, v_end); 

	if(pv_start == NULL || pv_end == NULL)
		return (G_INVALID_VERTEX); 

	ph_start_in_end = h_search_node(pv_end->ph_list, v_start); 
	ph_end_in_start = h_search_node(pv_start->ph_list, v_end); 
	if(ph_start_in_end != NULL && ph_end_in_start != NULL)
		return (G_EDGE_EXISTS); 

	h_insert_end(pv_start->ph_list, v_end); 
	h_insert_end(pv_end->ph_list, v_start); 
	g->nr_edges++; 
	return (SUCCESS); 
}

ret_t remove_vertex(graph_t* g, vertex_t v){
	vnode_t* pv_node = NULL; 
	vnode_t* pv_h_in_v = NULL; 
	hnode_t* ph_v_in_h = NULL; 
	hnode_t* ph_run = NULL; 
	hnode_t* ph_run_next = NULL;

	pv_node = v_search_node(g->pv_list, v); 
	if(pv_node == NULL)
		return (G_INVALID_VERTEX); 
		
	for(ph_run = pv_node->ph_list->next; ph_run != pv_node->ph_list; ph_run = ph_run_next){
		ph_run_next = ph_run->next; 
		pv_h_in_v = v_search_node(g->pv_list, ph_run->v); 
		ph_v_in_h = h_search_node(pv_h_in_v->ph_list, v); 
		h_generic_delete(ph_v_in_h); 
		free(ph_run); 
		g->nr_edges--; 
	}

	free(pv_node->ph_list); 
	v_generic_delete(pv_node); 
	g->nr_vertices--; 
	return (SUCCESS); 
}

ret_t remove_edge(graph_t* g, vertex_t v_start, vertex_t v_end){
	vnode_t* pv_start = NULL; 
	vnode_t* pv_end = NULL; 
	hnode_t* ph_start_in_end = NULL; 
	hnode_t* ph_end_in_start = NULL; 

	pv_start = v_search_node(g->pv_list, v_start); 
	pv_end = v_search_node(g->pv_list, v_end); 

	if(pv_start == NULL || pv_end == NULL)
		return (G_INVALID_VERTEX); 

	ph_start_in_end = h_search_node(pv_end->ph_list, v_start); 
	ph_end_in_start = h_search_node(pv_start->ph_list, v_end); 

	if(ph_start_in_end == NULL && ph_end_in_start == NULL)
		return (G_INVALID_EDGE); 

	h_generic_delete(ph_start_in_end); 
	h_generic_delete(ph_end_in_start); 

	g->nr_edges--; 
	return (SUCCESS); 
}

void print_graph(graph_t* g){
	vnode_t* pv_run = NULL; 
	hnode_t* ph_run = NULL; 

	for(pv_run = g->pv_list->next; pv_run != g->pv_list; pv_run = pv_run->next){
		printf("[%d]\t\t-->\t\t", pv_run->v); 
		for(ph_run = pv_run->ph_list->next; ph_run != pv_run->ph_list; ph_run = ph_run->next){
			printf("[%d]<->", ph_run->v); 
		}
		puts("[END]"); 
	}
}

size_t get_nr_vertices(graph_t* g){
	return (g->nr_vertices); 
}

size_t get_nr_edges(graph_t* g){
	return (g->nr_edges); 
}

ret_t destroy_graph(graph_t** pp_g){
	graph_t* g = NULL; 
	vnode_t* pv_run = NULL; 
	vnode_t* pv_run_next = NULL; 
	hnode_t* ph_run = NULL; 
	hnode_t* ph_run_next = NULL; 

	g = *pp_g; 

	for(pv_run = g->pv_list->next; pv_run != g->pv_list; pv_run = pv_run_next){
		pv_run_next = pv_run->next; 
		for(ph_run = pv_run->ph_list->next; ph_run != pv_run->ph_list; ph_run = ph_run_next){
			ph_run_next = ph_run->next; 
			free(ph_run); 
		}
		free(pv_run->ph_list); 
		free(pv_run); 
	}

	free(g->pv_list); 
	free(g); 
	*pp_g = NULL;
	return (SUCCESS);  
}

/* Horizontal List Management */ 

hlist_t* h_create_list(){
	hlist_t* ph_list = h_get_node(-1); 
	ph_list->prev = ph_list; 
	ph_list->next = ph_list; 
	return (ph_list); 
}

ret_t h_insert_end(hlist_t* ph_list, vertex_t v){
	h_generic_insert(ph_list->prev, h_get_node(v), ph_list); 
	return (SUCCESS); 
}

hnode_t* h_search_node(hlist_t* ph_list, vertex_t v){
	hnode_t* ph_run = NULL; 

	for(ph_run = ph_list->next; ph_run != ph_list; ph_run = ph_run->next)
		if(ph_run->v == v)
			return (ph_run); 
	
	return (NULL);
}

void h_generic_insert(hnode_t* p_beg, hnode_t* p_mid, hnode_t* p_end){
	p_mid->next = p_end; 
	p_mid->prev = p_beg; 
	p_beg->next = p_mid; 
	p_end->prev = p_mid; 
}

void h_generic_delete(hnode_t* p_delete_node){
	p_delete_node->prev->next = p_delete_node->next; 
	p_delete_node->next->prev = p_delete_node->prev; 
	free(p_delete_node); 
	p_delete_node = NULL; 
}

hnode_t* h_get_node(vertex_t v){
	hnode_t* ph_new_node = NULL; 
	ph_new_node = (hnode_t*)xcalloc(1, sizeof(hnode_t)); 
	ph_new_node->v = v; 
	return (ph_new_node); 
}

/* Vertical List Management */ 
vlist_t* v_create_list(){
	vlist_t* pv_list = (vlist_t*)xcalloc(1, sizeof(vnode_t)); 
	pv_list->v = -1; 
	pv_list->prev = pv_list; 
	pv_list->next = pv_list; 
	return (pv_list); 
}

ret_t v_insert_end(vlist_t* pv_list, vertex_t v){
	v_generic_insert(pv_list->prev, v_get_node(v), pv_list);
	return (SUCCESS);  
}

vnode_t* v_search_node(vlist_t* pv_list, vertex_t v){
	vnode_t* pv_run = NULL; 

	for(pv_run = pv_list->next; pv_run != pv_list; pv_run = pv_run->next)
		if(pv_run->v == v)
			return (pv_run); 

	return (NULL); 
}

void v_generic_insert(vnode_t* p_beg, vnode_t* p_mid, vnode_t* p_end){
	p_mid->next = p_end; 
	p_mid->prev = p_beg; 
	p_beg->next = p_mid; 
	p_end->prev = p_mid; 
}

void v_generic_delete(vnode_t* p_delete_node){
	p_delete_node->prev->next = p_delete_node->next; 
	p_delete_node->next->prev = p_delete_node->prev; 
	free(p_delete_node); 
	p_delete_node = NULL; 
}

vnode_t* v_get_node(vertex_t v){
	vnode_t* pv_new_node = NULL; 

	pv_new_node = (vnode_t*)xcalloc(1, sizeof(vnode_t)); 
	pv_new_node->v = v; 
	pv_new_node->ph_list = h_create_list(); 

	return (pv_new_node); 
}

/* Auxillary Routines */ 
void *xcalloc(size_t nr_elements, size_t size_per_element){
	void* p = NULL; 

	p = calloc(nr_elements, size_per_element); 
	if(p == NULL){
		fprintf(stderr, "fatal:calloc:out of virtual memory\n"); 
		exit(EXIT_FAILURE); 
	}

	return (p); 
}