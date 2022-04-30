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

ret_t add_edge(graph_t *g, vertex_t v_start, vertex_t v_end, double w){
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

	assert(insert_end_h(pv_node_start->ph_list, v_end, w) == SUCCESS); 
	assert(insert_end_h(pv_node_end->ph_list, v_start, w) == SUCCESS); 

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

ret_t dfs(graph_t *g){
	vnode_t *pv_run; 

	reset(g); 
	printf("[BEGINNING]<->"); 
	for(pv_run = g->pv_list->next; pv_run != g->pv_list; pv_run = pv_run->next){
		if(pv_run->c == WHITE)
			dfs_visit(g, pv_run); 
	}
	puts("[END]"); 

	return (SUCCESS); 
}

ret_t bfs(graph_t *g, vertex_t v){
	vnode_t *pv_source; 
	vnode_t *u = NULL; 
	vnode_t *pv_of_ph; 
	hnode_t *ph_run; 

	v_queue_t *Q = NULL; 

	reset(g); 

	pv_source = search_node_v(g->pv_list, v); 
	if(pv_source == NULL)
		return (G_INVALID_VERTEX); 

	pv_source->c = GRAY; 

	Q = v_create_queue(); 
	assert(v_enqueue(Q, pv_source)); 
	printf("[BEGINNING]<->"); 
	while(v_is_queue_empty(Q) != TRUE){
		assert(v_dequeue(Q, &u) == SUCCESS); 
		printf("[%d]<->", u->v); 
		ph_run = u->ph_list->next; 
		while(ph_run != u->ph_list){
			pv_of_ph = search_node_v(g->pv_list, ph_run->v); 
			if(pv_of_ph->c == WHITE){
				pv_of_ph->c = GRAY; 
				assert(v_enqueue(Q, pv_of_ph) == SUCCESS); 
			}
			ph_run = ph_run->next; 
		}
		u->c = BLACK; 
	}
	puts("[END]"); 
	assert(v_destroy_queue(&Q) == SUCCESS && Q == NULL); 

	return (SUCCESS); 
}


/* Graph - Auxillary routines - traversal algorithms */ 

void reset(graph_t *g){
	vnode_t *pv_run; 

	for(pv_run = g->pv_list->next; pv_run != g->pv_list; pv_run = pv_run->next){
		pv_run->c = WHITE; 
	}
}

void dfs_visit(graph_t *g, vnode_t *pv_node){
	hnode_t *ph_run = NULL;
	vnode_t *pv_of_hnode = NULL;  

	printf("[%d]<->", pv_node->v); 
	pv_node->c = GRAY; 

	for(ph_run = pv_node->ph_list->next; ph_run != pv_node->ph_list; ph_run = ph_run->next){
		pv_of_hnode = search_node_v(g->pv_list, ph_run->v); 
		if(pv_of_hnode->c == WHITE)
			dfs_visit(g, pv_of_hnode); 
	}
	pv_node->c = BLACK; 
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
	pv_new_node->c = WHITE; 
	return (pv_new_node); 
}

/* Graph - Auxillary routines - Part 2 - Horizontal List Management */ 
hlist_t *create_list_h(void){
	hnode_t *ph_head_node = get_node_h(-1, 0.0); 
	ph_head_node->prev = ph_head_node; 
	ph_head_node->next = ph_head_node; 
	return (ph_head_node); 
} 

ret_t insert_end_h(hlist_t *ph_list, vertex_t v_new, double w){
	generic_insert_h(ph_list->prev, get_node_h(v_new, w), ph_list); 
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

hnode_t *get_node_h(vertex_t v_new, double init_w){
	hnode_t *ph_new_node = (hnode_t*)xcalloc(1, sizeof(hnode_t)); 
	ph_new_node->v = v_new; 
	ph_new_node->w = init_w; 
	return (ph_new_node); 
}	

/* Graph - Auxillary Routines - BFS Queue */ 
v_queue_t *v_create_queue(void){
	return v_create_list(); 
}

ret_t v_enqueue(v_queue_t *pv_queue, vnode_t *pv_new_node){
	return v_insert_end(pv_queue, pv_new_node); 
}

ret_t v_dequeue(v_queue_t *pv_queue, vnode_t **ppv_beg_node){
	return v_remove_beg(pv_queue, ppv_beg_node); 
}

bool v_is_queue_empty(v_queue_t *pv_queue){
	return v_is_list_empty(pv_queue); 
}

ret_t v_destroy_queue(v_queue_t **ppv_queue){
	return v_destroy_list(ppv_queue); 
}

/* Graph - BFS QUEUE - List */ 
v_list_t *v_create_list(void){
	v_list_t *pvq_list = get_node_vq(NULL); 
	pvq_list->prev = pvq_list; 
	pvq_list->next = pvq_list; 
	return (pvq_list);
}

ret_t v_insert_end(v_list_t *pvq_list, vnode_t *pv_new_node){
	generic_insert_vq(pvq_list->prev, get_node_vq(pv_new_node), pvq_list); 
	return (SUCCESS); 
}

ret_t v_remove_beg(v_list_t *pvq_list, vnode_t **ppv_beg_node){
	if(pvq_list->prev == pvq_list && pvq_list->next == pvq_list)
		return (V_LIST_EMPTY); 
	*ppv_beg_node = pvq_list->next->pv_node; 
	generic_delete_vq(pvq_list->next); 
	return (SUCCESS); 
}

bool v_is_list_empty(v_list_t *pvq_list){
	if(pvq_list->prev == pvq_list && pvq_list->next == pvq_list)
		return (TRUE); 
	return (FALSE); 
}

ret_t v_destroy_list(v_list_t **ppvq_list){
	v_list_t *pvq_list = NULL; 
	v_node_t *pvq_run = NULL; 
	v_node_t *pvq_run_next = NULL;

	pvq_list = *ppvq_list; 
	pvq_run = pvq_list->next; 
	while(pvq_run != pvq_list){
		pvq_run_next = pvq_run->next; 
		free(pvq_run);  
		pvq_run = pvq_run_next; 
	} 

	free(pvq_list); 
	*ppvq_list = NULL; 
	return (SUCCESS); 
}

/* Graph - BFS QUEUE - List - Auxillary */ 
void generic_insert_vq(v_node_t *pvq_beg, v_node_t *pvq_mid, v_node_t *pvq_end){
	pvq_mid->next = pvq_end; 
	pvq_mid->prev = pvq_beg; 
	pvq_beg->next = pvq_mid; 
	pvq_end->prev = pvq_mid; 
}

void generic_delete_vq(v_node_t *pvq_delete_node){
	pvq_delete_node->prev->next = pvq_delete_node->next; 
	pvq_delete_node->next->prev = pvq_delete_node->prev; 
	free(pvq_delete_node); 
} 

v_node_t *get_node_vq(vnode_t *pv_new_node){
	v_node_t *pvq_node = (v_node_t*)xcalloc(1, sizeof(v_node_t)); 
	pvq_node->pv_node = pv_new_node; 
	return (pvq_node); 
}

/* Graph - Auxillary routine - Part - Misc. */ 
void *xcalloc(size_t nr_items, size_t size_per_item){
	void *p = NULL; 
	p = calloc(nr_items, size_per_item); 
	assert(p); 
	return (p); 
}