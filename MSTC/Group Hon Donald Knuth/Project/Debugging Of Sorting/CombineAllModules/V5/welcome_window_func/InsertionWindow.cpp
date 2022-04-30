#include<Windows.h>

#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "kernel32.lib")

int screen_width;
int screen_height;

void PrintTextI(HDC hdc,int cxClient,int cyClient);
void DrawInsertionWindow(HDC,int,int);
void DrawLineUtil(HDC,int,int,int,int);

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	static TCHAR szClassName[] = TEXT("Insertion Sort");
	static TCHAR szWindowCaption[] = TEXT("Insertion Sort");

	HBRUSH hBrush = NULL;
	HCURSOR hCursor = NULL;
	HICON hIcon = NULL;
	HICON hIconSm = NULL;
	HWND hWnd = NULL;

	WNDCLASSEX wndEx;
	MSG msg;

	screen_width = GetSystemMetrics(SM_CXSCREEN);
    screen_height = GetSystemMetrics(SM_CYSCREEN);

	ZeroMemory(&wndEx, sizeof(WNDCLASSEX));
	ZeroMemory(&msg, sizeof(MSG));

	hBrush = (HBRUSH)GetStockObject(WHITE_BRUSH);
	if( hBrush == NULL)
	{
		MessageBox((HWND)NULL, TEXT("Could not obtain brush"), TEXT("GetStockObject"), MB_ICONERROR);
		return (EXIT_FAILURE);
	}

	hCursor = LoadCursor((HINSTANCE)NULL, IDC_ARROW);
	if( hCursor == NULL)
	{
		MessageBox((HWND)NULL, TEXT("Could not obtain cursor"), TEXT("LoadCursor"), MB_ICONERROR);
		return (EXIT_FAILURE);
	}

	hIcon = LoadIcon((HINSTANCE)NULL, IDI_APPLICATION);
	if( hIcon == NULL)
	{
		MessageBox((HWND)NULL, TEXT("Could not obtain icon"), TEXT("LoadIcon"), MB_ICONERROR);
		return (EXIT_FAILURE);
	}

	hIconSm = LoadIcon((HINSTANCE)NULL, IDI_APPLICATION);
	if( hIconSm == NULL)
	{
		MessageBox((HWND)NULL, TEXT("Could not obtain small Icon"), TEXT("LoadIcon"), MB_ICONERROR);
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
	wndEx.style = CS_HREDRAW | CS_VREDRAW;

	if(!RegisterClassEx(&wndEx))
	{
		MessageBox((HWND)NULL, TEXT("Cannot register a window class"), TEXT("RegisterClassEx"), MB_ICONERROR);
		return (EXIT_FAILURE);
	}

	hWnd = CreateWindowEx(WS_EX_APPWINDOW,
						  szClassName,
						  szWindowCaption,
						  WS_OVERLAPPED | WS_CAPTION | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU | WS_THICKFRAME,
						  0 - 10,
                          0,
                          screen_width + 20,
                          screen_height + 10,
						  (HWND)NULL,
						  (HMENU)NULL,
						  hInstance,
						  NULL);

	if(hWnd == NULL)
	{
		MessageBox((HWND)NULL, TEXT("Could not create application Window"), TEXT("CreateWindowEx"), MB_ICONERROR);
		return (EXIT_FAILURE);
	}

	ShowWindow(hWnd, nShowCmd);
	UpdateWindow(hWnd);

	while(GetMessage(&msg, (HWND)NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	
	return(msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hWnd,UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static int cxClient, cyClient;
	
	HDC hdc = NULL;
	HWND hBtn;
	
	TEXTMETRIC tm;
	PAINTSTRUCT ps;

		switch(uMsg)
	{
	case WM_CREATE:
		{
			hBtn = CreateWindowEx(
							0,     
							TEXT("BUTTON"), 
							TEXT("ENTER DATA"), 
							WS_VISIBLE | WS_CHILD , 
							750, 
							765, 
							180, 
							35, 
							hWnd, 
							(HMENU)NULL, 
							(HINSTANCE)NULL, 
							NULL
							);

            if ((hBtn) == NULL) {
                MessageBox(NULL, TEXT("Button Failed."), TEXT("Error"), MB_OK | MB_ICONERROR);
				exit(0);
			}

		break;
		}
	
	case WM_SIZE:
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);
		break;
		
	case WM_PAINT:
		{
			hdc = BeginPaint(hWnd, &ps);
				
			DrawInsertionWindow(hdc,cxClient,cyClient);
			

			EndPaint(hWnd, &ps);
			hdc = NULL;		
			break;
		}
			
	case WM_DESTROY:
		PostQuitMessage(EXIT_SUCCESS);
		break;
	}
	
	return (DefWindowProc(hWnd, uMsg, wParam, lParam));
}

void DrawLineUtil(HDC hdc,int xsrc,int ysrc,int xdes,int ydes)
{
	MoveToEx(hdc,xsrc,ysrc,NULL);
    LineTo(hdc,xdes,ydes);
}

void DrawInsertionWindow(HDC hdc,int cxClient,int cyClient)
{
	HPEN hPen;
    HBRUSH hBrush;

	hPen = CreatePen(PS_SOLID,1,RGB(255,105,180));
    SelectObject(hdc,hPen);

	hBrush = CreateSolidBrush(RGB(255,255,191));
	SelectObject(hdc,hBrush);
	Rectangle(hdc,0,0,cxClient,cyClient);					//Whole window rectangle
	DrawLineUtil(hdc,0,70,cxClient,70);
	DrawLineUtil(hdc,0,380,cxClient,380);
	DrawLineUtil(hdc,250,575,600,475);
	DrawLineUtil(hdc,250,575,600,575);
	DrawLineUtil(hdc,250,575,600,675);
	DrawLineUtil(hdc,950,575,1000,575);
	DrawLineUtil(hdc,1200,575,1250,575);
	DrawLineUtil(hdc,950,675,1000,675);
	DrawLineUtil(hdc,0,740,cxClient,740);

	hBrush = CreateSolidBrush(RGB(152,251,152));
	SelectObject(hdc,hBrush);
	Rectangle(hdc,50,90,250,140);			//Rectangle for concept

	Rectangle(hdc,50,550,250,600);			//For Details
	Rectangle(hdc,600,450,950,500);			//For In-place sorting
	Rectangle(hdc,600,550,950,600);			//Time Complexity
	Rectangle(hdc,600,650,950,700);			//Space Complexity
	Rectangle(hdc,1000,550,1200,600);		//Best
	Rectangle(hdc,1250,550,1520,600);		//Avg & worst
	Rectangle(hdc,1000,650,1200,700);		//next to Space complixity 

	PrintTextI(hdc,cxClient,cyClient);
	return;
}


void PrintTextI(HDC hdc,int cxClient,int cyClient)
{
	HFONT hMyFont;

	SetBkColor(hdc,RGB(152,251,152));
	SetTextColor(hdc,RGB(255,0,0));
	hMyFont = CreateFont(35,0,0,0,700,0,0,0,0,0,0,0,FF_DONTCARE,"Arial Bold");
	SelectObject(hdc,hMyFont);

	TextOut(hdc,(cxClient/2)-138,20,TEXT("INSERTION SORT"),strlen(TEXT("INSERTION SORT")));
	TextOut(hdc,75,100,TEXT("CONCEPT"),strlen(TEXT("CONCEPT")));
	TextOut(hdc,80,558,TEXT("DETAILS"),strlen(TEXT("DETAILS")));
	
	SetBkColor(hdc,RGB(255,255,191));
	TextOut(hdc, 50, cyClient -70, TEXT("TO PROCEED FURTHER, CLICK HERE"),strlen("TO PROCEED FURTHER, CLICK HERE"));

	SetBkColor(hdc,RGB(152,251,152));
	hMyFont = CreateFont(30,0,0,0,700,0,0,0,0,0,0,0,FF_DONTCARE,"Arial Bold");
	SelectObject(hdc,hMyFont);
	SetTextColor(hdc,RGB(0,0,0));
	TextOut(hdc,630,457,TEXT("IN-PLACE SORTING"),strlen(TEXT("IN-PLACE SORTING")));
	TextOut(hdc,630,557,TEXT("TIME COMPLEXITY"),strlen(TEXT("TIME COMPLEXITY")));
	TextOut(hdc,630,657,TEXT("SPACE COMPLEXITY"),strlen(TEXT("SPACE COMPLEXITY")));
	TextOut(hdc,1020,557,TEXT("BEST = O(n)"),strlen(TEXT("BEST = O(n)")));
	TextOut(hdc,1255,557,TEXT("AVG/WORST = O(n^2)"),strlen(TEXT("AVG/WORST = O(n^2)")));
	TextOut(hdc,1070,657,TEXT("O(1)"),strlen(TEXT("O(1)")));

	SetBkColor(hdc,RGB(255,255,191));
	SetTextColor(hdc,RGB(0,0,0));
	TextOut(hdc,50,155,TEXT("I] Considers one element from given data set(key)."),
				strlen(TEXT("I] Considers one element from given data set(key).")));
	
	TextOut(hdc,50,195,TEXT("II] Checks it with the largest data from previously sorted list."),
				strlen(TEXT("II] Checks it with the largest data from previously sorted list.")));
	
	TextOut(hdc,50,235,TEXT("III] If the key is smaller, shifts all large values to create space & insert it at correct position."),
				strlen(TEXT("III] If the key is smaller, shifts all large values to create space & insert it at correct position.")));
	
	TextOut(hdc,50,275,TEXT("IV] If key is greater,leaves it at its place & considers nest element for comparison."),
				strlen(TEXT("IV] If key is greater,leaves it at its place & considers nest element for comparison.")));
	
	TextOut(hdc,50,315,TEXT("v] Repeats until all elements are covered."),
				strlen(TEXT("v] Repeats until all elements are covered.")));


	return;
}