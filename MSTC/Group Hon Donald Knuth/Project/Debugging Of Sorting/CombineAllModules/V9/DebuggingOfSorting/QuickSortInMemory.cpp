
#include"QuickSortHeaders.h"


/*
	CALL:
		quick_sort(arr,0,N-1);
*/

LP_QUICK_SORT_VECTOR g_pQuicksortVector;

void QuickSortInMemory(int* arr, size_t n)
{
	N = n;
	quick_sort(arr,0,N-1);
}

void quick_sort(int *pArr,int p,int r)
{
	int q = 0;
	if(p<r)
	{
		q = partition(pArr,p,r);
		quick_sort(pArr,p,q-1);
		quick_sort(pArr,q+1,r);
	}
}

int partition(int *pArr,int p,int r)
{
	int x = 0;	
	int tmp = 0;
	int flag = 0;
	QUICKSORTDATA quickObj;
	QUICKSORT_ARRAY arrObj;
	
	memset(&arrObj,0,sizeof(QUICKSORT_ARRAY));
	memset(&quickObj,0,sizeof(QUICKSORTDATA));

	arrObj.pivote = pArr[r];
	arrObj.pArr = pArr;

	copy_array(arrObj,&(quickObj.arrayObj),N);
	quickObj.rangeObj.toLine = 5+ 1;
	quickObj.rangeObj.fromLine = 5+2;
	PushBackQuick(g_pQuicksortVector,quickObj);
	memset(&quickObj,0,sizeof(QUICKSORTDATA));

    flag = 0;
	for(arrObj.i = p-1,arrObj.j = p; arrObj.j < r; arrObj.j++)
	{		
		if(arrObj.pArr[arrObj.j]  <= arrObj.pivote)
		{   			
            copy_array(arrObj,&(quickObj.originalArrayObj),N);

            if (arrObj.i != arrObj.j)
            {
                if (arrObj.i == -1)
                {
                    tmp = arrObj.pArr[arrObj.i + 1];
                    arrObj.pArr[arrObj.i + 1] = arrObj.pArr[arrObj.j];
                    pArr[arrObj.j] = tmp;
                    arrObj.i++;
                }
                else
                {
                    arrObj.i++;
                    tmp = arrObj.pArr[arrObj.i];
                    arrObj.pArr[arrObj.i] = arrObj.pArr[arrObj.j];
                    pArr[arrObj.j] = tmp;
                }
            }
    
			
            quickObj.isSwapElementDraw = ON;
            quickObj.SwapElement.swapIndex1 = arrObj.i;
            quickObj.SwapElement.swapIndex2 = arrObj.j;

			quickObj.isIndexDraw = ON;
			quickObj.isConditionDraw = ON;
			quickObj.isConditionSatisfied = ON;

            copy_array(arrObj,&(quickObj.arrayObj),N);

			quickObj.rangeObj.toLine = 5+4;
			quickObj.rangeObj.fromLine = 5+6;

			PushBackQuick(g_pQuicksortVector,quickObj);
			memset(&quickObj,0,sizeof(QUICKSORTDATA));
		}
        else
        {
			
			quickObj.isConditionDraw = ON;	
            quickObj.isIndexDraw = ON;
			quickObj.isConditionSatisfied = ON;
            copy_array(arrObj,&(quickObj.arrayObj),N);
            copy_array(arrObj, &(quickObj.originalArrayObj), N);
			quickObj.rangeObj.toLine = 0;
			quickObj.rangeObj.fromLine = 0;
            PushBackQuick(g_pQuicksortVector,quickObj);
            memset(&quickObj,0,sizeof(QUICKSORTDATA));
        }
	}
	if(arrObj.i+1 != r)
	{
		quickObj.isSwapElementDraw = ON;
		quickObj.SwapElement.swapIndex1 = arrObj.i+1;
		quickObj.SwapElement.swapIndex2 = r;
	}
	tmp = arrObj.pArr[arrObj.i+1];
	arrObj.pArr[arrObj.i+1] = arrObj.pArr[r];
	arrObj.pArr[r] = tmp;

	quickObj.isIndexDraw = ON;
	copy_array(arrObj,&(quickObj.arrayObj),N);
    copy_array(arrObj, &(quickObj.originalArrayObj), N);
	quickObj.rangeObj.toLine = 5+7;
	quickObj.rangeObj.fromLine =5+ 7;
	PushBackQuick(g_pQuicksortVector,quickObj);
	memset(&quickObj,0,sizeof(QUICKSORTDATA));

	return (arrObj.i+1);
}

