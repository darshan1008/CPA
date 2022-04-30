// HOMEWORK 
// Q1: Verify whether dry run of merge sort procedure
// is generating calls to merge procedure as we figured 
// out manually! 
// Q2: Verify whether implementation of merge sort 
// is nothing but practical manifestation of theoretical 
// DIVIDE AND CONQUOR STRATEGY. 
// TRY TO WRITE CAREFULLY, which is divide phase and which is 
// conquor phase.
#include<stdio.h>
#include<assert.h>

void merge_sort(int *a, int p, int r);
void merge(int* a, int p, int q, int r);

int main(){
	int i;
	int a[8] = {345, 4, 235, 47, 58, 31, 47, 1}; 
	puts("before sort ");
	for(i=0;i<sizeof(a)/sizeof(a[0]);i++)
	{
		printf("a[%d] : %d\n",i,a[i]);
	}

	merge_sort(a, 0, 7);
	puts("after sort  ");

	for(i=0;i<sizeof(a)/sizeof(a[0]);i++)
	{
		printf("a[%d] : %d\n",i,a[i]);
	}


}

void merge_sort(int *a, int p, int r){
	int q; 
	if(p < r){
		q = (p+r)/2; 
		merge_sort(a, p, q); 
		merge_sort(a, q+1, r); 
		merge(a, p, q, r); 
	}
}

void merge(int* a, int p, int q, int r){
	int* a1 = NULL, *a2 = NULL; 
	int n1, n2; 

	int cnt = 0; 
	int i = 0;
	int j = 0;
	int k = 0; 


	n1 = q - p + 1; 
	n2 = r - q; 

	a1 = (int*)malloc(n1 * sizeof(int)); 
	a2 = (int*)malloc(n2 * sizeof(int)); 
	assert(a1 != NULL && a2 != NULL); 
	memset(a1, 0, n1 * sizeof(int)); 
	memset(a2, 0, n2 * sizeof(int)); 

	for(cnt = 0; cnt < n1; ++cnt)
		a1[cnt] = a[p+cnt]; 

	for(cnt = 0; cnt < n2; ++cnt)
		a2[cnt] = a[q+1+cnt]; 

	k = 0; 
	while(k < (n1 + n2))
	{
		if(a1[i] <= a2[j])
		{
			a[p+k] = a1[i]; 
			i++; 
			k++; 
			// if a1 finishes earlier
			if(i == n1)
			{
				// copy back remaining a2 in a
				while(j < n2)
				{
					a[p+k] = a2[j]; 
					j++;
					k++; 
				}

				break; 
			}
		}
		else{
			a[p+k] = a2[j]; 
			j++;
			k++; 
			// if a2 finishes first 
			if(j == n2)
			{
				// copy back remaining a1 into a. 
				while(i < n1)
				{
					a[p+k] = a1[i]; 
					i++; 
					k++; 
				}
				break; 
			}
		}
	}

	free(a1); 
	free(a2); 
	a1 = a2 = NULL; 

}