#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include "InsertionSortHeader.h"

#pragma comment(lib, "kernel32.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")

#define SUCCESS						1
#define FALSE						0
#define TRUE						1

#define BUFFER_SIZE					256
#define ARRAY_SIZE(X) 				(sizeof(X)/sizeof(X[0]))

#define STATIC_PART_WIDTH_FACTOR	20
#define PAINT_BEGIN_VAL				10

#define FAIL_EXIT_IF(cond, szCaption, szMessage)	do\
													{\
														if((cond))\
														{\
															MessageBox((HWND)NULL, TEXT(szMessage), TEXT(szCaption), MB_ICONERROR);\
															ExitProcess(EXIT_FAILURE);\
														}\
													} while (0);\

/*	Global declarations	*/
LP_INSERTION_SORT_VECTOR g_insertionVector;
int N = 5;
int single_line_height = 100;

int FormatedTextOut(HDC hdc,int x,int y,TCHAR* pszFormat,...)
{
  	TCHAR szBuffer[1024] = {""};
	va_list pArgs;
	va_start(pArgs,pszFormat);

	_vsntprintf(szBuffer, ARRAY_SIZE(szBuffer) ,pszFormat,pArgs);
    TextOut(hdc,x,y,szBuffer,strlen(szBuffer));
    return(0);
}