void copy_array(QUICKSORT_ARRAY srcObj,QUICKSORT_ARRAY *destObj,int n)
{
    int iCounter = 0;
	
    destObj->pArr = (int *)malloc(sizeof(int)*n);  
    for(iCounter = 0; iCounter < n ; iCounter++)
    {
        destObj->pArr[iCounter] = srcObj.pArr[iCounter];
    }
    destObj->i = srcObj.i; 
    destObj->j = srcObj.j; 
    destObj->pivote = srcObj.pivote; 
}



/*Vector functionality*/

LP_QUICK_SORT_VECTOR CreateQuicksortVector(void)
{
    LP_QUICK_SORT_VECTOR pQuicksortVector = NULL;
    pQuicksortVector = (LP_QUICK_SORT_VECTOR)malloc(sizeof(LP_QUICK_SORT_VECTOR));
    if(NULL == pQuicksortVector)
    {
        exit(-1);
    }
    pQuicksortVector->pQuickSortData = NULL;
    pQuicksortVector->iVectorSize = 0;
    //printf("SIZE(QUICKSORTDATA):[%d]\n",sizeof(QUICKSORTDATA));
    return(pQuicksortVector);
}

RET_T PushBackQuick(LP_QUICK_SORT_VECTOR pVector,QUICKSORTDATA QuickSortData)
{
    //printf("PushBackQuick - 0,pp:[%d] size:[%d]\n",pVector->pQuickSortData,pVector->iVectorSize);
    pVector->pQuickSortData = (QUICKSORTDATA*)realloc(pVector->pQuickSortData,(pVector->iVectorSize+1) * sizeof(QUICKSORTDATA));
    // puts("before NULL checking");
   if(NULL == pVector->pQuickSortData)
    {
        puts("MEMORY ERROR");
        exit(-1);
    }
    
    //printf("pp:[%ld]\n",pVector->pQuickSortData);
    //printf("pp[%d]:[%ld]\n",pVector->iVectorSize,&(pVector->pQuickSortData[pVector->iVectorSize]));

    (pVector->pQuickSortData[pVector->iVectorSize]).arrayObj.pArr = QuickSortData.arrayObj.pArr;
    (pVector->pQuickSortData[pVector->iVectorSize]).arrayObj.i = QuickSortData.arrayObj.i;
    (pVector->pQuickSortData[pVector->iVectorSize]).arrayObj.j = QuickSortData.arrayObj.j;
    (pVector->pQuickSortData[pVector->iVectorSize]).arrayObj.pivote = QuickSortData.arrayObj.pivote;

    (pVector->pQuickSortData[pVector->iVectorSize]).originalArrayObj.pArr = QuickSortData.originalArrayObj.pArr;
    (pVector->pQuickSortData[pVector->iVectorSize]).originalArrayObj.i = QuickSortData.originalArrayObj.i;
    (pVector->pQuickSortData[pVector->iVectorSize]).originalArrayObj.j = QuickSortData.originalArrayObj.j;
    (pVector->pQuickSortData[pVector->iVectorSize]).originalArrayObj.pivote = QuickSortData.originalArrayObj.pivote;
    
    (pVector->pQuickSortData[pVector->iVectorSize]).isIndexDraw = QuickSortData.isIndexDraw;
    (pVector->pQuickSortData[pVector->iVectorSize]).isNewIteration = QuickSortData.isNewIteration;
    (pVector->pQuickSortData[pVector->iVectorSize]).isConditionDraw = QuickSortData.isConditionDraw;
    (pVector->pQuickSortData[pVector->iVectorSize]).isConditionSatisfied = QuickSortData.isConditionSatisfied;
    

    (pVector->pQuickSortData[pVector->iVectorSize]).isSwapElementDraw = QuickSortData.isSwapElementDraw;
    (pVector->pQuickSortData[pVector->iVectorSize]).SwapElement.swapIndex1 = QuickSortData.SwapElement.swapIndex1;
    (pVector->pQuickSortData[pVector->iVectorSize]).SwapElement.swapIndex2 = QuickSortData.SwapElement.swapIndex2;

    pVector->iVectorSize++; 
    return(0);
}

