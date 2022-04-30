#ifndef MASETR_HEADER
#define MASETR_HEADER

#include "ShowAlgorithmHeader.h"
#include "InsertionSortHeader.h"
#include "QuickSortHeaders.h"

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

/*TIMER ID's*/

#define END_SPLASH					101
#define ID_TIMER_INSERTION			1001
#define ID_TIMER_QUICK			1002

/*WINDOW ID's*/

#define IDB_OPEN_DLG			1003
#define IDB_OPEN_BUTTON         1010
#define IDB_ADDELE_BUTTON       1011
#define IDB_NEXTVAL_BUTTON      1012
#define ID_CLOSE_DLG            1013
#define ID_RBTN1_DLG            1014
#define ID_RBTN2_DLG            1015
#define ID_EB_VALUE_OF_N		1016
#define ID_EB_ELE_VALUE         1017

#define IDB_SHOW_SORTING		1018
#define ID_SHOW_INSERTION		1019
#define ID_SHOW_QUICK			1020
#define ID_SHOW_CREDIT_SCREEN	1021





/**/
extern int g_arr[MAX];
extern int g_CharWidth;
extern int g_sortTypeSelection[2];
extern HWND g_MainHwnd;
extern int N;
#endif