// Callback
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static int cxClient, cyClient;
	int debugCount = 0;

	int i, x, y, iVertPos, iHorzPos, iPaintBeg, iPaintEnd;

	HDC hdc = NULL;
	PAINTSTRUCT ps;
	SCROLLINFO si;
	RECT rect;
	int iCounter;
    int iCounter2;
    int xPos;
    int yPos;

    int arr[5] = {50, 40, 10, 30, 20};
	switch(uMsg)
	{
		case WM_CREATE:
			g_insertionVector = CreateInsertionSortVector();
            InsertionSortInMemory(arr,N);

			// set_timer(id, millisec timeout)
			break;

		case WM_SIZE:
			cxClient = LOWORD(lParam);
			cyClient = HIWORD(lParam);

			si.cbSize = sizeof(SCROLLINFO);
			si.fMask = SIF_RANGE | SIF_PAGE | SIF_POS;
			si.nMin = 0;
			si.nMax = g_insertionVector->iVectorSize - 1;

			si.nPage = cyClient / single_line_height;
			SetScrollInfo(hWnd, SB_VERT, &si, TRUE);
			break;

		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
			//TextOut(hdc, (cxClient/2) - 50, 25, TEXT("Debugging of Sorting"), strlen(TEXT("Debugging of Sorting")));
			TextOut(hdc, (cxClient/2) - 50, cyClient / 12, TEXT("Debugging of Sorting"), strlen(TEXT("Debugging of Sorting")));
			TextOut(hdc, 25 * (STATIC_PART_WIDTH_FACTOR / 8), cyClient / 2, TEXT("Algorithm Steps"), strlen(TEXT("Algorithm Steps")));
			
			si.fMask = SIF_POS;
			GetScrollInfo(hWnd, SB_VERT, &si);
			iVertPos = si.nPos;

			iPaintBeg = 2;		// TODO: This starting point of paint needs to be adjusted in terms of 'cyClient'. 
			iPaintEnd = iVertPos + ps.rcPaint.bottom;
			
			if(iPaintBeg < 0)
				iPaintBeg = 0;
			if(iPaintEnd >= g_insertionVector->iVectorSize)
				iPaintEnd = g_insertionVector->iVectorSize - 1;

			for(i = iPaintBeg; i <= iPaintEnd; ++i)
			{
				xPos = 200;
	  	       	yPos = (i - iVertPos) * single_line_height;

	   	       	for(iCounter2 = 0; iCounter2 < N ; iCounter2++, xPos+=30)
                {
                    FormatedTextOut(hdc,xPos,yPos," %d ",(g_insertionVector->pInsertionSort[i]).arrayObj.pArr[iCounter2]);
                }
                xPos += 50;
                FormatedTextOut(hdc,xPos,yPos,"\ti : [%d]",g_insertionVector->pInsertionSort[i].arrayObj.i);
                xPos += 50;
                FormatedTextOut(hdc,xPos,yPos,"\tj : [%d]",g_insertionVector->pInsertionSort[i].arrayObj.j);
                xPos += 50;
                FormatedTextOut(hdc,xPos,yPos,"\tkey : [%d]",g_insertionVector->pInsertionSort[i].arrayObj.key);
                xPos += 50;
                FormatedTextOut(hdc,xPos,yPos,"\tCount : %d", debugCount++);
	        }
	        
			EndPaint(hWnd, &ps);
			hdc = NULL;
		 	break;

		case WM_VSCROLL:
			si.cbSize = sizeof(si);
			si.fMask = SIF_ALL;
			GetScrollInfo(hWnd, SB_VERT, &si);

			iVertPos = si.nPos;

			switch(LOWORD(wParam))
			{
				case SB_TOP:
					si.nPos = si.nMin;
					break;

				case SB_BOTTOM:
					si.nPos = si.nMax;
					break;

				case SB_LINEUP:
					si.nPos -= 1;
					break;

				case SB_LINEDOWN:
					si.nPos += 1;
					break;
			}

			si.fMask = SIF_ALL;
			SetScrollInfo(hWnd, SB_VERT, &si, TRUE);
			GetScrollInfo(hWnd, SB_VERT, &si);

			// SP: Coordinates of valid rectangle
			rect.left = cxClient * 0.2;
            rect.top = cyClient * 0.2;
            rect.right = cxClient;
            rect.bottom = cyClient;

			if(si.nPos != iVertPos)
			{
				ScrollWindow(hWnd, 0, single_line_height * (iVertPos - si.nPos), &rect, &rect);
				//ScrollWindow(hWnd, 0, 30 * (iVertPos - si.nPos), NULL, NULL);
				UpdateWindow(hWnd);
			}
			break;

		case WM_DESTROY:
			PostQuitMessage(EXIT_SUCCESS);
			break;
	}

	return(DefWindowProc(hWnd, uMsg, wParam, lParam));
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	static TCHAR szClassName[] = TEXT("The standard window");
	static TCHAR szWindowCaption[] = TEXT("Step by step Sorting");

	HBRUSH hBrush = NULL;
	HCURSOR hCursor = NULL;
	HICON hIcon = NULL;
	HICON hIconSm = NULL;
	HWND hWnd = NULL;

	ATOM bIsWindowClassRegistered = 0;

	WNDCLASSEX wndEx;
	MSG msg;

	ZeroMemory(&wndEx, sizeof(WNDCLASSEX));
	ZeroMemory(&msg, sizeof(MSG));

	hBrush = (HBRUSH)GetStockObject(WHITE_BRUSH);
	FAIL_EXIT_IF(hBrush == NULL, "GetStockObject", "Could not obtain brush");

	hCursor = LoadCursor((HINSTANCE)NULL, IDC_ARROW);
	FAIL_EXIT_IF(hCursor == NULL, "LoadCursor", "Could not load cursor");

	hIcon = LoadIcon((HINSTANCE)NULL, IDI_APPLICATION);
	FAIL_EXIT_IF(hIcon == NULL, "LoadIcon", "Could not load icon");

	hIconSm = LoadIcon((HINSTANCE)NULL, IDI_APPLICATION);
	FAIL_EXIT_IF(hIconSm == NULL, "LoadIcon", "Could not load small icon");

	wndEx.cbSize = sizeof(WNDCLASSEX);
	wndEx.cbClsExtra = 0;
	wndEx.cbWndExtra = 0;
	wndEx.hbrBackground = hBrush;
	wndEx.hCursor = hCursor;
	wndEx.hIcon = hIcon;
	wndEx.hIconSm = hIconSm;
	wndEx.hInstance = hInstance;
	wndEx.lpfnWndProc = WndProc;
	wndEx.lpszClassName = szClassName;
	wndEx.lpszMenuName = NULL;
	wndEx.style = CS_HREDRAW | CS_VREDRAW;

	bIsWindowClassRegistered = RegisterClassEx(&wndEx);
	FAIL_EXIT_IF(bIsWindowClassRegistered == 0, "RegisterClassEx", "Could not register window class");

	hWnd = CreateWindowEx(	WS_EX_APPWINDOW, szClassName, szWindowCaption,
							WS_OVERLAPPEDWINDOW | WS_VSCROLL,
							CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
							(HWND)NULL, (HMENU)NULL, hInstance, NULL );
	FAIL_EXIT_IF(hWnd == NULL, "CreateWindowEx", "Could not create a window");

	ShowWindow(hWnd, nShowCmd);
	UpdateWindow(hWnd);

	while(GetMessage(&msg, (HWND)NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return(msg.wParam);
}




