#include <stdio.h> 
#include <stdlib.h> 
#include <assert.h>
#include "graph.h"

/* Graph - Interface routines */ 

graph_t *create_graph(void){
	graph_t *g = (graph_t*)xcalloc(1, sizeof(graph_t)); 
	g->pv_list = (vnode_t*)xcalloc(1, sizeof(vnode_t)); 
	
	g->pv_list->v = -1; 
	
	g->pv_list->ph_list = NULL; 
	g->pv_list->prev = g->pv_list; 
	g->pv_list->next = g->pv_list; 
	
	g->nr_vertices = 0; 
	g->nr_edges = 0; 
	
	return (g); 
}

ret_t add_vertex(graph_t *g, vertex_t v){
	vnode_t *pv_node = search_node_v(g->pv_list, v); 
	if(pv_node != NULL)
		return (G_VERTEX_EXISTS); 
	insert_end_v(g->pv_list, v); 
	g->nr_vertices++; 
	return (SUCCESS); 
}

ret_t remove_vertex(graph_t *g, vertex_t v){
	vnode_t *pv_node = NULL; 
	vnode_t *pv_node_of_hv = NULL; 
	hnode_t *ph_run = NULL; 
	hnode_t *ph_run_next = NULL; 
	ret_t ret; 
	
	pv_node = search_node_v(g->pv_list, v); 
	if(pv_node == NULL)
		return (G_INVALID_VERTEX); 

	ph_run = pv_node->ph_list->next; 
	while(ph_run != pv_node->ph_list){
		ph_run_next = ph_run->next; 
		pv_node_of_hv = search_node_v(g->pv_list, ph_run->v);
		ret = remove_vertex_h(pv_node_of_hv->ph_list, v); 
		assert(ret == SUCCESS); 
		free(ph_run); 
		g->nr_edges--; 
		ph_run = ph_run_next; 
	}

	free(pv_node->ph_list); 
	generic_delete_v(pv_node); 
	g->nr_vertices--; 

	return (SUCCESS); 
}

ret_t add_edge(graph_t *g, vertex_t v_start, vertex_t v_end){
	vnode_t *pv_node_start = NULL; 
	vnode_t *pv_node_end = NULL; 
	hnode_t *ph_node = NULL; 

	pv_node_start = search_node_v(g->pv_list, v_start); 
	pv_node_end = search_node_v(g->pv_list, v_end); 
	if(pv_node_start == NULL || pv_node_end == NULL)
		return (G_INVALID_VERTEX); 

	ph_node = search_node_h(pv_node_start->ph_list, v_end); 
	if(ph_node != NULL)
		return (G_EDGE_EXISTS); 

	assert(insert_end_h(pv_node_start->ph_list, v_end) == SUCCESS); 
	assert(insert_end_h(pv_node_end->ph_list, v_start) == SUCCESS); 

	g->nr_edges++; 
	return (SUCCESS); 
}

ret_t remove_edge(graph_t *g, vertex_t v_start, vertex_t v_end){
	vnode_t *pv_start = NULL; 
	vnode_t *pv_end = NULL; 
	ret_t ret; 

	pv_start = search_node_v(g->pv_list, v_start); 
	pv_end = search_node_v(g->pv_list, v_end); 

	if(pv_start == NULL || pv_end == NULL)
		return (G_INVALID_VERTEX); 

	ret = remove_vertex_h(pv_start->ph_list, v_end); 
	if(ret == HLIST_DATA_NOT_FOUND)
		return (G_INVALID_EDGE); 

	ret = remove_vertex_h(pv_end->ph_list, v_start); 
	if(ret == HLIST_DATA_NOT_FOUND)
		return (G_INVALID_EDGE); 
	
	g->nr_edges--; 
	return (SUCCESS); 
}

void print_graph(graph_t *g, const char *msg){
	vnode_t *pv_node = NULL; 
	hnode_t *ph_node = NULL; 

	puts(msg); 

	for(pv_node = g->pv_list->next; pv_node != g->pv_list; pv_node = pv_node->next){
		printf("[%d]\t--->\t", pv_node->v); 
		for(ph_node = pv_node->ph_list->next; ph_node != pv_node->ph_list; ph_node = ph_node->next){
			printf("[%d]<->", ph_node->v); 
		}
		puts("[END]"); 
	}
}

int get_nr_vertices(graph_t *g){
	return (g->nr_vertices); 
}

int get_nr_edges(graph_t *g){
	return (g->nr_edges); 
}

ret_t destroy_graph(graph_t **pp_g){
	graph_t *g = NULL; 
	vnode_t *pv_node = NULL; 
	vnode_t *pv_node_next = NULL; 

	g = *pp_g; 

	for(pv_node = g->pv_list->next; pv_node != g->pv_list; pv_node = pv_node_next){
		pv_node_next = pv_node->next; 
		destroy_list_h(&pv_node->ph_list); 
		free(pv_node); 
	}

	free(g->pv_list); 
	free(g); 

	*pp_g = NULL; 

	return (SUCCESS); 
}

