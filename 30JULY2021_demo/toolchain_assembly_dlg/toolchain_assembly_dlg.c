#include<Windows.h>
#include<winuser.h>
#include"MyHeader.h"

#pragma comment(lib,"gdi32.lib")
#pragma comment(lib,"user32.lib")
#pragma comment(lib,"User32.lib")
#pragma comment(lib,"kernel32.lib")


#define IDB_ASMBTN			1001
#define IDB_WNDBUTTON		1002
#define IDB_DLGBUTTON		1003
#define ID_CLOSE_ASM_DLG	1004


TCHAR DialogClassName[] = TEXT("DialogClass");
TCHAR DialogClassName_Asm[] = TEXT("DailogBox Assembly");

LRESULT CALLBACK WndProc(HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM lParam);
LRESULT CALLBACK DlgProcToolchain( HWND   hWndDlg, UINT   Msg, WPARAM wParam, LPARAM lParam );
LRESULT CALLBACK DlgProcAssembly( HWND   hWndDlg, UINT   Msg, WPARAM wParam, LPARAM lParam );


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

LRESULT CALLBACK WndProc( HWND    hWnd,UINT    Msg,WPARAM  wParam,LPARAM  lParam )
{
	HWND hWndButton = NULL;
	HWND hWndDlgBox = NULL;
	HWND hShowAsm = NULL;
    static HINSTANCE hInst;
    WNDCLASSEX  wc;
    switch (Msg)

    {
        case WM_CREATE:
        {
            hInst = (HINSTANCE)((LPCREATESTRUCT)lParam)->hInstance;
            
            wc.cbSize           = sizeof(WNDCLASSEX);
            wc.style            = 0;
            wc.lpfnWndProc      = (WNDPROC)DlgProcToolchain;
            wc.cbClsExtra       = 0;
            wc.cbWndExtra       = 0;
            wc.hInstance        = (HINSTANCE)hInst;
            wc.hIcon            = NULL;
            wc.hIconSm          = NULL;
            wc.hCursor          = LoadCursor(NULL, IDC_ARROW);
            wc.hbrBackground    = (HBRUSH)(COLOR_WINDOW + 1);
            wc.lpszMenuName     = NULL;
            wc.lpszClassName    = DialogClassName;
            if(!RegisterClassEx(&wc))
            {
                MessageBox(NULL, TEXT("Failed To Register The Dialog Class."), TEXT("Error"), MB_OK | MB_ICONERROR);
                break;
            }

			wc.cbSize           = sizeof(WNDCLASSEX);
            wc.style            = 0;
            wc.lpfnWndProc      = (WNDPROC)DlgProcAssembly;
            wc.cbClsExtra       = 0;
            wc.cbWndExtra       = 0;
            wc.hInstance        = (HINSTANCE)hInst;
            wc.hIcon            = NULL;
            wc.hIconSm          = NULL;
            wc.hCursor          = LoadCursor(NULL, IDC_ARROW);
            wc.hbrBackground    = (HBRUSH)(COLOR_WINDOW + 1);
            wc.lpszMenuName     = NULL;
            wc.lpszClassName    = DialogClassName_Asm;
            if(!RegisterClassEx(&wc))
            {
                MessageBox(NULL, TEXT("Failed To Register The Dialog Class."), TEXT("Error"), MB_OK | MB_ICONERROR);
                break;
            }

            hWndButton = CreateWindowEx(
									0,     
									TEXT("BUTTON"), 
									TEXT("Show Toolchain"), 
									WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 
									10, 
									10, 
									100, 
									30, 
									hWnd, 
									(HMENU)IDB_WNDBUTTON, 
									(HINSTANCE)hInst, 
									NULL
									); 

            if (!hWndButton)
			{
                MessageBox(NULL, TEXT("Main Window Button Failed."), TEXT("Error"), MB_OK | MB_ICONERROR);
				break;
			}
			hShowAsm =  CreateWindowEx(
									0,     
									TEXT("BUTTON"), 
									TEXT("World of Assembly "), 
									WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 
									10, 
									50, 
									120, 
									30, 
									hWnd, 
									(HMENU)IDB_ASMBTN, 
									(HINSTANCE)hInst, 
									NULL
									); 

            if (!hShowAsm)
			{
                MessageBox(NULL, TEXT("Main Window Button Failed."), TEXT("Error"), MB_OK | MB_ICONERROR);
				break;
			}
			break;
        }
        
        case WM_COMMAND: 

        {
            switch(LOWORD(wParam))
            {
                case IDB_WNDBUTTON:
                {
                    switch(HIWORD(wParam))
                    {
                        case BN_CLICKED:
                        {
                            if (!hWndDlgBox)
                            {

                                hWndDlgBox = CreateWindowEx(
												WS_EX_DLGMODALFRAME | WS_EX_TOPMOST,
												DialogClassName,
												TEXT("Toolchain"), 
												WS_VISIBLE | WS_POPUP | WS_CAPTION, 
												100, 
												100, 
												600, 
												650, 
												hWnd, 
												NULL, 
												(HINSTANCE)hInst, 
												NULL);

                                if (!hWndDlgBox)
								{
                                    MessageBox(NULL, TEXT("Dialog Box Failed."), TEXT("Error"), MB_OK | MB_ICONERROR);
									break;
								}
                           }
                        }
                        break; 
                    }
				}
				case IDB_ASMBTN:
                {
                    switch(HIWORD(wParam))
                    {
                        case BN_CLICKED:
                        {
                            if (!hWndDlgBox)
                            {
                                hWndDlgBox = CreateWindowEx(
												WS_EX_DLGMODALFRAME | WS_EX_TOPMOST,
												DialogClassName_Asm,
												TEXT("Assembly Wolrd"), 
												WS_VISIBLE | WS_POPUP | WS_CAPTION, 
												100, 
												100, 
												600, 
												650, 
												hWnd, 
												NULL, 
												(HINSTANCE)hInst, 
												NULL);

                                if (!hWndDlgBox)
								{
                                    MessageBox(NULL, TEXT("ASM Dialog Box Failed."), TEXT("Error"), MB_OK | MB_ICONERROR);
									break;
								}
                           }
                        }
                        break; 
                    }
				}
                break;
			}
			break;
        }


        case WM_CLOSE:
		{
            DestroyWindow(hWnd);
			break;
		}

        case WM_DESTROY:
		{
            PostQuitMessage(0);
			break;
		}
    }



    return (DefWindowProc(hWnd, Msg, wParam, lParam));

}

