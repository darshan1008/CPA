enum color{
	WHITE = 0, 
	GREY, 
	BLACK
}; 

struct hnode{
	int v; 
	double w; 

	struct hnode *prev; 
	struct hnode *next; 
}; 

struct vnode{
	int v; 
	struct hnode *ph_list; 
	enum color c; 
	double key; 
	struct vnode *p_pred_vertex; 

	struct vnode *prev; 
	struct vnode *next; 
};

struct graph{
	struct vnode *pv_list; 
	int nr_vertices; 
	int nr_edges; 
}; 

struct v_node{
	struct vnode *pv_node; 
	struct v_node *prev; 
	struct v_node *next; 
}; 

// generic_insert_v, generic_delete_v, search_node_v, get_node_v, create_list_v, insert_end_v, remove_end_v, destroy_list_v 
// create_prio_queue_v, enqueue_prio_v, dequeue_prio_v, is_prio_queue_empty_v, find_prio_queue_v, destroy_prio_queue_v 
// int enqueue_prio_v(struct prio_queue_v *p_prio_queue, struct v_node *p_v_node); 
// int dequeue_prio_v(struct prio_queue_v *p_prio_queue, struct v_node **pp_v_node); 
// bool find_prio_queue_v(struct prio_queue_v *p_prio_queue, vnode_t *pv_node); 

// graph mamagement routines are same, only prim's algorithm needs to be written 

int prims(struct graph *g, int v_root){
	vnode_t *pv_run; 
	vnode_t *pv_u; 
	vnode_t *pv_v; 
	hnode_t *ph_run; 
	struct v_node *p_v_node; 
	bool b; 
	// MST-PRIM(G, w, r)
	// 		for every u in G.V 
	// 			u.key = infinity 
	// 			u.pi = NIL 
	// 		r.key = 0.0 

	for(pv_run = g->pv_list->next; pv_run != g->pv_list; pv_run = pv_run->next){
		if(pv_run->v != v_root){
			pv_run->key = INFINITY; 
		}else{
			pv_run->key = 0.0; 
		}
		pv_run->p_pred_vertex = NULL; 
	}

	// 		Q = G.V 
	struct v_node *p_prio_queue = create_prio_queue_v(); 
	for(pv_run = g->pv_list->next; pv_run != g->pv_list; pv_run = pv_run->next){
		enqueue_prio_v(p_prio_queue, get_node_v(pv_run)); 
	}

	// while Q is not empty 
	// 	 	u = EXTRACT_MIN(Q)
	//		for every in v in G.adj[u]
	// 		if v is in Q and v.key > w(u, v)
	//			v.key = w(u, v)
	//			v.pred = u 

	while(is_prio_queue_empty_v(p_prio_queue) != PRIO_QUEUE_EMPTY){
		dequeue_prio_v(p_prio_queue, &p_v_node); 
		pv_u = p_v_node->pv_node; 
		for(ph_run = pv_u->ph_list->next; ph_run != pv_u->ph_list; ph_run = ph_run->next){
			pv_v = v_search_node(g->pv_list, ph_run->v); 
			b = find_prio_queue_v(p_prio_queue, pv_v); 
			if(b == TRUE && pv_v->key > ph_run->w){
				pv_v->p_pred_vertex = pv_u; 
				pv_v->key = ph_run->w; 
			}
		}
	}

	destroy_prio_queue_v(p_prio_queue); 
	p_prio_queue = NULL; 

	// if pv_run->key == inifinity (means graph is not connected and you can return an error)
	// otherwise 
	return (SUCCESS); 
} 

void print_prim_mst(struct graph *g, int v_root){
	vnode_t *pv_run; 

	printf("[START]<->");
	for(pv_run = g->pv_list->next; pv_run != g->pv_list; pv_run = pv_run->next)
		if(pv_run->v != v_root)
			printf("[%d <-> %d]<->", pv_run->v, pv_run->p_pred_vertex->v); 
	
	puts("[END]"); 
}
