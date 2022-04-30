#include <stdio.h> 
#include <stdlib.h> 

#define OFFSET_OF(type_name, member_name)	((unsigned long int)(&((type_name*)0)->member_name))

#define CONTAINER_OF(addr, type_name, member_name)	((type_name*)((char*)addr - OFFSET_OF(type_name, member_name)))

struct A{
	int a; 
	char b; 
	float c; 
}; 

struct A inA = {10, 'A', 3.14}; 

void f(float* pf); 

int main()
{
	
	struct A* pA; 
	f(&inA.c); 

	return 0; 

}

void f(float* pf)
{
	struct A* pA; 
	printf("*pf=%f\n", *pf); 

	pA = (struct A*)((char*)pf - ((unsigned long int)(&((struct A*)0)->c)));
	printf("pA->a : %d\n", pA->a); 
	printf("pA->b : %c\n", pA->b); 
	printf("pA->c : %f\n", pA->c); 

	pA =  CONTAINER_OF(pf,struct A,c);
	printf("pA->a : %d\n", pA->a); 
	printf("pA->b : %c\n", pA->b); 
	printf("pA->c : %f\n", pA->c); 

}

