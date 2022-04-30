#include<Windows.h>

#pragma comment(lib,"gdi32.lib")
#pragma comment(lib,"user32.lib")
#pragma comment(lib,"kernel32.lib")

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR szCmdLine,int nShowCmd)
{
    static TCHAR szClassName[] = TEXT("WinMain_5");
    static TCHAR szWindowCaption[] = TEXT("WinMain - 5");

    HWND hwnd = NULL;
    HICON hIcon = NULL;
    HICON hIconSm = NULL;
    HBRUSH hBrush = NULL;
    HCURSOR hCursor = NULL;

    MSG msg;
    WNDCLASSEX wndEx;

    ZeroMemory(&msg,sizeof(MSG));
    ZeroMemory(&wndEx,sizeof(WNDCLASSEX));

    hIcon = LoadIcon((HINSTANCE)NULL,IDI_APPLICATION);
    if(!hIcon){
        MessageBox((HWND)NULL,TEXT("Could Not load icon"),TEXT("LoadIcon"),MB_ICONERROR);
        return(EXIT_FAILURE);
    }

    hIconSm = LoadIcon((HINSTANCE)NULL,IDI_APPLICATION);
    if(!hIconSm){
        MessageBox((HWND)NULL,TEXT("Could not load small icon"),TEXT("LoadIcon"),MB_ICONERROR);
        return(EXIT_FAILURE);
    }

    hBrush = (HBRUSH)GetStockObject(WHITE_BRUSH);
    if(!hBrush){
        MessageBox((HWND)NULL,TEXT("Could not get brush"),TEXT("GetStockBrush"),MB_ICONERROR);
        return(EXIT_FAILURE);
    }

    hCursor = LoadCursor((HINSTANCE)NULL,IDC_ARROW);
    if(!hCursor){
        MessageBox((HWND)NULL,TEXT("Could not load cursor"),TEXT("LoadCursor"),MB_ICONERROR);
        return(EXIT_FAILURE);
    }


    wndEx.cbSize = sizeof(WNDCLASSEX);
    wndEx.cbClsExtra = 0;
    wndEx.cbWndExtra = 0;
    wndEx.hIcon = hIcon;
    wndEx.hIconSm = hIconSm;
    wndEx.hbrBackground = hBrush;
    wndEx.hCursor = hCursor;
    wndEx.lpszClassName = szClassName;
    wndEx.lpszMenuName = NULL;
    wndEx.lpfnWndProc = WndProc;
    wndEx.hInstance = hInstance;
    wndEx.style = CS_HREDRAW|CS_VREDRAW;

    if(!RegisterClassEx(&wndEx)){
        MessageBox((HWND)NULL,TEXT("Could not register class"),TEXT("RegisterClassEx"),MB_ICONERROR);
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

    if(!hwnd){
        MessageBox((HWND)NULL,TEXT("could not able to create window"),TEXT("CreateWindowEx"),MB_ICONERROR);
        return(EXIT_FAILURE);
    }

    ShowWindow(hwnd,nShowCmd);
    UpdateWindow(hwnd);

    while(GetMessage(&msg,NULL,0,0)){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return((int)msg.wParam);
}


LRESULT CALLBACK WndProc(HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM lParam){

    switch(uMsg){
        case WM_DESTROY:
        {
            PostQuitMessage(0);
            break;
        }
    }
    return (DefWindowProc(hwnd,uMsg,wParam,lParam));
}