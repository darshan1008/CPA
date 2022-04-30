class HNode{
	friend class VNode; 
	friend class Graph; 
	private: 
		int vertex; 
		double w;
		HNode(int init_vertex, double init_w = 0.0) : vertex(init_vertex), w(init_w) { }  
}; 

class VNode{
	private: 
		int vertex;
		std::vector<HNode> hvec;  
		color_t c; 
		double d; // key in case prim's 
		VNode *p_pred_node; 
}; 

class Graph{
	private: 
		std::vector<VNode> vvec; 
	public: 

}; 

// C 

struct hnode{
	int vertex; 
	double w; 
}; 

struct vec_hnode{
	struct hnode *ph_array; 
	size_t size; 
}; 

struct vnode{
	int vertex; 
	struct vec_hnode *h_vec; 
	color_t c; 
	double d; 
}; 

struct vec_vnode{
	struct vnode *pv_array; 
	size_t size; 
}; 

struct graph{
	struct vec_vnode *v_vec; 
	int nr_vertices; 
	int nr_edges; 
}; 

int main(){
	struct graph *g = create_graph(); 

	// access edge (i, j)
	g->v_vec->pv_array[i]->h_vec->ph_array[j]; // O(1)
	g->v_vec->pv_array[j]->h_vec->ph_array[i]; // O(1)
}

/* 
// BE FLUENT IN COMPLEX DATA LAYOUT HANDING AS MUCH AS 
// YOU ARE FLUENT WITH FOLLOWING ALGORITHMS
bool search(int *arr, int n, int search_element){
	int i; 

	for(i = 0; i < n; ++i)
		if(arr[i] == search_element)
			return true; 
	return false; 
}
*/ 