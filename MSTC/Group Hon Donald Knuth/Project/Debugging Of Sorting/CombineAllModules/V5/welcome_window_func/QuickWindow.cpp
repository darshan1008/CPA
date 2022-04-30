#include<Windows.h>

#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "kernel32.lib")

int screen_width;
int screen_height;

void PrintTextQ(HDC hdc,int cxClient,int cyClient);
void DrawQuickWindow(HDC,int,int);
void DrawLineUtil(HDC,int,int,int,int);

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	static TCHAR szClassName[] = TEXT("Quick Sort");
	static TCHAR szWindowCaption[] = TEXT("Quick Sort");

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
							760, 
							790, 
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
				
			DrawQuickWindow(hdc,cxClient,cyClient);
			

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

void DrawQuickWindow(HDC hdc,int cxClient,int cyClient)
{
	HPEN hPen;
    HBRUSH hBrush;

	hPen = CreatePen(PS_SOLID,1,RGB(255,105,180));
    SelectObject(hdc,hPen);

	hBrush = CreateSolidBrush(RGB(255,255,191));
	SelectObject(hdc,hBrush);
	Rectangle(hdc,0,0,cxClient,cyClient);					//Whole window rectangle
	DrawLineUtil(hdc,0,70,cxClient,70);
	DrawLineUtil(hdc,0,355,cxClient,355);
	DrawLineUtil(hdc,250,575,600,400);
	DrawLineUtil(hdc,250,575,600,575);
	DrawLineUtil(hdc,250,575,600,750);
	DrawLineUtil(hdc,950,575,1000,575);
	DrawLineUtil(hdc,1200,575,1250,575);
	DrawLineUtil(hdc,950,750,1000,750);
	DrawLineUtil(hdc,150,550,150,420);
	DrawLineUtil(hdc,150,600,150,730);
	DrawLineUtil(hdc,0,cyClient-50,cxClient,cyClient-50);

	hBrush = CreateSolidBrush(RGB(152,251,152));
	SelectObject(hdc,hBrush);
	Rectangle(hdc,50,90,250,140);			//Rectangle for concept

	Rectangle(hdc,50,550,250,600);			//For Details
	Rectangle(hdc,50,380,350,420);			//For In-place sorting
	Rectangle(hdc,50,730,360,770);			//Developed by

	Rectangle(hdc,600,380,950,420);			//For Divide and conqure
	Rectangle(hdc,600,550,950,600);			//Time Complexity
	Rectangle(hdc,600,730,950,770);			//Space Complexity
	Rectangle(hdc,1000,550,1230,600);		//Best
	Rectangle(hdc,1250,550,1520,600);		//Avg & worst
	Rectangle(hdc,1000,730,1200,770);		//next to Space complixity

	PrintTextQ(hdc,cxClient,cyClient);
	return;
}


void PrintTextQ(HDC hdc,int cxClient,int cyClient)
{
	HFONT hMyFont;

	SetBkColor(hdc,RGB(152,251,152));
	SetTextColor(hdc,RGB(255,0,0));
	hMyFont = CreateFont(35,0,0,0,700,0,0,0,0,0,0,0,FF_DONTCARE,"Arial Bold");
	SelectObject(hdc,hMyFont);

	TextOut(hdc,(cxClient/2)-138,20,TEXT("QUICK SORT"),strlen(TEXT("QUICK SORT")));
	TextOut(hdc,75,100,TEXT("CONCEPT"),strlen(TEXT("CONCEPT")));
	TextOut(hdc,80,558,TEXT("DETAILS"),strlen(TEXT("DETAILS")));
	
	SetBkColor(hdc,RGB(255,255,191));
	TextOut(hdc, 50, cyClient -45, TEXT("TO PROCEED FURTHER, CLICK HERE"),strlen("TO PROCEED FURTHER, CLICK HERE"));

	SetBkColor(hdc,RGB(152,251,152));
	hMyFont = CreateFont(30,0,0,0,700,0,0,0,0,0,0,0,FF_DONTCARE,"Arial Bold");
	SelectObject(hdc,hMyFont);
	SetTextColor(hdc,RGB(0,0,0));

	TextOut(hdc,630,386,TEXT("DIVIDE AND CONQUER"),strlen(TEXT("DIVIDE AND CONQUER")));
	TextOut(hdc,75,386,TEXT("IN-PLACE SORTING"),strlen(TEXT("IN-PLACE SORTING")));
	TextOut(hdc,650,560,TEXT("TIME COMPLEXITY"),strlen(TEXT("TIME COMPLEXITY")));
	TextOut(hdc,650,735,TEXT("SPACE COMPLEXITY"),strlen(TEXT("SPACE COMPLEXITY")));
	TextOut(hdc,1003,557,TEXT("BEST = O(n*log(n))"),strlen(TEXT("BEST = O(n*log(n))")));
	TextOut(hdc,1275,557,TEXT("WORST = O(n^2)"),strlen(TEXT("WORST = O(n^2)")));
	TextOut(hdc,1050,735,TEXT("O(log n)"),strlen(TEXT("O(log n)")));
	TextOut(hdc,52,735,TEXT("Developed by Tony Hoare"),strlen(TEXT("Developed by Tony Hoare")));

	SetBkColor(hdc,RGB(255,255,191));
	SetTextColor(hdc,RGB(0,0,0));
	TextOut(hdc,50,155,TEXT("I] Selects pivot element from given dataset."),
				strlen(TEXT("I] Selects pivot element from given dataset.")));
	
	TextOut(hdc,50,195,TEXT("II] Pivot partitions the data into 2 non-empty sets."),
				strlen(TEXT("II] Pivot partitions the data into 2 non-empty sets.")));
	
	TextOut(hdc,50,235,TEXT("III] Comparison of pivot with every data element brings pivot at a position where leftside values are less and rightside"),
				strlen(TEXT("III] Comparison of pivot with every data element brings pivot at a position where leftside values are less and rightside")));
	
	TextOut(hdc,50,275,TEXT("      values are greater than it."),
				strlen(TEXT("      values are greater than it.")));
	
	TextOut(hdc,50,315,TEXT("v] Recursively executes step 3 for generated 2 sets."),
				strlen(TEXT("v] Recursively executes step 3 for generated 2 sets.")));

	return;
}