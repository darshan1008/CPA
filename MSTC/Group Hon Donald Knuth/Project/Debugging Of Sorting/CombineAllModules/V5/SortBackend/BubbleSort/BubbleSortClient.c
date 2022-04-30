#include"BubbleSortHeader.h"

int N;
LP_BUBBLE_SORT_VECTOR g_bubbleVector;
void ShowBubbleDebugging(BUBBLE_DATA bubbleData);

void Output(int *pArr,size_t n);
int main()
{
    int pArr[5] = {20,50,40,10,30};
    int n = 5;
    int iCounter = 0;
    N = 5;
    g_bubbleVector = CreateBubbleSortVector();

    Output(pArr,n);
    BubbleSortInMemory(pArr,n);
    //Output(pArr,n);

    //DisplayBubbleSortVector(g_bubbleVector);

    for(iCounter = 0 ; iCounter < g_bubbleVector->iVectorSize; iCounter++)
    {
       ShowBubbleDebugging(g_bubbleVector->pBubbleSort[iCounter]);
    }

    DestroyBubbleSortVector(g_bubbleVector);
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


void ShowBubbleDebugging(BUBBLE_DATA bubbleData)
{
    int iCounter1;
   
    if(0 != bubbleData.passNumber)
    {
        printf("\n\nPASS %d:\n",bubbleData.passNumber);
    }
    else 
    {
         printf("\nARRAY :: ");
        for(iCounter1 = 0; iCounter1 < N ; iCounter1++)
        {
            printf(" %d",bubbleData.arrayObj.pArr[iCounter1]);
        }
        printf("\t");
        if(bubbleData.swapFlag)
        {
            printf("%d > %d ,SWAP",bubbleData.swapN1,bubbleData.swapN2);
        }
        else
        {
            printf("%d < %d ,OK",bubbleData.swapN1,bubbleData.swapN2);
        }
    }
}

