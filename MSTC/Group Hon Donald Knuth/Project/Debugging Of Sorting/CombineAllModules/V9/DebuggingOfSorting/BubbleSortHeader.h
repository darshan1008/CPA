#ifndef BUBBLE_HEADER
#define BUBBLE_HEADER

#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>
#include<Windows.h>

typedef struct BubbleArray
{
    int *pArr;
    int i;
    int j;
}BUBBLE_ARRAY;

typedef struct RangeOfBubbleAlgLine
{
    int fromLine;
    int toLine;
}BUBBLE_RANGE;

typedef unsigned int FLAG;
typedef struct BubbleSortData
{
    BUBBLE_ARRAY arrayObj;
    BUBBLE_RANGE rangeObj;

    FLAG swapFlag;
    int passNumber;//while showing, if passNumber is 0 then ignore the lable printing
    int swapIndex1;
    int swapIndex2;

    
}BUBBLE_DATA;

#endif


/*vector functionality header*/
#ifndef BUBBLE_VECTOR_HEADER
#define BUBBLE_VECTOR_HEADER
void bubble_sort(int *pArr,int n);
void BubbleSortInMemory(int *pArr,int n);

typedef int RET_T;
typedef struct BubbleSortVector
{
    BUBBLE_DATA* pBubbleSort;
    size_t iVectorSize;  
}BUBBLE_SORT_VECTOR,*LP_BUBBLE_SORT_VECTOR; 

extern int N;
extern LP_BUBBLE_SORT_VECTOR g_bubbleVector;
LP_BUBBLE_SORT_VECTOR CreateBubbleSortVector(void);
RET_T PushBackBubbleSort(LP_BUBBLE_SORT_VECTOR pVector,BUBBLE_DATA Data);
RET_T DestroyBubbleSortVector(LP_BUBBLE_SORT_VECTOR pVector);
void DisplayBubbleSortVector(LP_BUBBLE_SORT_VECTOR pVector);

#endif 

/* UI Functionality */
int DrawBubbleSort(HDC hdc,int xPos,int yPos,BUBBLE_DATA data);
