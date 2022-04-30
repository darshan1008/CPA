#include"MergeSortHeader.h"
void Output(int *pArr,size_t n);
int main()
{
    int pArr[5] = {20,50,40,10,30};
    int n = 5;
    Output(pArr,5);
    merge_sort(pArr,0,n-1);
    Output(pArr,5);
    return(0);
}

void Output(int *pArr,size_t n)
{
	int i = 0;

	while(i < n)
	{
		printf("ARR[%d]:%d\n",i,pArr[i]);
		i++;
	}
}