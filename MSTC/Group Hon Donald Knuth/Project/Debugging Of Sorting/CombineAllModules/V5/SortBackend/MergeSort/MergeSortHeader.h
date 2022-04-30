#ifndef MERGE_HEADER
#define MERGE_HEADER
#include<stdio.h>

void merge(int *pArr,int p,int  q,int r);
void merge_sort(int *pArr,int p,int r);

extern int N;
typedef struct MergeArray
{
    int *pArr;
    int p;
    int q;
    int r;
}MERGE_ARRAY;

typedef struct RangeOfMergeAlgLine
{
    int fromLine;
    int toLine;
}MERGE_RANGE;


typedef struct MergeSortData
{
    MERGE_ARRAY arrayObj;
    MERGE_RANGE rangeObj;
    
}MERGE_DATA;

#endif


/*vector functionality header*/
#ifndef MERGE_VECTOR_HEADER
#define MERGE_VECTOR_HEADER

void MergeSortInMemory(int *pArr,int n);

typedef int RET_T;
typedef struct MergeSortVector
{
    MERGE_DATA* pMergeSort;
    size_t iVectorSize;  
}MERGE_SORT_VECTOR,*LP_MERGE_SORT_VECTOR; 

extern int N;
extern LP_MERGE_SORT_VECTOR g_mergeVector;
LP_MERGE_SORT_VECTOR CreateMergeSortVector(void);
RET_T PushBackMergeSort(LP_MERGE_SORT_VECTOR pVector,MERGE_DATA Data);
RET_T DestroyMergeSortVector(LP_MERGE_SORT_VECTOR pVector);
void DisplayMergeSortVector(LP_MERGE_SORT_VECTOR pVector);

#endif 

/* UI Functionality */

