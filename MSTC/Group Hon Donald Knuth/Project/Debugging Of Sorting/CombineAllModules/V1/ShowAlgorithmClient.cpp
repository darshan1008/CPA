//#include"DebuggingOfSortingHeader.h"
#include "ShowAlgorithmHeader.h"
#include "InsertionSortHeader.h"



LPTSTR glpCmdLine = NULL; 
PSTRINGVECTOR gpStrVec = NULL;

LP_INSERTION_SORT_VECTOR g_insertionVector;

LRESULT CALLBACK WndProc(HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM lParam);

//-----------------------------------------------------------------------------------------------------------------

/*FUNCTION DEFINITIONS*/
int g_screen_width;
int g_screen_height;
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd)
{
    static TCHAR szClassName[] = TEXT("Module 2");
    static TCHAR szWindowCaption[] = TEXT("Module 2");

    HBRUSH hBrush = NULL;
    HCURSOR hCursor = NULL;
    HICON hIcon  = NULL;
    HICON hIconSm = NULL;
    HWND hwnd = NULL;

    MSG msg;
    WNDCLASSEX wndEx;

    ZeroMemory(&wndEx,sizeof(WNDCLASSEX));
    ZeroMemory(&wndEx,sizeof(MSG));

    glpCmdLine = lpCmdLine; 

    hBrush = (HBRUSH)GetStockObject(WHITE_BRUSH);
    if (NULL == hBrush)
    {
        MessageBox((HWND)NULL,TEXT("Could not obtain brush"),TEXT("GetStockObject"),MB_ICONERROR);
        return (EXIT_FAILURE);
    }

    hCursor = LoadCursor((HINSTANCE)NULL,IDC_ARROW);
    if(NULL == hCursor){
        MessageBox((HWND)NULL,TEXT("Could not obtain cursor"),TEXT("LoadCursor"),MB_ICONERROR);
        return(EXIT_FAILURE);
    }

    hIcon = LoadIcon((HINSTANCE)NULL,IDI_APPLICATION);
    if(NULL == hIcon){
        MessageBox((HWND)NULL,TEXT("Could not obtain icon"),TEXT("LoadIcon"),MB_ICONERROR);
        return(EXIT_FAILURE);
    }

    hIconSm = LoadIcon((HINSTANCE)NULL,IDI_APPLICATION);
    if(NULL == hIconSm){
        MessageBox((HWND)NULL,TEXT("Could not obtain icon"),TEXT("LoadIcon"),MB_ICONERROR);
        return(EXIT_FAILURE);
    }

    wndEx.cbSize = sizeof(WNDCLASSEX);
    wndEx.cbClsExtra = 0;
    wndEx.cbWndExtra = 0;
    wndEx.hbrBackground  = hBrush;
    wndEx.hCursor = hCursor;
    wndEx.hIcon = hIcon;
    wndEx.hIconSm = hIconSm;
    wndEx.hInstance = hInstance;
    wndEx.lpfnWndProc = WndProc;
    wndEx.lpszClassName = szClassName;
    wndEx.lpszMenuName = NULL;
    wndEx.style = CS_HREDRAW | CS_VREDRAW ;

    if(! RegisterClassEx(&wndEx))
    {
        MessageBox((HWND)NULL,TEXT("Could not resgister window class"),TEXT("RegisterClassEx"),MB_ICONERROR);
        return(EXIT_FAILURE);
    }

    g_screen_width = GetSystemMetrics(SM_CXSCREEN);
    g_screen_height = GetSystemMetrics(SM_CYSCREEN);
    hwnd = CreateWindowEx(
                    WS_EX_APPWINDOW,
                    szClassName,
                    szWindowCaption,
                    WS_OVERLAPPEDWINDOW,
                    0-10,
                    0,
                    g_screen_width+20,
                    g_screen_height,
                    (HWND)NULL,
                    (HMENU)NULL,
                    hInstance,
                    NULL
                    );

    if(NULL == hwnd){
        MessageBox((HWND)NULL,TEXT("Could not create application window"),TEXT("CreateWindowEx"),MB_ICONERROR);
        return(EXIT_FAILURE);
    }
    
    ShowWindow(hwnd,nShowCmd);
    UpdateWindow(hwnd);

    while(GetMessage(&msg,(HWND)NULL,0,0)){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return((int)msg.wParam);
}

int N = 5;
#define IDB_BUTTON1 1001
#define ID_TIMER_INSERTION      1002

LRESULT CALLBACK WndProc(HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
    PAINTSTRUCT ps;
	TEXTMETRIC tm;
	HDC hdc;

	static int cxClient,cyClient;
	static int cxChar, cyChar, cxCaps;
	static int iCount,iLine;
	static int xPos = 0, yPos = 0;
    static int line1 = 1;
    static int line2 = 2;
    int arr[5] = {40,50,30,20,10};
    static int iCounter = 0;
    
	switch(uMsg)
    {
		case WM_CREATE: 
        {
			hdc = GetDC(hwnd); 
            GetTextMetrics(hdc, &tm); 
            cxChar = tm.tmAveCharWidth; 
            cyChar = tm.tmHeight + tm.tmExternalLeading; 
            cxCaps = (tm.tmPitchAndFamily & 1 ? 3 : 2) * cxChar / 2;
            
			ReleaseDC(hwnd, hdc); 
            hdc = NULL; 
            gpStrVec = ReadFileInMemory(glpCmdLine);

             g_insertionVector = CreateInsertionSortVector();
            InsertionSortInMemory(arr,N);

			break;
		}

		case WM_SIZE:
		{
			cxClient = LOWORD(lParam);
			cyClient = HIWORD(lParam);
            SetTimer(hwnd,ID_TIMER_INSERTION,1000,(TIMERPROC)NULL);
			hdc = GetDC(hwnd);            
            xPos = cxClient * 0.3 + 100;
            yPos = 10;
            ReleaseDC(hwnd,hdc);
            
			break;
		}

        case WM_PAINT:
        {
            hdc = BeginPaint(hwnd,&ps);
			//iCounter = 0;
            //header(hdc, cxClient,cyClient,g_insertionVector->pInsertionSort[0]);
			PaintDesign(hdc,cxClient,cyClient);
            
			PrintAlgorithm(hdc, cyChar, cxCaps);
            
			//PrintArrow(hdc,0,0, cyChar, cxCaps);   //Testing Purpose
            
            
            
            //for(iCounter = 0; iCounter < g_insertionVector->iVectorSize ; iCounter++)
            {
                /*We will call Drawing Diagram function for sort diagram. */
               // DrawInsertionSort(hdc, xPos, yPos, g_insertionVector->pInsertionSort[iCounter]);
               // yPos += 80;
            }

            EndPaint(hwnd,&ps);
            hdc = NULL; 
        }
        break;
        case WM_TIMER:
        {
            //DrawInsertionSort(hdc, xPos, yPos, g_insertionVector->pInsertionSort[iCounter]);
            //yPos += 80;
            if(g_insertionVector == NULL)
            {
                break;
            }
           
            switch(wParam)
            {
                case ID_TIMER_INSERTION:
                {
                    hdc = GetDC(hwnd);
                    line1 = g_insertionVector->pInsertionSort[iCounter].rangeObj.fromLine;
                    line2 = g_insertionVector->pInsertionSort[iCounter].rangeObj.toLine;
                    
                    //DrawInsertionTextOut(hdc, xPos, yPos, g_insertionVector->pInsertionSort[iCounter]);
                    //yPos += 30;

                    DrawInsertionSort(hdc, xPos, yPos, g_insertionVector->pInsertionSort[iCounter]);
                    yPos += 80;//getHeightSquare();
                    PrintArrow(hdc,line1,line2, cyChar, cxCaps);   //Testing Purpose
                    ReleaseDC(hwnd,hdc);
                    iCounter++;
                    if(iCounter == g_insertionVector->iVectorSize)
                        KillTimer(hwnd,ID_TIMER_INSERTION);
                    break;
                }
            }
        }
       
        break;

		case WM_DESTROY:
        {
            DestroyStringVector(gpStrVec);
            DestroyInsertionSortVector(g_insertionVector);
            PostQuitMessage(0);
            break;
        }
    }

    return (DefWindowProc(hwnd,uMsg,wParam,lParam));
}



