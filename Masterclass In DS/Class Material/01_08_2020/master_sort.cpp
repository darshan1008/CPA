#include <iostream> 
#include <cstdlib>
#include <cassert> 
#include <ctime>

class Array{
private: 
	int* a; 
	int n; 
public: 
	Array(int size) : a(new int[size]), n(size) {}
	
	static friend std::istream& operator>>(std::istream& istr, Array& arr_obj){
		srand(time(0));
		for(int i = 0; i < arr_obj.n; ++i)
			arr_obj.a[i] = rand();
		return istr;   
	}

	static friend std::ostream& operator<<(std::ostream& ostr, Array& arr_obj){
		for(int i = 0; i < arr_obj.n; ++i)
			ostr << "a[" << i << "]:" << arr_obj.a[i] << std::endl; 
		return ostr; 
	}

	void insertion_sort(){
		int i, j; 
		int key; 
		for(j = 1; j < n; ++j){
			key = a[j]; 
			i = j - 1;
			while(i > -1 && a[i] > key){
				a[i+1] = a[i]; 
				i = i - 1; 
			}
			a[i+1] = key; 
		}
	}

	bool test_sort(){
		for(int i = 0; i < n-1; ++i)
			if(a[i] > a[i+1])
				return false; 
		return true;
	}

	~Array(){
		delete[] a; 
	}
}; 

int main(int argc, char* argv[]){
	
	if(argc != 2){
		std::cerr << "usage error:" << argv[0] << " number of elements" << std::endl; 
		return (-1); 
	}

	Array A(atoi(argv[1])); 
	std::cin >> A; 
	A.insertion_sort(); 
	assert(A.test_sort() == true); 
	std::cout << A; 

	return 0; 
}