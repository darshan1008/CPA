class hnode{
	friend class vnode; 
	private: 
		vertex_t v; 
		hnode* prev; 
		hnode* next;
		hnode(vertex_t v=-1) : v(v), prev(0), next(0) { } 
}; 

class vnode{
	friend class graph; 
	private: 
		vertex_t v; 
		hnode* ph_list; 

		vnode* prev; 
		vnode* next; 

		vnode(vertex_t v=-1) : v(v), ph_list(new hnode), prev(0), next(0) {} 
		~vnode(){
			// horizontal list destruction 
		}
}; 

class graph{
	private: 
		vnode* pv_list; 
		size_t nr_vertices; 
		size_t nr_edges; 
	public: 
		graph() : pv_list(new vnode), nr_vertices(0), nr_edges(0){ }
		
		~graph(){
			// destroy list headed by pv_list 

			// delete pv_node; 
		}

		ret_t add_vertex(vertex_t v); 
		ret_t add_edge(vertex_t v_start, vertex_t v_end); 
		ret_t remove_vertex(vertex_t v); 
		ret_t remove_edge(vertex_t v_start, vertex_t v_end); 

		friend std::ostream& operator<<(std::ostream& os, const graph& ref_g); 
}; 

