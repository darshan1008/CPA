#include <Windows.h> 

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam); 

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLint, int nShowCmd){
	static TCHAR szAppname[] = TEXT("HelloWin"); 
	HWND hWnd; 
	MSG msg; 
	WNDCLASSEX wndEx; 

	ZeroMemory(&msg, sizeof(MSG)); 
	ZeroMemory(&wndEx, sizeof(WNDCLASSEX)); 

	wndEx.cbSize = sizeof(WNDCLASSEX); 
	wndEx.cbClsExtra = 0; 
	wndEx.cbWndExtra = 0; 
	wndEx.hbrBackground = (HBRUSH)GetStockObject(NULL, WHITE_BRUSH); 
	wndEx.hIcon = LoadIcon(NULL, IDI_APPLICATION); 
	wndEx.hIconSm = LoadIcon(NULL, IDI_APPLICATION); 
	wndEx.hCursor = LoadCursor(NULL, IDC_ARROW); 
	wndEx.lpszClassName = szAppname; 
	wndEx.lpszMenuName = NULL; 
	wndEx.lpfnWndProc = WndProc; 
	wndEx.style = CS_HREDRAW | CS_VREDRAW; 

	RegisterClassEx(&wndEx); 

	hWnd = CreateWindowEx(WS_EX_APPWINDOW, szAppname, szAppname, WS_OVERLAPPEDWINDOW, 
							CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 
							NULL, NULL, hInstance, NULL); 

	ShowWindow(hWnd, nShowCmd); 
	UpdateWindow(hWnd); 

	while(GetMessage(&msg, NULL, 0, 0)){
		TranslateMessage(&msg); 
		DispatchMessage(&msg); 
	}

	return msg.wParam; 
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam){
	
	switch(uMsg){
		case WM_DESTROY: 
			PostQuitMessage(0); 
			break; 
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam); 
}