#include <iostream>
#include <cstdlib>

template <typename T1, typename T2> 
unsigned long long int get_offset(){
	return (unsigned long long int)(&(((T1*)0)->T2)); 
}

struct A{
	int a; 
	char b; 
	float c; 
}; 

typedef int c; 

int main(){
	unsigned long long int off; 
	off = get_offset<struct A*, c>(); 
	printf("off = %llu\n", off); 
	return (0); 
}