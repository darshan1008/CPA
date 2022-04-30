#include <stdio.h> 
#include <stdlib.h> 


int main(){
	unsigned long long n = 0; 

	printf("I:n = %llu \t size : %d\n", n,sizeof(n)); 
	
	*(char*)&n = 0xaaee;  
	printf("1:n = %llx\n", n);
	*(short*)((char*)&n + 1) = 0xbbbb; 
	printf("2:n = %llx\n", n);
	*(int*)((char*)&n + 3) = 0xcccccccc; 
	printf("3:n = %llx\n", n); 
	*(char*)((char*)&n + 7) = 0xdd; 
	printf("4:n = %llx\n", n); 

	printf("\nsize : %d %d %d \n",sizeof(0xaa),sizeof(0xbbbb),sizeof(0xccccccc));
	return 0; 
}

/* 
n : ull
&n : ull*

*(&n) : *(ull*) = ull

// [] [] [] [] [] [] [] [] 
*(char*)&n = 0xff; 
// [ff] [] [] [] [] [] [] [] 

*(short*)((char*)&n + 1) = 0xffff; 

// [ff] [ff] [ff] [] [] [] [] [] 

	*(int*)((char*)&n + 3) = 0xffffffff; 

// [ff] [ff] [ff] [ff] [ff] [ff] [ff] [] 

*/ 