LRESULT CALLBACK DlgProcToolchain( HWND   hWndDlg, UINT   Msg, WPARAM wParam, LPARAM lParam )
{
	HDC hdc;
    HDC hdcComp;
    static HBITMAP hbmap;
    RECT rc;
    PAINTSTRUCT ps;
    BITMAP bmBuffer;
    static HINSTANCE hInst;
	HANDLE hImage;
	HWND hStatic;
	static HWND hDlgButton;

	switch(Msg)
	{
		case WM_CREATE:
        {
			hInst = (HINSTANCE)((LPCREATESTRUCT)lParam)->hInstance;
			GetClientRect(hWndDlg,&rc);
            hDlgButton = CreateWindowEx(
									0,     
									TEXT("BUTTON"), 
									TEXT("Close"), 
									WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 
									rc.right/2 - 50, 
									rc.bottom - 30, 
									100, 
									20, 
									hWndDlg, 
									(HMENU)IDB_DLGBUTTON, 
									(HINSTANCE)hInst, 
									NULL
									);

             if (!hDlgButton)
			 {
                MessageBox(NULL, TEXT("Dialog Button Failed."), TEXT("Error"), MB_OK | MB_ICONERROR);
				break;
			 }

			 break;
        }

		case WM_COMMAND:
		{
			if(LOWORD(wParam) == IDB_DLGBUTTON)
			{
				//SendMessage(hWndDlg, WM_CLOSE, 0, 0);
				DestroyWindow(hWndDlg);
			}
			break;
		}
		case WM_PAINT:
		{
			hdc = BeginPaint(hWndDlg,&ps);
			SetBkColor(hdc,RGB(255,0,0));
            TextOut(hdc,10,100,TEXT("TEST"),4);
            hbmap = LoadBitmap(hInst,MAKEINTRESOURCE(TOOLCHAIN_BITMAP));
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
            GetClientRect(hWndDlg,&rc);
           if(! BitBlt(hdc, (rc.right - bmBuffer.bmWidth)/3, (rc.bottom - bmBuffer.bmHeight)/3, (int)bmBuffer.bmWidth , (int)bmBuffer.bmHeight, hdcComp, 0, 0, SRCCOPY))
			{
				MessageBox(NULL,TEXT("BitBlt FAIELD"),TEXT("ERROR"),MB_ICONERROR);
			}

			//BitBlt(hdc, 0, 10, (int)bmBuffer.bmWidth , (int)bmBuffer.bmHeight, hdcComp, 0, 0, SRCCOPY);
            //StretchBlt(hdc, 0, 0, rc.right, rc.bottom-30, hdcComp, 0, 0, bmBuffer.bmWidth, bmBuffer.bmHeight, SRCCOPY);
            
            DeleteDC(hdcComp);
            DeleteObject(hbmap);
            EndPaint(hWndDlg,&ps);
            break;
		}
		case WM_CLOSE:
		{
			PostQuitMessage(0);
			break;
		}

	}
	return(DefWindowProc(hWndDlg,Msg,wParam,lParam));
}

LRESULT CALLBACK DlgProcAssembly( HWND hWndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	HDC hdc;
    HDC hdcComp;
    static HBITMAP hbmap;
    RECT rc;
    PAINTSTRUCT ps;
    BITMAP bmBuffer;
    static HINSTANCE hInst;
	HANDLE hImage;
	HWND hStatic;
	static HWND hDlgButton;

	switch(uMsg)
	{
		case WM_CREATE:
        {
			hInst = (HINSTANCE)((LPCREATESTRUCT)lParam)->hInstance;
			GetClientRect(hWndDlg,&rc);
            hDlgButton = CreateWindowEx(
									0,     
									TEXT("BUTTON"), 
									TEXT("Close"), 
									WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 
									rc.right/2 - 50, 
									rc.bottom - 20, 
									100, 
									20, 
									hWndDlg, 
									(HMENU)ID_CLOSE_ASM_DLG, 
									(HINSTANCE)hInst, 
									NULL
									);

             if (!hDlgButton)
			 {
                MessageBox(NULL, TEXT("Dialog Button Failed."), TEXT("Error"), MB_OK | MB_ICONERROR);
				break;
			 }

			 break;
        }
		case WM_COMMAND:
		{
			if(LOWORD(wParam) == ID_CLOSE_ASM_DLG)
			{
				//SendMessage(hWndDlg, WM_CLOSE, 0, 0);
				DestroyWindow(hWndDlg);
			}
			break;
		}
	}
	return(DefWindowProc(hWndDlg,uMsg,wParam,lParam));
}