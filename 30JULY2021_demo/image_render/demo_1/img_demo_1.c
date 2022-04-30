#include<Windows.h>
#include"img_demo_1.h"

#pragma comment(lib,"gdi32.lib")
#pragma comment(lib,"user32.lib")
#pragma comment(lib,"kernel32.lib")

LRESULT CALLBACK WndProc(HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd)
{
    static TCHAR szClassName[] = TEXT("The First Window");
    static TCHAR szWindowCaption[] = TEXT("Hello Windows!");

    HBRUSH hBrush = NULL;
    HCURSOR hCursor = NULL;
    HICON hIcon  = NULL;
    HICON hIconSm = NULL;
    HWND hwnd = NULL;

    MSG msg;
    WNDCLASSEX wndEx;

    ZeroMemory(&wndEx,sizeof(WNDCLASSEX));
    ZeroMemory(&wndEx,sizeof(MSG));



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

    hwnd = CreateWindowEx(
                    WS_EX_APPWINDOW,
                    szClassName,
                    szWindowCaption,
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


LRESULT CALLBACK WndProc(HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
    HDC hdc;
    HDC hdcComp;
    static HBITMAP hbmap;
    RECT rc;
    PAINTSTRUCT ps;
    BITMAP bmBuffer;
    static HINSTANCE hInst;

    switch(uMsg)
    {
        case WM_CREATE:
        {
            hInst = (HINSTANCE)((LPCREATESTRUCT)lParam)->hInstance;
            break;
        }
        case WM_PAINT:
        {
            hdc = BeginPaint(hwnd,&ps);
            
            hbmap = LoadBitmap(hInst,MAKEINTRESOURCE(MY_BITMAP_2));
                /*
                LoadBitmap(hInst,MAKEINTRESOURCE(MY_BITMAP_1));
                    This function loads the specified bitmap resource from a modules executable file.
                */

            hdcComp = CreateCompatibleDC(hdc);
                /*
                CreateCompatibleDC(hdc);
                    The CreateCompatibleDC function creates a memory device context (DC) 
                    compatible with the specified device.
                */

            SelectObject(hdcComp,hbmap);
            GetObject(hbmap, sizeof(BITMAP), &bmBuffer); // retrieves dimension of a bitmap
            GetClientRect(hwnd,&rc);
            
            //BitBlt(hdc, (rc.right - bmBuffer.bmWidth)/3, (rc.bottom - bmBuffer.bmHeight)/3, (int)bmBuffer.bmWidth , (int)bmBuffer.bmHeight, hdcComp, 0, 0, SRCCOPY);
            StretchBlt(hdc, 0, 0, rc.right, rc.bottom, hdcComp, 0, 0, bmBuffer.bmWidth, bmBuffer.bmHeight, SRCCOPY);
            
            DeleteDC(hdcComp);
            DeleteObject(hbmap);
            EndPaint(hwnd,&ps);
            break;
        }
        case WM_DESTROY:
        {
            PostQuitMessage(0);
            break;
        }
    }

    return (DefWindowProc(hwnd,uMsg,wParam,lParam));
}
