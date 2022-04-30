#include <Windows.h> 
#include <assert.h> 

#pragma comment(lib, "kernel32.lib")
#pragma comment(lib, "gdi32.lib") 
#pragma comment(lib, "user32.lib")

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam); 

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    static TCHAR szAppname[] = TEXT("HelloWin App"); 
    static TCHAR szWindowname[] = TEXT("ASTROMEDICOMP-PYTHON BATCH#43");    

    HWND hWnd = NULL; 
    HBRUSH hBrush = NULL; 
    HCURSOR hCursor = NULL; 
    HICON hIcon = NULL; 
    HICON hIconSm = NULL; 

    WNDCLASSEX wndEx; 
    MSG msg; 

    ZeroMemory(&wndEx, sizeof(WNDCLASSEX)); 
    ZeroMemory(&msg, sizeof(MSG)); 

    hBrush = (HBRUSH)GetStockObject(WHITE_BRUSH); 
    assert(hBrush); 

    hCursor = LoadCursor(NULL, IDC_ARROW); 
    assert(hCursor); 

    hIcon = LoadIcon(NULL, IDI_APPLICATION); 
    assert(hIcon); 

    hIconSm = LoadIcon(NULL, IDI_APPLICATION); 
    assert(hIconSm); 
    
    wndEx.cbSize = sizeof(WNDCLASSEX); 
    wndEx.cbClsExtra = 0; 
    wndEx.cbWndExtra = 0; 
    wndEx.hbrBackground = hBrush; 
    wndEx.hCursor = hCursor; 
    wndEx.hIcon = hIcon; 
    wndEx.hIconSm = hIconSm; 
    wndEx.hInstance = hInstance; 
    wndEx.lpfnWndProc = WndProc; 
    wndEx.lpszClassName = szAppname; 
    wndEx.lpszMenuName = NULL; 
    wndEx.style = CS_HREDRAW | CS_VREDRAW; 

    ATOM bRet = RegisterClassEx(&wndEx); 
    assert(bRet); 
    
    hWnd = CreateWindowEx(WS_EX_APPWINDOW, szAppname, szWindowname, WS_OVERLAPPEDWINDOW, 
                            CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 
                            NULL, NULL, hInstance, NULL); 
    assert(hWnd != NULL); 

    ShowWindow(hWnd, nShowCmd); 
    UpdateWindow(hWnd); 

    while(GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg); 
        DispatchMessage(&msg); 
    }

    return (msg.wParam); 
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
        case WM_DESTROY: 
            PostQuitMessage(0); 
            break; 
    }

    return (DefWindowProc(hWnd, uMsg, wParam, lParam)); 
}