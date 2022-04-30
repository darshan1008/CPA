#include <stdio.h> 
#include <stdlib.h>
#include <assert.h>
#include "graph.h"

#define NR_VERTICES 6 

typedef struct edge edge_t; 

struct edge{
	vertex_t v_start; 
	vertex_t v_end; 
}; 


int main(){
	graph_t* g = NULL; 
	edge_t E[] = 	{ 
						{1, 2}, {2, 3}, {3, 4}, {4, 5}
						{5, 6}, {6, 1}, {2, 5}, {3, 6}
					}; 
	ret_t ret; 
	int i; 
	
	g = create_graph(); 
	assert(g); 

	for(i = 0; i < NR_VERTICES; ++i){
		ret = add_vertex(g, i+1); 
		assert(ret == SUCCESS); 
	}

	for(i = 0; i < sizeof(E) / sizeof(E[0]); ++i){
		ret = add_edge(g, E[i].v_start, E[i].v_end); 
		assert(ret == SUCCESS); 
	}

	puts("Graph:STATE 1:After immediate creation:"); 
	print_graph(g); 

	ret = add_vertex(g, 7); 
	assert(ret == SUCCESS); 

	ret = add_edge(g, 1, 7); 
	assert(ret == SUCCESS); 

	ret = add_edge(g, 6, 7); 
	assert(ret == SUCCESS); 

	puts("Graph:STATE 2:After adding vertex 7 and edges (1, 7) & (6, 7):"); 
	print_graph(g); 

	ret = remove_edge(g, 2, 5);
	assert(ret == SUCCESS); 

	ret = remove_edge(g, 3, 6); 
	assert(ret == SUCCESS); 

	puts("Graph:STATE 3:After removing edges (2, 5) & (3, 6):"); 
	print_graph(g); 

	ret = remove_vertex(g, 1); 
	assert(ret == SUCCESS); 

	puts("Graph:STATE 4:After removing vertex 1:"); 
	print_graph(g); 

	ret = destroy_graph(&g); 
	assert(ret == SUCCESS && g == NULL); 

	return (EXIT_SUCCESS); 
}