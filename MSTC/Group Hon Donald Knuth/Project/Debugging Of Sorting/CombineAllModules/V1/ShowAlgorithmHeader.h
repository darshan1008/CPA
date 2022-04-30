#ifndef SHOW_ALGORITHM_HEADER
#define  SHOW_ALGORITHM_HEADER
#include<Windows.h>
#include<Windows.h>
#include <stdio.h>

#pragma comment(lib,"gdi32.lib")
#pragma comment(lib,"user32.lib")
#pragma comment(lib,"kernel32.lib")

//------------------------------------------------------------------------------------------------------------------
/*	ALL MACRO'S   */

#define SUCCESS 1 
#define X_OFFSET_1 7
#define FAIL_EXIT_IF(COND, MSG, CAPTION)        do\
                                                {\
                                                    if((COND) == TRUE)\
                                                    {\
                                                        MessageBox(NULL, TEXT(MSG), TEXT(CAPTION), MB_ICONERROR);\
                                                        ExitProcess(EXIT_FAILURE);\
                                                    }\
                                                }\
                                                while(0)
//-------------------------------------------------------------------------------------------------------------------
/*	STRINGVECTOR	*/ 
typedef struct tagStringVector
{
    CHAR** ppString;
    int iVectorSize;  
}STRINGVECTOR, *PSTRINGVECTOR, *NPSTRINGVECTOR, *LPSTRINGVECTOR; 


//---------------------------------------------------------------------------------------------------------------------
/* Global Handles */ 

extern LPTSTR glpCmdLine ; 
extern PSTRINGVECTOR gpStrVec;

//------------------------------------------------------------------------------------------------------------------
/*	FUNCTION DECLARATIONS	*/
PSTRINGVECTOR CreateStringVector(void);
int PushBack(PSTRINGVECTOR pStrVec, CHAR* pNewString); 
int DestroyStringVector(PSTRINGVECTOR pStrVec); 
void ReleaseAll(void);

LPVOID Xcalloc(size_t cbSize, size_t cbSizePerElement); 
PSTRINGVECTOR ReadFileInMemory(LPTSTR lpFileName);

void DrawLine(HDC,int,int,int,int);
void PaintDesign(HDC,int,int);
void PrintAlgorithm(HDC,int,int);
int PrintArrow(HDC,int,int,int,int);

#endif