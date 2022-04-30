//list.h 

typedef int data_t; 
typedef enum { }ret_t; 
typedef int len_t; 

namespace ds{

	class snode{
	friend class slist; 
	friend class sclist; 
	private: 
		data_t data; 
		snode* next;
		snode(data_t new_data = 0); 
	}; 

	class dnode{
	friend class dlist; 
	friend class dclist; 
	private: 
		data_t data; 
		dnode* prev; 
		dnode* next; 
		dnode(data_t new_data = 0); 
	}; 

	class slist{

	}; 

	class sclist{

	}; 

	class dlist{

	}; 

	class dclist{

	}; 

}


// tree.h 

namespace ds{
	class bst_node{
	friend class bst; 
	private: 
		data_t data; 
		bst_node* left; 
		bst_node* right; 
		bst_node* parent; 
		bst_node(data_t new_data); 
	};  

	class bst{
	private: 
		bst_node* p_root_node; 
	public: 

	}; 

	class rb_tree; 
	class avl_tree; 
	class leftist_tree; 
	class b_tree; 
	class b_plus_tree; 
	class splay_tree; 
}

// graph.h
namespace ds{
	class hnode{

	}; 

	class vnode{

	}; 

	class graph{

	}; 



}

// heap.h 
namespace ds{

}

int main(){
	ds::dclist lst; 
	ds::rb_tree rbt; 
	ds::graph g; 

	lst.find(200); 
	rbt.insert(100); 
	g.dijisktra(3); 
}

namespace ds{
	namespace list{
		template <typename T> 
		class snode{
		private: 
			T data; 
			snode* next; 
			snode(T new_data);
		}; 

		template <typename T> 
		class dnode{
		private: 
			T data; 
			dnode* prev; 
			dnode* next; 
			dnode(T new_data); 
		}; 

		template <typename T> 
		class dclist{
		private: 
			dnode<T>* p_head_node; 
		public: 
			class iterator{

			}; 
		}; 

		template <typename T> 
		class dlist{
			class iterator{

			}; 
		}; 

		template <typename T> 
		class slist{
			class iterator{

			}; 

		}; 

		template <typename T> 
		class sclist{
			class iterator{

			}; 
		}; 

	}
}

// WRITE SERVER COMPATIBLE TO THIS CLIENT 
int main(){
	ds::list::dclist<int> lst; 

	for(data = 0; data < 10; ++data)
		lst.insert_end(data); 

	for(ds::list::dclist<int>::iterator iter = lst.begin(); 
		iter != lst.end(); 
		++iter)
		std::cout << *iter << std::endl; 

}

