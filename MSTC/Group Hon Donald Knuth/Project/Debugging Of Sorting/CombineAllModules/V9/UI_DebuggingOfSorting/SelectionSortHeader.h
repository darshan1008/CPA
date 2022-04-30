#ifndef SELECTION_HEADER
#define SELECTION_HEADER

#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>
#include<Windows.h>

typedef struct SelectionArray
{
    int *pArr;
    int i;
    int j;
}SELECTION_ARRAY;

typedef struct RangeOfSelectionAlgLine
{
    int fromLine;
    int toLine;
}SELECTION_RANGE;

typedef unsigned int FLAG;
typedef struct SelectionSortData
{
    SELECTION_ARRAY arrayObj;
    SELECTION_RANGE rangeObj;

    int smallEleIndex;
    FLAG swapFlag;
    int swapIndex;

    
}SELECTION_DATA;

#endif


/*vector functionality header*/
#ifndef SELECTION_VECTOR_HEADER
#define SELECTION_VECTOR_HEADER
void selection_sort(int *pArr,int n);
void SelectionSortInMemory(int *pArr,int n);

typedef int RET_T;
typedef struct SelectionSortVector
{
    SELECTION_DATA* pSelectionSort;
    size_t iVectorSize;  
}SELECTION_SORT_VECTOR,*LP_SELECTION_SORT_VECTOR; 

extern int N;
extern LP_SELECTION_SORT_VECTOR g_selectionVector;
LP_SELECTION_SORT_VECTOR CreateSelectionSortVector(void);
RET_T PushBackSelectionSort(LP_SELECTION_SORT_VECTOR pVector,SELECTION_DATA Data);
RET_T DestroySelectionSortVector(LP_SELECTION_SORT_VECTOR pVector);
void DisplaySelectionSortVector(LP_SELECTION_SORT_VECTOR pVector);

#endif 

/* UI Functionality */
int DrawSelectionSort(HDC hdc,int xPos,int yPos,SELECTION_DATA data);
