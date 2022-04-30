#include"BubbleSortHeader.h"


void copy_array(BUBBLE_ARRAY srcObj,BUBBLE_ARRAY *destObj,int n);

void BubbleSortInMemory(int *pArr,int n)
{
	int temp = 0;
	int no_of_swaps = 0;
    int pass_counter = 1;

    BUBBLE_DATA obj;
    BUBBLE_ARRAY arrObj;
    int debugCounter = 0;

    arrObj.pArr = pArr;
    arrObj.i = 0;
    arrObj.j = 0;

    memset(&obj,0,sizeof(obj));
    obj.rangeObj.fromLine = 0; 
    obj.rangeObj.toLine = 0;
    obj.passNumber = 0;
    copy_array(arrObj,&(obj.arrayObj),n);
    //PushBackBubbleSort(g_bubbleVector,obj);
    
	for(arrObj.i=0; arrObj.i<n-1; arrObj.i++)
	{
        memset(&obj,0,sizeof(obj));
        obj.passNumber = pass_counter;
        copy_array(arrObj,&(obj.arrayObj),n);
        PushBackBubbleSort(g_bubbleVector,obj);

		no_of_swaps = 0;
		for(arrObj.j=0; arrObj.j<n-1-arrObj.i; arrObj.j++)
		{
            memset(&obj,0,sizeof(obj));
            obj.passNumber = 0;
            obj.swapN1 = arrObj.pArr[arrObj.j];
            obj.swapN2 = arrObj.pArr[arrObj.j+1];

			//if(arrObj.pArr[arrObj.j] > arrObj.pArr[arrObj.j+1])
            if(obj.swapN1 > obj.swapN2)
			{
				
                
                obj.rangeObj.fromLine = 0; 
                obj.rangeObj.toLine = 0;
                obj.swapFlag = 1;
                copy_array(arrObj,&(obj.arrayObj),n);
                PushBackBubbleSort(g_bubbleVector,obj);
                temp = arrObj.pArr[arrObj.j];
				arrObj.pArr[arrObj.j] = arrObj.pArr[arrObj.j+1];
				arrObj.pArr[arrObj.j+1] = temp;
				++no_of_swaps;
			}
            else
            {
                obj.rangeObj.fromLine = 0; 
                obj.rangeObj.toLine = 0;
                obj.swapFlag = 0;
                copy_array(arrObj,&(obj.arrayObj),n);
                PushBackBubbleSort(g_bubbleVector,obj);  
            }
		}
 
		if(0 == no_of_swaps)
        {
            
			break;
        }
         pass_counter++;
	}

    memset(&obj,0,sizeof(obj));
    obj.rangeObj.fromLine = 0; 
    obj.rangeObj.toLine = 0;
    obj.swapFlag = 0;
    obj.passNumber = 0;
    copy_array(arrObj,&(obj.arrayObj),n);
    PushBackBubbleSort(g_bubbleVector,obj);  
}

void copy_array(BUBBLE_ARRAY srcObj,BUBBLE_ARRAY *destObj,int n)
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

LP_BUBBLE_SORT_VECTOR CreateBubbleSortVector(void)
{
    LP_BUBBLE_SORT_VECTOR pBubbleVector = NULL;
    pBubbleVector = (LP_BUBBLE_SORT_VECTOR)malloc(sizeof(BUBBLE_SORT_VECTOR));
    if(NULL == pBubbleVector)
    {
        exit(-1);
    }
    pBubbleVector->pBubbleSort = NULL;
    pBubbleVector->iVectorSize = 0;
    printf("SIZE(BUBBLE_DATA):[%d]\n",sizeof(BUBBLE_DATA));
    return(pBubbleVector);
}

RET_T PushBackBubbleSort(LP_BUBBLE_SORT_VECTOR pVector,BUBBLE_DATA Data)
{
    pVector->pBubbleSort = (BUBBLE_DATA*)realloc(pVector->pBubbleSort,(pVector->iVectorSize+1) * sizeof(BUBBLE_DATA));
   if(NULL == pVector->pBubbleSort)
    {
        puts("MEMORY ERROR");
        exit(-1);
    }
    
    //printf("pp:[%ld]\n",pVector->pBubbleSort);
    //printf("pp[%d]:[%ld]\n",pVector->iVectorSize,&(pVector->pBubbleSort[pVector->iVectorSize]));

    (pVector->pBubbleSort[pVector->iVectorSize]).arrayObj.pArr = Data.arrayObj.pArr;
    (pVector->pBubbleSort[pVector->iVectorSize]).arrayObj.i = Data.arrayObj.i;
    (pVector->pBubbleSort[pVector->iVectorSize]).arrayObj.j = Data.arrayObj.j;

    (pVector->pBubbleSort[pVector->iVectorSize]).rangeObj.fromLine = Data.rangeObj.fromLine;
    (pVector->pBubbleSort[pVector->iVectorSize]).rangeObj.toLine = Data.rangeObj.toLine;

    (pVector->pBubbleSort[pVector->iVectorSize]).swapFlag = Data.swapFlag;
    (pVector->pBubbleSort[pVector->iVectorSize]).swapN1 = Data.swapN1;
    (pVector->pBubbleSort[pVector->iVectorSize]).swapN2 = Data.swapN2;
    (pVector->pBubbleSort[pVector->iVectorSize]).passNumber = Data.passNumber;
    
    pVector->iVectorSize++;
    return(0);
}

RET_T DestroyBubbleSortVector(LP_BUBBLE_SORT_VECTOR pVector)
{
    size_t iCounter = 0;
    if(NULL == pVector)
    {
        return (-1);
    }
    for(iCounter = 0; iCounter < pVector->iVectorSize-1 ; iCounter++)
    {
        if(NULL != (pVector->pBubbleSort[iCounter]).arrayObj.pArr )
        {
            free((pVector->pBubbleSort[iCounter]).arrayObj.pArr);
            (pVector->pBubbleSort[iCounter]).arrayObj.pArr = NULL;
        }
    }
    pVector->iVectorSize = 0;
    free(pVector);
    pVector = NULL;
    
    return(0);
}

void DisplayBubbleSortVector(LP_BUBBLE_SORT_VECTOR pVector)
{
    size_t iCounter = 0;
    int iCounter2 = 0;
    for(iCounter = 0; iCounter < pVector->iVectorSize ; iCounter++)
    {
        printf("A:: ");
        for(iCounter2 = 0; iCounter2 < N ; iCounter2++)
        {
            printf(" %d",(pVector->pBubbleSort[iCounter]).arrayObj.pArr[iCounter2]);
        }

        printf("\ti:%d",pVector->pBubbleSort[iCounter].arrayObj.i);
        printf("\tj:%d",pVector->pBubbleSort[iCounter].arrayObj.j);
    }
}

