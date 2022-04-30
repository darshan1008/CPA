#include"MergeSortHeader.h"
#include<malloc.h>
#include<stdlib.h>

void merge_sort(int *pArr,int p,int r){
	int q;
	if(p < r){
		q = (p+r) / 2;
		//a[p...q] ->unsorted
		merge_sort(pArr,p,q);
		//a[p...q] ->unsorted
		merge_sort(pArr,q+1,r);
		merge(pArr,p,q,r);

	}
}

void merge(int *pArr,int p,int  q,int r)
{
	int *a1 = NULL;	
	int *a2 = NULL;

	int n1,n2;
	int i = 0;
	int j = 0;
	int k = 0;
	int cnt = 0;

	n1 = q - p + 1;
	n2 = r - q;

	a1 = (int*)calloc(n1,sizeof(int));
	a2 = (int*)calloc(n2,sizeof(int));
	
	if(a1 == NULL || a2 == NULL)
	{
		exit(0);
	}

	for(cnt = 0; cnt< n1; cnt++){
		a1[cnt] = pArr[p+cnt];
	}

	for(cnt = 0; cnt < n2; cnt++){
		a2[cnt] = pArr[q+1+cnt];
	}

	k = 0;
	while(k < (n1+n2))
	{
		if(a1[i] <= a2[j])
		{
			pArr[p+k] = a1[i];
			i++;
			k++;

			if(i == n1)	
			{
				while(j < n2)
				{
					pArr[p+k] = a2[j];
					k++;
					j++;
				}
				break;
			}
		}
		else	
		{
			pArr[p+k] = a2[j];
			j++;
			k++;
			if(j == n2)
			{
				while(i < n1)
				{
					pArr[p+k] = a1[i];
					i++;
					k++;
				}
				break;
			}
		}
	}

	free(a1);
	free(a2);
	a1 = NULL;
	a2 = NULL;
}

void MergeSortInMemory(int *pArr,int n);

LP_MERGE_SORT_VECTOR CreateMergeSortVector(void);
RET_T PushBackMergeSort(LP_MERGE_SORT_VECTOR pVector,MERGE_DATA Data);
RET_T DestroyMergeSortVector(LP_MERGE_SORT_VECTOR pVector);
void DisplayMergeSortVector(LP_MERGE_SORT_VECTOR pVector);
