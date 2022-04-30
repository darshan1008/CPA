#include"SelectionSortHeader.h"

LP_SELECTION_SORT_VECTOR g_selectionVector;

void copy_array(SELECTION_ARRAY srcObj,SELECTION_ARRAY *destObj,int n);

void SelectionSortInMemory(int *pArr,int n)
{
	int min;
    
    SELECTION_DATA objData;
    SELECTION_ARRAY arrObj; 
    arrObj.pArr = pArr;
	for(arrObj.i = 0; arrObj.i< n ; arrObj.i++)
	{
        memset(&objData,0,sizeof(SELECTION_DATA));
		min = arrObj.i;
		for(arrObj.j = arrObj.i+1 ; arrObj.j<n ; arrObj.j++)
		{
			if(arrObj.pArr[arrObj.j] < arrObj.pArr[min])
			{
				min = arrObj.j;
			}
		}
		//printf("%d is smallest\n",arrObj.pArr[min]);
        objData.smallEleIndex = min;
        copy_array(arrObj,&(objData.arrayObj),n);
		if(min != arrObj.i)
		{
			//printf("swap index : %d <-> %d\n",arrObj.i,min);
            objData.swapIndex = arrObj.i;
            objData.swapFlag = TRUE;
			arrObj.j = arrObj.pArr[arrObj.i];
			arrObj.pArr[arrObj.i] = arrObj.pArr[min];
			arrObj.pArr[min] = arrObj.j;
		}
        PushBackSelectionSort(g_selectionVector,objData);
	}
}

void copy_array(SELECTION_ARRAY srcObj,SELECTION_ARRAY *destObj,int n)
{
    int iCounter = 0;

    destObj->pArr = (int *)malloc(sizeof(int)*n);
    
    for(iCounter = 0; iCounter < n ; iCounter++)
    {
        destObj->pArr[iCounter] = srcObj.pArr[iCounter];
    }
    destObj->i = srcObj.i; 
    destObj->j = srcObj.j; 
}

LP_SELECTION_SORT_VECTOR CreateSelectionSortVector(void)
{
    LP_SELECTION_SORT_VECTOR pSelectionVector = NULL;
    pSelectionVector = (LP_SELECTION_SORT_VECTOR)malloc(sizeof(SELECTION_SORT_VECTOR));
    if(NULL == pSelectionVector)
    {
        exit(-1);
    }
    pSelectionVector->pSelectionSort = NULL;
    pSelectionVector->iVectorSize = 0;
    printf("SIZE(SELECTION_DATA):[%d]\n",sizeof(SELECTION_DATA));
    return(pSelectionVector);
}

RET_T PushBackSelectionSort(LP_SELECTION_SORT_VECTOR pVector,SELECTION_DATA Data)
{
    pVector->pSelectionSort = (SELECTION_DATA*)realloc(pVector->pSelectionSort,(pVector->iVectorSize+1) * sizeof(SELECTION_DATA));
   if(NULL == pVector->pSelectionSort)
    {
        puts("MEMORY ERROR");
        exit(-1);
    }
    
    //printf("pp:[%ld]\n",pVector->pSelectionSort);
    //printf("pp[%d]:[%ld]\n",pVector->iVectorSize,&(pVector->pSelectionSort[pVector->iVectorSize]));

    (pVector->pSelectionSort[pVector->iVectorSize]).arrayObj.pArr = Data.arrayObj.pArr;
    (pVector->pSelectionSort[pVector->iVectorSize]).arrayObj.i = Data.arrayObj.i;
    (pVector->pSelectionSort[pVector->iVectorSize]).arrayObj.j = Data.arrayObj.j;

    (pVector->pSelectionSort[pVector->iVectorSize]).rangeObj.fromLine = Data.rangeObj.fromLine;
    (pVector->pSelectionSort[pVector->iVectorSize]).rangeObj.toLine = Data.rangeObj.toLine;

    (pVector->pSelectionSort[pVector->iVectorSize]).swapFlag = Data.swapFlag;
    (pVector->pSelectionSort[pVector->iVectorSize]).swapIndex = Data.swapIndex;
    (pVector->pSelectionSort[pVector->iVectorSize]).smallEleIndex = Data.smallEleIndex;
    
    pVector->iVectorSize++;
    return(0);
}

RET_T DestroySelectionSortVector(LP_SELECTION_SORT_VECTOR pVector)
{
    size_t iCounter = 0;
    if(NULL == pVector)
    {
        return (-1);
    }
    for(iCounter = 0; iCounter < pVector->iVectorSize-1 ; iCounter++)
    {
        if(NULL != (pVector->pSelectionSort[iCounter]).arrayObj.pArr )
        {
            free((pVector->pSelectionSort[iCounter]).arrayObj.pArr);
            (pVector->pSelectionSort[iCounter]).arrayObj.pArr = NULL;
        }
    }
    pVector->iVectorSize = 0;
    free(pVector);
    pVector = NULL;
    
    return(0);
}

void DisplaySelectionSortVector(LP_SELECTION_SORT_VECTOR pVector)
{
    size_t iCounter = 0;
    int iCounter2 = 0;
    for(iCounter = 0; iCounter < pVector->iVectorSize ; iCounter++)
    {
        printf("\nA:: ");
        for(iCounter2 = 0; iCounter2 < N ; iCounter2++)
        {
            printf(" %d",(pVector->pSelectionSort[iCounter]).arrayObj.pArr[iCounter2]);
        }

        printf("\ti:%d",pVector->pSelectionSort[iCounter].arrayObj.i);
        //printf("\tj:%d",pVector->pSelectionSort[iCounter].arrayObj.j);

        //printf("\tsmallele:%d",(pVector->pSelectionSort[iCounter]).arrayObj.pArr[pVector->pSelectionSort[iCounter].smallEleIndex]);
        printf("\tsmallele: %d",pVector->pSelectionSort[iCounter].smallEleIndex);
        printf("\tswap: %d",pVector->pSelectionSort[iCounter].swapIndex);
        printf("\tswapFlag: %d",pVector->pSelectionSort[iCounter].swapFlag);

    }
}
