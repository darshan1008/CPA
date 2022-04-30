#include <stdio.h>
#include <stdlib.h>
#include <assert.h> 
#include <time.h>
#include "graph.h"

struct edge{
	vertex_t v_start; 
	vertex_t v_end; 
	double w; 
}; 

int main(){

	graph_t *g=NULL; 
	vertex_t v; 
	int i; 

	struct edge E[] = 	{	
							{1, 6, 1.1}, {1, 2, 2.2}, {1, 3, 3.3}, {4, 5, 4.4}, 
							{2, 5, 10.2}, {3, 4, 12.3}, {2, 6, 3.6}, {3, 6, 8.2}
						}; 

	g = create_graph(); 
	for(v=1; v < 7; ++v)
		assert(add_vertex(g, v) == SUCCESS); 

	for(i=0; i < sizeof(E) / sizeof(E[0]); i++)
		assert(add_edge(g, E[i].v_start, E[i].v_end, E[i].w) == SUCCESS); 
	print_graph(g, "STATE I:INITIAL"); 
	printf("|V| = %d, |E| = %d\n", get_nr_vertices(g), get_nr_edges(g)); 

	printf("Depth First Traversal Sequence:\n"); 
	assert(dfs(g) == SUCCESS); 
	printf("Bread First Traversal Sequence:\n");
	srand(time(0));  
	assert(bfs(g, (rand() % 6)+1)  == SUCCESS); 
	assert(destroy_graph(&g) == SUCCESS && g == NULL); 

	return (EXIT_SUCCESS); 
}