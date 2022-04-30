
#include"InsertionSortHeader.h"

void copy_array(INSERTION_ARRAY srcObj,INSERTION_ARRAY *destObj,int n);

void InsertionSortInMemory(int *pArr,int n)
{
    INSERTIONSORTDATA obj;
    INSERTION_ARRAY arrObj;
    int debugCounter = 0;
    arrObj.pArr = pArr;
    arrObj.i = 0;
    arrObj.j = 0;
    arrObj.key = 0;
    obj.rangeObj.fromLine = 0; 
    obj.rangeObj.toLine = 0;
    memset(&obj,0,sizeof(obj));
    copy_array(arrObj,&(obj.arrayObj),n);
    PushBackInsertionSort(g_insertionVector,obj);
    
	for(arrObj.j = 1; arrObj.j < n; arrObj.j++)
	{
		arrObj.key = pArr[arrObj.j];
		arrObj.i = arrObj.j-1;
        
        obj.rangeObj.fromLine = 1 ;
        obj.rangeObj.toLine = 3 ;
        copy_array(arrObj,&(obj.arrayObj),n);
        PushBackInsertionSort(g_insertionVector,obj);
        memset(&obj,0,sizeof(obj));
    
		while( arrObj.i > -1  && arrObj.pArr[arrObj.i] > arrObj.key)
		{
   			arrObj.pArr[arrObj.i+1] = arrObj.pArr[arrObj.i];

            obj.exchangeFlag = ON;
            obj.exchangeIndex1 = arrObj.i+1;
            obj.exchangeIndex2 = arrObj.i;

            obj.rangeObj.fromLine = 5;
            obj.rangeObj.toLine = 7;
            
            arrObj.i = arrObj.i-1;

            copy_array(arrObj,&obj.arrayObj,n);
            PushBackInsertionSort(g_insertionVector,obj);
            memset(&obj,0,sizeof(obj));
		}

		arrObj.pArr[arrObj.i+1] = arrObj.key;
        obj.exchangeFlag = ON;
        obj.exchangeIndex1 = arrObj.i+1;
        obj.exchangeIndex2 = arrObj.j;
        obj.sortedUnsortedFlag = ON;
        obj.seperatorIndex = (arrObj.j-1);
        
        obj.rangeObj.fromLine = 8; 
        obj.rangeObj.toLine = 8;
        copy_array(arrObj,&obj.arrayObj,n);
        PushBackInsertionSort(g_insertionVector,obj);
        memset(&obj,0,sizeof(obj));
	}

    obj.sortedUnsortedFlag = ON;
    obj.seperatorIndex = (arrObj.j-1);
    obj.rangeObj.fromLine = 0; 
    obj.rangeObj.toLine = 0;
    copy_array(arrObj,&obj.arrayObj,n);
    PushBackInsertionSort(g_insertionVector,obj);
    memset(&obj,0,sizeof(obj));
}

void copy_array(INSERTION_ARRAY srcObj,INSERTION_ARRAY *destObj,int n)
{
    int iCounter = 0;

    destObj->pArr = (int *)malloc(sizeof(int)*n);
    
    for(iCounter = 0; iCounter < n ; iCounter++)
    {
        destObj->pArr[iCounter] = srcObj.pArr[iCounter];
    }
    destObj->i = srcObj.i; 
    destObj->j = srcObj.j; 
    destObj->key = srcObj.key; 
}


/*Vector functionality*/

LP_INSERTION_SORT_VECTOR CreateInsertionSortVector(void)
{
    LP_INSERTION_SORT_VECTOR pInsertionVector = NULL;
    pInsertionVector = (LP_INSERTION_SORT_VECTOR)malloc(sizeof(INSERTION_SORT_VECTOR));
    if(NULL == pInsertionVector)
    {
        exit(-1);
    }
    pInsertionVector->pInsertionSort = NULL;
    pInsertionVector->iVectorSize = 0;
    printf("SIZE(INSERTIONSORTDATA):[%d]\n",sizeof(INSERTIONSORTDATA));
    return(pInsertionVector);
}

