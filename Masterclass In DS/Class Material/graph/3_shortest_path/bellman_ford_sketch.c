enum color{
	WHITE = 0, 
	GRAY, 
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
	color_t c; 
	double d; 
	vnode_t *pred_vertex;

	struct vnode *prev; 
	struct vnode *next;  
}; 

struct edge{
	vnode_t *pv_start; 
	vnode_t *pv_end; 
	double w; 
}; 

struct graph{
	struct vnode *pv_list; 
	struct edge *p_edge_list; 
	int nr_vertices; 
	int nr_edges; 
}; 

struct graph *create_graph(){
	struct graph *g = calloc(1, sizeof(struct graph)); 

	/* allocate dummy node v list */ 
	g->pv_list = calloc(1, sizeof(struct vnode)); 
	
	/* Initialize head node of v list*/ 
	g->pv_list->v = -1; 
	g->pv_list->c = WHITE; 
	g->pv_list->d = 0.0; 
	g->pv_list->pred_vertex = NULL; 

	g->pv_list->prev = g->pv_list; 
	g->pv_list->next = g->pv_list; 

	/* allocate head node edge list */ 
	g->p_edge_list = calloc(1, sizeof(struct edge)); 
	
	/* initialize head node of edge list */ 
	g->p_edge_list->pv_start = NULL; 
	g->p_edge_list->pv_end = NULL; 
	g->p_edge_list->w = 0.0; 

	g->p_edge_list->prev = g->p_edge_list; 
	g->p_edge_list->next = g->p_edge_list; 

	g->nr_vertices = 0; 
	g->nr_edges = 0; 

	return (g); 
}

/* remember that we are dealing with a directed graph, 
   therefore, and v_end in hlist of v_start 
   but not other way round. 

   Also, we have to add a node in edge list as well */  
int add_edge(struct graph *g, int v_start, int v_end, double w){
	struct vnode *pv_start = NULL; 
	struct vnode  *pv_end = NULL; 
	struct edge *p_new_edge = NULL; 

	pv_start = search_node_v(g->pv_list, v_start); 
	if(pv_start == NULL)
		return (G_INVALID_VERTEX); 

	pv_end = search_node_v(g->pv_list, v_end); 
	if(pv_end == NULL)
		return (G_INVALID_VERTEX); 

	assert(insert_end_h(pv_start->ph_list, v_end, w) == SUCCESS); 

	p_new_edge = calloc(1, sizeof(struct edge)); 
	p_new_edge->pv_start = pv_start; 
	p_new_edge->pv_end = pv_end; 
	p_new_edge->w = w; 

	g->nr_edges++; 

	return (SUCCESS); 
}

int remove_edge(struct graph *g, int v_start, int v_end){
	// TODO
}

int bellman_ford(struct graph *g){
	struct edge *p_edge_run = NULL; 
	
	int N = g->nr_vertices; 
	int i; 

	for(i = 0; i < N-1; ++i)
		for(p_edge_run = g->p_edge_list->next; p_edge_run != p_edge_list; p_edge_run = p_edge_run->next)
			relax(g, p_edge_run->pv_start, p_edge_run->pv_end); 
		
	for(p_edge_run = g->p_edge_list->next; p_edge_run != p_edge_list; p_edge_run = p_edge_run->next)
		if(p_edge_run->pv_start->d > p_edge_run->pv_end->d + p_edge_run->w)
			return (G_DETECTED_NEGATIVE_PATH_CYCLE); 

	return (SUCCESS); 
}