/* Graph - Auxillary routines - Part 1 - Vertical List Management */ 

vlist_t *create_list_v(void){
	vnode_t *pv_head_node = get_node_v(-1); 
	pv_head_node->prev = pv_head_node; 
	pv_head_node->next = pv_head_node; 
	return (pv_head_node); 
}

ret_t insert_end_v(vlist_t *pv_list, vertex_t v_new){
	generic_insert_v(pv_list->prev, get_node_v(v_new), pv_list);
	return (SUCCESS);  
}

ret_t remove_vertex_v(vlist_t *pv_list, vertex_t r_vertex){
	vnode_t *pv_node = search_node_v(pv_list, r_vertex); 
	if(pv_node == NULL)
		return (VLIST_DATA_NOT_FOUND);
	generic_delete_v(pv_node);
	return (SUCCESS);  
}

ret_t destroy_list_v(vlist_t **pp_vlist){
	vlist_t *pv_list = *pp_vlist; 
	vnode_t *pv_run = NULL; 
	vnode_t *pv_run_next = NULL; 

	for(pv_run = pv_list->next; pv_run != pv_list; pv_run = pv_run_next){
		pv_run_next = pv_run->next; 
		free(pv_run); 
	}

	free(pv_list); 
	*pp_vlist = NULL; 

	return (SUCCESS); 
}

/* Vertical List - Auxillary Routines */ 
void generic_insert_v(vnode_t *p_beg, vnode_t *p_mid, vnode_t *p_end){
	p_mid->next = p_end; 
	p_mid->prev = p_beg; 
	p_beg->next = p_mid; 
	p_end->prev = p_mid; 
}

void generic_delete_v(vnode_t *pv_node){
	pv_node->prev->next = pv_node->next; 
	pv_node->next->prev = pv_node->prev; 
	free(pv_node); 
}

vnode_t *search_node_v(vlist_t *pv_list, vertex_t v_search){
	vnode_t *pv_run = NULL; 
	for(pv_run = pv_list->next; pv_run != pv_list; pv_run = pv_run->next){
		if(pv_run->v == v_search)
			return (pv_run); 
	}

	return (NULL); 
}

vnode_t *get_node_v(vertex_t v_new){
	vnode_t *pv_new_node = (vnode_t*)xcalloc(1, sizeof(vnode_t)); 
	pv_new_node->v = v_new; 
	pv_new_node->ph_list = create_list_h(); 
	return (pv_new_node); 
}

/* Graph - Auxillary routines - Part 2 - Horizontal List Management */ 
hlist_t *create_list_h(void){
	hnode_t *ph_head_node = get_node_h(-1); 
	ph_head_node->prev = ph_head_node; 
	ph_head_node->next = ph_head_node; 
	return (ph_head_node); 
} 

ret_t insert_end_h(hlist_t *ph_list, vertex_t v_new){
	generic_insert_h(ph_list->prev, get_node_h(v_new), ph_list); 
	return (SUCCESS); 
}

ret_t remove_vertex_h(hlist_t *ph_list, vertex_t r_vertex){
	hnode_t *ph_node = search_node_h(ph_list, r_vertex); 
	if(ph_node == NULL)
		return (HLIST_DATA_NOT_FOUND);
	generic_delete_h(ph_node); 
	return (SUCCESS);  	
}

ret_t destroy_list_h(hlist_t **pp_hlist){
	hlist_t *ph_list = *pp_hlist; 
	hnode_t *ph_run = NULL; 
	hnode_t *ph_run_next = NULL; 

	for(ph_run = ph_list->next; ph_run != ph_list; ph_run = ph_run_next){
		ph_run_next = ph_run->next; 
		free(ph_run); 
	}

	free(ph_list); 
	*pp_hlist = NULL; 

	return (SUCCESS); 
}

/* Horizontal List - Auxillary Routines */ 
void generic_insert_h(hnode_t *p_beg, hnode_t *p_mid, hnode_t *p_end){
	p_mid->next = p_end; 
	p_mid->prev = p_beg; 
	p_beg->next = p_mid; 
	p_end->prev = p_mid; 
}

void generic_delete_h(hnode_t *ph_node){
	ph_node->prev->next = ph_node->next; 
	ph_node->next->prev = ph_node->prev; 
	free(ph_node); 
} 

hnode_t *search_node_h(hlist_t *ph_list, vertex_t v_search){
	hnode_t *ph_run = NULL; 
	
	for(ph_run = ph_list->next; ph_run != ph_list; ph_run = ph_run->next){
		if(ph_run->v == v_search)
			return (ph_run); 
	}

	return (NULL); 
}

hnode_t *get_node_h(vertex_t v_new){
	hnode_t *ph_new_node = (hnode_t*)xcalloc(1, sizeof(hnode_t)); 
	ph_new_node->v = v_new; 
	return (ph_new_node); 
}	

/* Graph - Auxillary routine - Part - Misc. */ 
void *xcalloc(size_t nr_items, size_t size_per_item){
	void *p = NULL; 
	p = calloc(nr_items, size_per_item); 
	assert(p); 
	return (p); 
}