RET_T PushBackInsertionSort(LP_INSERTION_SORT_VECTOR pVector,INSERTIONSORTDATA InsertionSortData)
{
    //printf("PushBackInsertionSort - 0,pp:[%d] size:[%d]\n",pVector->pInsertionSort,pVector->iVectorSize);
    pVector->pInsertionSort = (INSERTIONSORTDATA*)realloc(pVector->pInsertionSort,(pVector->iVectorSize+1) * sizeof(INSERTIONSORTDATA));
    //puts("before NULL checking");
   if(NULL == pVector->pInsertionSort)
    {
        puts("MEMORY ERROR");
        exit(-1);
    }
    
    //printf("pp:[%ld]\n",pVector->pInsertionSort);
    //printf("pp[%d]:[%ld]\n",pVector->iVectorSize,&(pVector->pInsertionSort[pVector->iVectorSize]));

    (pVector->pInsertionSort[pVector->iVectorSize]).arrayObj.pArr = InsertionSortData.arrayObj.pArr;
    (pVector->pInsertionSort[pVector->iVectorSize]).arrayObj.i = InsertionSortData.arrayObj.i;
    (pVector->pInsertionSort[pVector->iVectorSize]).arrayObj.j = InsertionSortData.arrayObj.j;
    (pVector->pInsertionSort[pVector->iVectorSize]).arrayObj.key = InsertionSortData.arrayObj.key;

    (pVector->pInsertionSort[pVector->iVectorSize]).exchangeFlag = InsertionSortData.exchangeFlag;
    (pVector->pInsertionSort[pVector->iVectorSize]).exchangeIndex1 = InsertionSortData.exchangeIndex1;
    (pVector->pInsertionSort[pVector->iVectorSize]).exchangeIndex2 = InsertionSortData.exchangeIndex2;

    (pVector->pInsertionSort[pVector->iVectorSize]).sortedUnsortedFlag = InsertionSortData.sortedUnsortedFlag;
    (pVector->pInsertionSort[pVector->iVectorSize]).seperatorIndex = InsertionSortData.seperatorIndex;

    (pVector->pInsertionSort[pVector->iVectorSize]).hPen = InsertionSortData.hPen;
    (pVector->pInsertionSort[pVector->iVectorSize]).hBrush = InsertionSortData.hBrush;
    (pVector->pInsertionSort[pVector->iVectorSize]).hMyFont_1 = InsertionSortData.hMyFont_1;
    
    (pVector->pInsertionSort[pVector->iVectorSize]).rangeObj.toLine = InsertionSortData.rangeObj.toLine;
    (pVector->pInsertionSort[pVector->iVectorSize]).rangeObj.fromLine = InsertionSortData.rangeObj.fromLine;

    pVector->iVectorSize++;
 
    return(0);
}

void DisplayInsertionSortVector(LP_INSERTION_SORT_VECTOR pVector)
{
    size_t iCounter = 0;
    int iCounter2 = 0;
    for(iCounter = 0; iCounter < pVector->iVectorSize ; iCounter++)
    {
        printf("A:: ");
        for(iCounter2 = 0; iCounter2 < N ; iCounter2++)
        {
            printf(" %d",(pVector->pInsertionSort[iCounter]).arrayObj.pArr[iCounter2]);
        }

        printf("\ti:%d",pVector->pInsertionSort[iCounter].arrayObj.i);
        printf("\tj:%d",pVector->pInsertionSort[iCounter].arrayObj.j);
        printf("\tkey:%d",pVector->pInsertionSort[iCounter].arrayObj.key);
        if(ON == pVector->pInsertionSort[iCounter].exchangeFlag)
        {
            printf("\tSWAP index : %d-%d",
                            pVector->pInsertionSort[iCounter].exchangeIndex1,
                            pVector->pInsertionSort[iCounter].exchangeIndex2
                            );
        }

        if(ON == pVector->pInsertionSort[iCounter].sortedUnsortedFlag)
        {
            printf("\n\t\tSORTED:[0-%d],UNSOERTED:[%d-%d]",
                            pVector->pInsertionSort[iCounter].seperatorIndex,
                            pVector->pInsertionSort[iCounter].seperatorIndex+1,
                            N-1
                            );
        }
        printf("\n");

    }
}

RET_T DestroyInsertionSortVector(LP_INSERTION_SORT_VECTOR pVector)
{
    size_t iCounter = 0;
    if(NULL == pVector)
    {
        return (-1);
    }
    for(iCounter = 0; iCounter < pVector->iVectorSize-1 ; iCounter++)
    {
        if(NULL != (pVector->pInsertionSort[iCounter]).arrayObj.pArr )
        {
            free((pVector->pInsertionSort[iCounter]).arrayObj.pArr);
            (pVector->pInsertionSort[iCounter]).arrayObj.pArr = NULL;
        }
    }
    pVector->iVectorSize = 0;
    free(pVector);
    pVector = NULL;
    
    return(0);
}
