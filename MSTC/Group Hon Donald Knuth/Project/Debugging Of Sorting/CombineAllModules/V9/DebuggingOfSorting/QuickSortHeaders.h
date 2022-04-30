#ifndef QUICKSORT_HEADER
#define QUICKSORT_HEADER
#include <Windows.h>
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>


#define MAX 	5
#define MIN		3

#define ON 		1
#define OFF 	0

#define FALSE 	0
#define TRUE 	1

typedef unsigned int QUICK_FLAG;
typedef unsigned int INDEX;
extern int isNewIteration;
typedef struct QuickSortArray
{
    int *pArr;
    int i;
    int j;
    int pivote;
}QUICKSORT_ARRAY;

struct SwapElementDraw;

struct SwapElementDraw
{
	INDEX swapIndex1;
	INDEX swapIndex2;
};

typedef struct RangeOfQuickAlgLine
{
    int fromLine;
    int toLine;
};



typedef struct QuickSortData
{
	QUICKSORT_ARRAY arrayObj;
	QUICKSORT_ARRAY originalArrayObj;

	struct RangeOfQuickAlgLine rangeObj;

	//for simple draw all flags will OFF 

	//flag for draw index
	QUICK_FLAG isIndexDraw;

	//flag for draw condition
	QUICK_FLAG isConditionDraw;
	QUICK_FLAG isSwapElementDraw;
	QUICK_FLAG isConditionSatisfied;

	//flag for draw swapping element
	struct SwapElementDraw SwapElement;
	QUICK_FLAG isNewIteration;

}QUICKSORTDATA;


#endif
/*---------------------------- QUICKSORT VECTOR HEADER ----------------------------------------*/

#ifndef QUICKSORT_VECTOR_HEADER
#define QUICKSORT_VECTOR_HEADER

typedef int RET_T;
extern int N;


typedef struct QuickSortVector
{
    QUICKSORTDATA* pQuickSortData;
    size_t iVectorSize;  
}QUICKSORTVECTOR,*LP_QUICK_SORT_VECTOR; 

extern LP_QUICK_SORT_VECTOR g_pQuicksortVector;

LP_QUICK_SORT_VECTOR CreateQuicksortVector(void);
RET_T PushBackQuick(LP_QUICK_SORT_VECTOR pVector,QUICKSORTDATA InsertionSortData);
void DisplayVector(LP_QUICK_SORT_VECTOR pVector);
RET_T DestroyQuicksortVector(LP_QUICK_SORT_VECTOR pVector);

int partition(int *pArr,int p,int r);
void quick_sort(int *pArr,int p,int r);
void copy_array(QUICKSORT_ARRAY srcObj,QUICKSORT_ARRAY *destObj,int n);
void QuickSortInMemory(int* arr, size_t n);
#endif

extern enum ArrowType;
/* Drawing Quick Sort On UI*/
void AddArrow(HDC hdc, int StartX, int StartY,enum ArrowType type);
void AddComparisonOperator(HDC hdc, int startX, int startY);
void AddIndexForArrayBoxes(HDC hdc,int left, int top, int numberOfElements);
void AddDottedLineForLoop(HDC hdc,int x,int y,int CurrentLoop);
void AddSingleBox(HDC hdc, int left, int top, int penstyle, bool bHasStyle);
void SwapNumbers(HDC hdc, int left, int top, int numberOfElements, struct QuickSortData quicksortstruc);
void SetBoxesForArray(HDC hdc,int left, int top, int numberOfElements, int iSwap, int jSwap,int *pArr);
void SetSidePane(HDC hdc, int left, int top,int pivote, int i,int j);
int DrawQuickSort(int CurrentXPos, int CurrentYPos, HDC hdc, struct QuickSortData quicksortstruc);
void DisplayQuicksort(HDC hdc,int xPos,int yPos,QUICKSORTDATA dataObj);

