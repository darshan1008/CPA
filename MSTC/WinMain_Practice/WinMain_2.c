#include<Windows.h>

#pragma comment(lib,"gdi32.lib")
#pragma comment(lib,"user32.lib")
#pragma comment(lib,"kernel32.lib")

LRESULT CALLBACK WndProc(HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR szCmdLine,int nShowCmd)
{
    static TCHAR szClassName[] = TEXT("The First Window");
    static TCHAR szWindowCaption[] = TEXT("WinMain_2");

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
    if(NULL == hIcon){
        MessageBox((HWND)NULL,TEXT("Could not load icon"),TEXT("LoadIcon"),MB_ICONERROR);
        return (EXIT_FAILURE);
    }

    hIconSm = LoadIcon((HINSTANCE)NULL,IDI_APPLICATION);
    if(NULL == hIconSm)
    {
        MessageBox((HWND)NULL,TEXT("Could not load small icon"),TEXT("LoadIcon"),MB_ICONERROR);
        return (EXIT_FAILURE);
    }

    hCursor = LoadCursor((HINSTANCE)NULL,IDC_ARROW);
    if(NULL == hCursor){
        MessageBox((HWND)NULL,TEXT("Could not load cursor"),TEXT("LaodCursor"),MB_ICONERROR);
        return (EXIT_FAILURE);
    }

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
    wndEx.style = CS_HREDRAW | CS_VREDRAW ;


    if(! RegisterClassEx(&wndEx)){
        MessageBox((HWND)NULL,TEXT("Could not register window class"),TEXT("RegisterClassEx"),MB_ICONERROR);
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
        return (EXIT_FAILURE);
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
    switch(uMsg)
    {
        case WM_DESTROY:
        {
            PostQuitMessage(0);
            break;
        }
    }

    return(DefWindowProc(hwnd,uMsg,wParam,lParam));
}
