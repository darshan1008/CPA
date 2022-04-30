
#include"InsertionSortHeader.h"

#pragma comment(lib,"user32.lib")
#pragma comment(lib,"gdi32.lib")
#pragma comment(lib,"kernel32.lib")
#define ARRAY_SIZE(X) (sizeof(X)/sizeof(X[0]))

int N = 5;
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance, LPSTR lpCmdLine,int nShowCmd)
{
    static char lpszClassName[] = TEXT("First Window");
    static char lpszWindowCaption[] = TEXT("Project ");
    
    WNDCLASSEX wndEx;
    MSG msg;

    HBRUSH hBrush = NULL;
    HCURSOR hCursor = NULL;
    HICON hIcon = NULL;
    HICON hIconSm = NULL;
    HWND hWnd = NULL;

    ZeroMemory(&wndEx, sizeof(WNDCLASSEX));
    ZeroMemory(&msg,sizeof(msg));

    hBrush = (HBRUSH)GetStockObject(WHITE_BRUSH);
    if(!hBrush)
    {
        MessageBox((HWND)NULL,TEXT("Failed"),TEXT("GetStockObject"),MB_ICONERROR);
        return(EXIT_FAILURE);
    }
    hCursor = LoadCursor((HINSTANCE)NULL,IDC_ARROW);
    if(!hCursor)
    {
        MessageBox((HWND)NULL,TEXT("Failed"),TEXT("LoadCursor"),MB_ICONERROR);
        return(EXIT_FAILURE);
    }
    hIcon = LoadIcon((HINSTANCE)NULL,IDI_APPLICATION);
    if(!hIcon)
    {
        MessageBox((HWND)NULL,TEXT("Failed"),TEXT("LoadIcon"),MB_ICONERROR);
        return(EXIT_FAILURE);
    }
    hIconSm = LoadIcon((HINSTANCE)NULL,IDI_APPLICATION);
    if(!hIconSm)
    {
        MessageBox((HWND)NULL,TEXT("Failed"),TEXT("LoadIcon"),MB_ICONERROR);
        return(EXIT_FAILURE);
    }
    wndEx.cbSize = sizeof(WNDCLASSEX);
    wndEx.cbClsExtra = 0;
    wndEx.cbWndExtra = 0;

    wndEx.hbrBackground = hBrush;
    wndEx.hCursor = hCursor;
    wndEx.hIcon = hIcon;
    wndEx.hIconSm = hIconSm;

    wndEx.lpszClassName = lpszClassName;
    wndEx.lpszMenuName = NULL;
    wndEx.lpfnWndProc = WndProc;
    wndEx.style = CS_VREDRAW | CS_HREDRAW;

    wndEx.hInstance = hInstance;

    if(!RegisterClassEx(&wndEx))
    {
        MessageBox((HWND)NULL,TEXT("Failed"),TEXT("RegisterClassEx"),MB_ICONERROR);
        return(EXIT_FAILURE);
    }

    hWnd = CreateWindowEx(
        WS_EX_APPWINDOW,
        lpszClassName,
        lpszWindowCaption,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        (HWND)NULL,
        (HMENU)NULL,
        hInstance,
        NULL
        );
    if(!hWnd)
    {
        MessageBox((HWND)NULL,TEXT("Failed"),TEXT("CreateWindowEx"),MB_ICONERROR);
        return(EXIT_FAILURE);
    }
    ShowWindow(hWnd,nShowCmd);
    UpdateWindow(hWnd);
    while(GetMessage(&msg,NULL,0,0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return(msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    INSERTIONSORTDATA insertionSortDataObj;
    int iCounter;
    int iCounter2;
    PAINTSTRUCT ps;
	RECT rs;
    HDC hdc;
    static int cxClient;                /*static variable to store width of window*/
    static int cyClient;                /*static variable to store height of window*/
    static HINSTANCE hInst;
    int screenHeight;
    int screenWidth;
    int xPos = cxClient/4*1;
    int yPos = 0;
    CHAR* noteArray[] = {TEXT("Note - "),TEXT("- Sorted Array"),TEXT("- UnSorted Array"),TEXT("- Exchange Array")};
    int i;                              /*loop variable */
    int p = 150,q = 200;                /*given array rectangle control variable*/
    int x = 10;                         /*note ,sortedArray, unSortedArray text control variable*/
    int k = 0;                          /*formatted value control variable*/
    int m = 180;                        /*note rectangle control variable*/
    int n = 220;                        /*note rectangle control variable*/
    
    

    int arr[5] = {50,40,30,20,10};
    switch(uMsg)
    {
        case WM_CREATE:
        {
            hInst = (HINSTANCE)((LPCREATESTRUCT)lParam)->hInstance;
            hdc = GetDC(hWnd);
            screenWidth = GetDeviceCaps(hdc,HORZRES);
            screenHeight = GetDeviceCaps(hdc,VERTRES);

            SetWindowPos(hWnd,HWND_TOP,0,0,screenWidth,screenHeight,SWP_SHOWWINDOW);
            ReleaseDC(hWnd,hdc);

            g_insertionVector = CreateInsertionSortVector();
            InsertionSortInMemory(arr,N);
           
            break;
        } 
        case WM_SIZE:
        {
            cxClient = LOWORD(lParam);
            cyClient = HIWORD(lParam);
            break;
        }
        case WM_PAINT:
        {
            hdc = BeginPaint(hWnd,&ps);
            xPos = cxClient/4*1;
            yPos = 0;
            //header(hdc, cxClient,cyClient,g_insertionVector);
            for(iCounter = 0; iCounter < g_insertionVector->iVectorSize ; iCounter++,yPos += 80)
            {
                /*We will call Drawing Diagram function for sort diagram. */
                DrawInsertionSort(hdc, xPos, yPos, g_insertionVector->pInsertionSort[iCounter]);
            }
            EndPaint(hWnd,&ps);
            break;
        }
    
        case WM_DESTROY:
        {
            DestroyInsertionSortVector(g_insertionVector);
            PostQuitMessage(0);
            break;
        }
    }
    return(DefWindowProc(hWnd,uMsg,wParam,lParam));
}

int FormatedTextOut(HDC hdc,int x,int y,TCHAR* pszFormat,...)
{
  	TCHAR szBuffer[1024] = {""};
	va_list pArgs;
	va_start(pArgs,pszFormat);

	_vsntprintf(szBuffer, ARRAY_SIZE(szBuffer) ,pszFormat,pArgs);
    TextOut(hdc,x,y,szBuffer,strlen(szBuffer));
    return(0);
}
