#include<stdio.h>


struct A
{
	int a;
	char b;
	float c;

};

struct A obj = {10,'a',1.10f};
struct A *pObj;

int main()
{

	int arr[10] = {10,20};
	int i= 0;
	pObj = &obj;

	//printf("\n%d %d\n",pObj->a,(*pObj).a);
	for(i=0;i<10;++i)
	{
		printf("\n%ld",&(arr[i]));
	}

	/*	
	int a[10] = {0};
	int *p = a;
	int i;
	*(p + 1) = 20;

	a[2] = 30;
	for(i = 0; i<10 ; ++i)
		printf("%d ",a[i]);
	*/


	return 0;
}
