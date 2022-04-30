
#ifndef INSERTION_HEADER
#define INSERTION_HEADER 
#include <Windows.h>
#include <stdio.h>
#include<tchar.h>
#include <stdlib.h> 
#include <assert.h>

//#include"DebuggingOfSortingHeader.h"




#define ON          1
#define OFF         0

typedef int FLAG;
extern int N;
typedef struct InsertionArray
{
    int *pArr;
    int i;
    int j;
    int key;
}INSERTION_ARRAY;

typedef struct RangeOfAlgLine
{
    int fromLine;
    int toLine;
}RANGE;


typedef struct InsertionSortData
{
    INSERTION_ARRAY arrayObj;
    RANGE rangeObj;

    FLAG exchangeFlag;
    int exchangeIndex1;
    int exchangeIndex2;

    FLAG sortedUnsortedFlag;
    int seperatorIndex;     // this index is included into sorted array
                            // i.e [0:i]-> SORTED, [i+1:N]->UNSORTED
    HPEN hPen;
    HBRUSH hBrush;
    HFONT hMyFont_1;
    //CHAR* label;

}INSERTIONSORTDATA;

#endif


/*vector functionality header*/

#ifndef INSERTIONVECTOR_HEADER
#define INSERTIONVECTOR_HEADER

void InsertionSortInMemory(int *pArr,int n);


typedef int RET_T;
typedef struct InsertionSortVector
{
    INSERTIONSORTDATA* pInsertionSort;
    size_t iVectorSize;  
}INSERTION_SORT_VECTOR,*LP_INSERTION_SORT_VECTOR; 

extern int N;
extern LP_INSERTION_SORT_VECTOR g_insertionVector;
LP_INSERTION_SORT_VECTOR CreateInsertionSortVector(void);
RET_T PushBackInsertionSort(LP_INSERTION_SORT_VECTOR pVector,INSERTIONSORTDATA Data);
RET_T DestroyInsertionSortVector(LP_INSERTION_SORT_VECTOR pVector);
void DisplayInsertionSortVector(LP_INSERTION_SORT_VECTOR pVector);

#endif



/* UI Functionality */

extern CHAR* label[4];// = {TEXT("Given Array"),TEXT("i"),TEXT("j"),TEXT("Key")};
//CHAR* label[] = {TEXT("Given Array"),TEXT("Iteration - "),TEXT("0"),TEXT("1"),TEXT("2"),TEXT("3"),TEXT("4"),TEXT("Key"),TEXT("i"),TEXT("j")};


/* color function declarations */
void sortedColor(HDC hdc, INSERTIONSORTDATA insertionDataObj);
void unsortedColor(HDC hdc,INSERTIONSORTDATA insertionDataObj);
void exchangeColor(HDC hdc,INSERTIONSORTDATA insertionDataObj);
void notexchangeColor(HDC hdc,INSERTIONSORTDATA insertionDataObj);
void rectangleBordercolorAndFillColorWhite(HDC hdc,INSERTIONSORTDATA insertionDataObj);
void rectangleBordercolorAndFillColorMagenta(HDC hdc,INSERTIONSORTDATA insertionDataObj);
void ellipseYelloColor(HDC hdc,INSERTIONSORTDATA insertionDataObj);
void ellipseMagentaColor(HDC hdc,INSERTIONSORTDATA insertionDataObj);
void ellipseRedColor(HDC hdc,INSERTIONSORTDATA insertionDataObj);
void ellipseWhiteColor(HDC hdc,INSERTIONSORTDATA insertionDataObj);
void textColor(HDC hdc,INSERTIONSORTDATA insertionDataObj);
void labelColor(HDC hdc,INSERTIONSORTDATA insertionDataObj);
void noteColor(HDC hdc,INSERTIONSORTDATA insertionDataObj);
void counterF(HDC hdc, int xPos, int yPos);

/*InsertionSort function declaration */
void DrawInsertionSort(HDC hdc,int xPos, int yPos, INSERTIONSORTDATA insertionDataObj);
void header(HDC hdc, int cxClient,int cyClient,INSERTIONSORTDATA insertionData);
int FormatedTextOut(HDC hdc,int x,int y,TCHAR* ap_format,...);
int getHeightSquare();

void DrawInsertionTextOut(HDC hdc,int xPos,int yPos,INSERTIONSORTDATA insertObj);
