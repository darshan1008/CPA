#include <stdio.h>
#include <stdlib.h>
#include <assert.h> 
#include "graph.h"

struct edge{
	vertex_t v_start; 
	vertex_t v_end; 
}; 

int main(){

	graph_t *g=NULL; 
	vertex_t v; 
	int i; 

	struct edge E[] = 	{	
							{1, 2}, {2, 3}, {3, 4},
							{4, 5}, {5, 6}, {6, 1},
							{1, 4}, {2, 5}, {3, 6}
						}; 

	g = create_graph(); 
	for(v=1; v < 7; ++v)
		assert(add_vertex(g, v) == SUCCESS); 

	for(i=0; i < sizeof(E) / sizeof(E[0]); i++)
		assert(add_edge(g, E[i].v_start, E[i].v_end) == SUCCESS); 
	print_graph(g, "STATE I:INITIAL"); 
	printf("|V| = %d, |E| = %d\n", get_nr_vertices(g), get_nr_edges(g)); 

	assert(remove_edge(g, 2, 3) == SUCCESS); 
	assert(remove_edge(g, 5, 6) == SUCCESS); 
	print_graph(g, "STATE II:After removing edges 2<->3 and 5<->6"); 
	printf("|V| = %d, |E| = %d\n", get_nr_vertices(g), get_nr_edges(g)); 

	assert(remove_vertex(g, 1) == SUCCESS); 
	print_graph(g, "STATE III:After removing vertex 1"); 
	printf("|V| = %d, |E| = %d\n", get_nr_vertices(g), get_nr_edges(g)); 

	assert(destroy_graph(&g) == SUCCESS); 
	printf("ALL ROUTINES SUCCESS\n");
	return (EXIT_SUCCESS); 
}; 