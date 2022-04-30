#ifndef MASETR_HEADER
#define MASETR_HEADER

#include "ShowAlgorithmHeader.h"
#include "InsertionSortHeader.h"
#include "BubbleSortHeader.h"
#include "CreditScreenHeader.h"
#include "resource.h"

#define FAIL_EXIT_IF(COND, MSG, CAPTION)        do\
                                                {\
                                                    if((COND) == TRUE)\
                                                    {\
                                                        MessageBox(NULL, TEXT(MSG), TEXT(CAPTION), MB_ICONERROR);\
                                                        ExitProcess(EXIT_FAILURE);\
                                                    }\
                                                }\
                                                while(0)

#define ARRAY_SIZE(X) (sizeof(X)/sizeof(X[0]))
#define DIALOG_HEIGHT   600
#define DIALOG_WIDTH    500

#define MAX 5
#define MIN 3


#define SELECT      1
#define UNSELECT    0

#define SET         1
#define UNSET       0

#define WM_USER_1	0x0400
#define SORT_TYPE_COUNT		2
enum sortTypeIndex
{
	INSERTION_SORT,
	//QUICK_SORT,
	BUBBLE_SORT,
	//SELECTION_SORT
};
enum timerID
{
	/*TIMER ID's*/

	TIMER_ID_START = 1000,
	END_SPLASH,
	ID_TIMER_INSERTION,
	ID_TIMER_QUICK,
	ID_TIMER_BUBBLE

};

enum childWindowID
{
	/*WINDOW ID's*/

	CHILD_WINDOW_ID_START = 2000,
	IDB_OPEN_DLG,
	IDB_OPEN_BUTTON ,
	IDB_ADDELE_BUTTON,
	IDB_NEXTVAL_BUTTON,
	IDB_NEXT_STEP_BUTTON,
	ID_CLOSE_DLG,
	ID_RBTN1_DLG,
	ID_RBTN2_DLG,
	ID_RBTN3_DLG,
	ID_RBTN4_DLG,
	ID_EB_VALUE_OF_N,
	ID_EB_ELE_VALUE,

	IDB_SHOW_SORTING,
	ID_SHOW_INSERTION,
	ID_SHOW_QUICK,
	ID_SHOW_BUBBLE,

	ID_SHOW_CREDIT_SCREEN

};

enum menuId {
	 ID_NEW_SORT = 3000,
	ID_NEW_DATA,
	ID_RESTART,
	ID_PAUSE,
	ID_RESUME,
	ID_GET_DATA,
	ID_QUICK_SORT,
	ID_EXIT
};
/**/
extern int g_arr[MAX];
extern int g_CharWidth;
extern int g_sortTypeSelection[SORT_TYPE_COUNT];
extern HWND g_MainHwnd;
extern int N;

/*Utility Functions*/
#define ARRAY_SIZE(X)   (sizeof(X)/sizeof(X[0]))
int FormatedTextOut(HDC hdc, int x, int y, TCHAR* pszFormat, ...);

void PrintPicture(HWND hWnd,HWND *lp_hImage,LPCSTR lv_imagePath,RECT lv_rect);
void DrawLineUtil(HDC hdc,int xsrc,int ysrc,int xdes,int ydes);
void PrintHeader(HDC hdc);


#endif