void DisplayVector(LP_QUICK_SORT_VECTOR pVector)
{
    size_t iCounter = 0;
    int iCounter2 = 0;

    for(iCounter = 0; iCounter < pVector->iVectorSize ; iCounter++)
    {
        if(NULL != (pVector->pQuickSortData[iCounter]).originalArrayObj.pArr)
        {
            printf("Original :: ");
            for(iCounter2 = 0; iCounter2 < N  ; iCounter2++)
            {
                printf(" %d",(pVector->pQuickSortData[iCounter]).originalArrayObj.pArr[iCounter2]);
            }

            printf("\ti:%d",pVector->pQuickSortData[iCounter].originalArrayObj.i);
            printf("\tj:%d",pVector->pQuickSortData[iCounter].originalArrayObj.j);
            printf("\tpivote:%d",pVector->pQuickSortData[iCounter].originalArrayObj.pivote);
        }

        if(NULL != (pVector->pQuickSortData[iCounter]).arrayObj.pArr)
        {

            printf("A :: ");
            for(iCounter2 = 0; iCounter2 < N ; iCounter2++)
            {
                printf(" %d",(pVector->pQuickSortData[iCounter]).arrayObj.pArr[iCounter2]);
            }

            printf("\ti:%d",pVector->pQuickSortData[iCounter].arrayObj.i);
            printf("\tj:%d",pVector->pQuickSortData[iCounter].arrayObj.j);
            printf("\tpivote:%d",pVector->pQuickSortData[iCounter].arrayObj.pivote);
        }

        printf("\tisSwapElementDraw:%d",pVector->pQuickSortData[iCounter].isSwapElementDraw);
        if(1 == pVector->pQuickSortData[iCounter].isSwapElementDraw)
        {
            printf("\tI1:%d",pVector->pQuickSortData[iCounter].SwapElement.swapIndex1);
            printf("\tI2:%d",pVector->pQuickSortData[iCounter].SwapElement.swapIndex2);
        }
        printf("\n");
    }
}

RET_T DestroyQuicksortVector(LP_QUICK_SORT_VECTOR pVector)
{
    size_t iCounter = 0;

    for(iCounter = 0; iCounter < pVector->iVectorSize-1 ; iCounter++)
    {
        if(NULL != (pVector->pQuickSortData[iCounter]).arrayObj.pArr )
        {
            free((pVector->pQuickSortData[iCounter]).arrayObj.pArr);
            (pVector->pQuickSortData[iCounter]).arrayObj.pArr = NULL;
        }

         if(NULL != (pVector->pQuickSortData[iCounter]).originalArrayObj.pArr )
        {
            free((pVector->pQuickSortData[iCounter]).originalArrayObj.pArr);
            (pVector->pQuickSortData[iCounter]).originalArrayObj.pArr = NULL;
        }
       
    }
    pVector->iVectorSize = 0;
    free(pVector);
    pVector = NULL;
    
    return(0);
}
