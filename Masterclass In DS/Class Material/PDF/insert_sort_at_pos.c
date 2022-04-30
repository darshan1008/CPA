#include<stdio.h>

void insret_at_sorting_pos(int *a,int n)
{
	int key;
	int i,j;

	key = a[n-1];
	i = n-2;
	
	while(i > -1 && a[i] > key)
	{
		a[i+1] = a[i];
		i = i-1;
	}

	a[i+1] = key;
 
}

void Output(int *pArr,int iCount)
{
	int iCounter1 = 0;
	for(iCounter1 = 0; iCounter1 < iCount; iCounter1++)
		printf("pArr[%d] : %d\n",iCounter1,pArr[iCounter1]);
}


int main()
{
	int a[6] = {10,20,30,40,50,25};
	int b[10] = {45,78,2,465,125,74,56,12,01,15};
	int i;

	puts("\na before sort");
	Output(a,6);
	insret_at_sorting_pos(a,6);		
	puts("\na After Sort");
	Output(a,6);

	puts("\nb before sort");
	Output(b,10);
	
	for(i=2;i<=10; i++)		
		insret_at_sorting_pos(b,i);		

	puts("\nb After Sort");
	Output(b,10);


	

	return 0;	
}