#include <stdio.h> 
#include <stdlib.h> 
#include <assert.h> 

struct hnode{
    int v; 
    double w; 

    struct hnode* prev; 
    struct hnode* next; 
};

struct vnode{
    int v; 
    struct hnode* ph_list; 
    int color; 
    double d;   /* cost of shortest path from source vertex to current vertex 
                    at any point of time. at the end of algorithm this field 
                    should reflect the cost of shortest between the source 
                    vertex and the current vertex 
                */ 
    struct vnode* pred_vertex; 

    struct vnode* prev; 
    struct vnode*next; 
}; 

struct edge{
    int u, 
    int v; 
    double w; 
}; 

struct graph{
    struct vnode* pv_list; 
    struct edge* p_edge_list; 
    int nr_vertices; 
    int nr_edges; 
}; 


void initialize_single_source(struct graph* g, int source_vertex){
    struct vnode* pv_run; 
    struct vnode* pv_source; 
    for(pv_run = g->pv_list->next; pv_run != g->pv_list; pv_run = pv_run->next){
        pv_run->d = INFINITY; 
        pv_run->c = WHITE; 
    }

    pv_source = search_node_v(g->pv_list, source_vertex); 
    pv_source->d = 0.0; 
}

void relax(struct graph* g, struct vnode* pv_u, struct vnode* pv_v){
    struct hnode* ph_v_in_u = NULL; 
    double w; 
    ph_v_in_u = h_search_node(pv_u->ph_list, v); 
    w = ph_v_in_u->w; 
    if(pv_v->d > pv_u->d + w){
        pv_v->d = pv_u->d + w; 
        pv_v->pred_vertex = pv_u; 
    }
}

int add_edge(struct graph* g, int u, int v, double w){
    struct vnode* pv_u = NULL; 
    struct vnode* pv_v = NULL; 
    struct edge* p_new_edge = NULL; 

    pv_u = v_search_node(g->pv_list, u); 
    pv_v = v_search_node(g->pv_list, v); 
    assert(pv_u && pv_v); 

    h_insert_end(pv_u->ph_list, v, w);
    h_insert_end(pv_v->ph_list, u, w); 

    edge_insert_end(g->p_edge_list, u, v, w); 
    g->nr_edges++; 

    return (SUCCESS); 
}

int remove_edge(struct edge* p_edge_list, int u, int v){
    struct vnode* pv_u = NULL; 
    struct vnode* pv_v = NULL; 
    struct hnode* ph_u_in_v = NULL; 
    struct hnode* ph_v_in_u = NULL; 
    struct edge* p_delete_edge = NULL; 

    pv_u = v_search_node(g->pv_list, u); 
    pv_v = v_search_node(g->pv_list, v); 
    assert(pv_u && pv_v); 

    ph_u_in_v = h_search_node(pv_v->ph_list, u); 
    ph_v_in_u = h_search_node(pv_u->ph_list, v); 

    assert(ph_u_in_v && ph_v_in_u); 
    h_generic_delete(ph_u_in_v); 
    h_generic_delete(ph_v_in_u); 

    p_delete_edge = edge_search_node(g->p_edge_list, u, v); 
    edge_generic_delete(p_delete_edge); 
    g->nr_edges--; 

    return (SUCCESS); 
}

void relax(struct graph* g, struct vnode* pv_u, struct vnode* pv_v){
    struct hnode* ph_v_in_u = NULL; 
    double w; 
    ph_v_in_u = h_search_node(pv_u->ph_list, v); 
    w = ph_v_in_u->w; 
    if(pv_v->d > pv_u->d + w){
        pv_v->d = pv_u->d + w; 
        pv_v->pred_vertex = pv_u; 
    }
}

bool bellman_ford(struct graph* g, int source_vertex){
    int i; 
    struct edge* p_edge_run = NULL; 
    struct vnode* pv_u = NULL; 
    struct vnode* pv_v = NULL; 

    initialize_single_source(g, source_vertex); 

    for(i = 0; i < g->nr_vertices - 1; ++i)
        for(p_edge_run = g->p_edge_list->next; 
            p_edge_run != g->p_edge_list; 
            p_edge_run = p_edge_run->next){
                pv_u = v_search_node(g->pv_list, p_edge_run->u); 
                pv_v = v_search_node(g->pv_list, p_edge_run->v); 
                relax(g, pv_u, pv_v); 
            }

    for(p_edge_run = g->p_edge_list->next; 
        p_edge_run != g->p_edge_list; 
        p_edge_run = p_edge_run->next){
            pv_u = v_search_node(g->pv_list, p_edge_run->u); 
            pv_v = v_search_node(g->pv_list, p_edge_run->v); 
            if(pv_v->d > pv_u->d + p_edge_run->w)
                return (FALSE); 
        }

    return (TRUE); 
}

struct edge* edge_create_list(); 
int edge_insert_end(struct edge* p_edge_list, int u, int v, double w); 
int edge_destroy_list(struct edge* p_list); 
void edge_generic_insert(struct edge* p_beg, struct edge* p_mid, struct edge* p_end); 
void edge_generic_delete(struct edge* p_delete_edge); 
/* while searching if p_run is of  the type struct edge* 
    then equality condition should be following 
    if((p_run->u == u && p_run->v == v) || (p_run->u == v) && (p_run->v == u))
        return p_run; 

    return NULL; 
*/ 
struct edge* edge_search_node(struct edge* p_edge_list, int u, int v); 
struct edge* get_edge(int u, int v, double w); 

