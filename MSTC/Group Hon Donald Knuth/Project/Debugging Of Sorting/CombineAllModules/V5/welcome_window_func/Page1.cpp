#include<Windows.h>

#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "kernel32.lib")

int screen_width;
int screen_height;


void PrintText(HDC,int,int);
void DrawLineUtil(HDC,int,int,int,int);
void DrawWelcomeWindow(HDC,int,int);

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	static TCHAR szClassName[] = TEXT("Sorting");
	static TCHAR szWindowCaption[] = TEXT("Sorting");

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
							770, 
							785, 
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
				
			DrawWelcomeWindow(hdc,cxClient,cyClient);
			

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

void DrawWelcomeWindow(HDC hdc,int cxClient,int cyClient)
{
	HPEN hPen;
    HBRUSH hBrush;

	hPen = CreatePen(PS_SOLID,1,RGB(255,105,180));
    SelectObject(hdc,hPen);

	hBrush = CreateSolidBrush(RGB(255,255,191));
	SelectObject(hdc,hBrush);
	Rectangle(hdc,0,0,cxClient,cyClient);					//Whole window rectangle
	DrawLineUtil(hdc,0,cyClient-60,cxClient,cyClient-60);
	DrawLineUtil(hdc,cxClient/2,0,cxClient/2,cyClient-60);
		
	hBrush = CreateSolidBrush(RGB(152,251,152));
	SelectObject(hdc,hBrush);
	Rectangle(hdc,50,30,250,80);									//Left 1st level 
	Rectangle(hdc,(cxClient/2)+50,30,(cxClient/2)+250,80);			//Right 1st level
	Rectangle(hdc,(cxClient/4)-100,((cyClient-360)/2)+300,(cxClient/4)+120,((cyClient-360)/2)+360); //left 4th level	

	hBrush = CreateSolidBrush(RGB(255,228,255));
	SelectObject(hdc,hBrush);
	Rectangle(hdc,50,120,(cxClient/2)-40,300);						//Left second level 

	Ellipse(hdc,1340,110,1500,200);
	Ellipse(hdc,1340,220,1500,310);
	Ellipse(hdc,1340,330,1500,420);
	Ellipse(hdc,1340,440,1500,530);
	Ellipse(hdc,1340,550,1500,640);
	Ellipse(hdc,1340,660,1500,750);

	Rectangle(hdc,50,380,230,450);									//left 3rd level 1st
	Rectangle(hdc,((cxClient/2)-40)-180,380,(cxClient/2)-40,450);	//left 3rd level 2nd
	Rectangle(hdc,50,660,230,730);									//left 5th level 1st
	Rectangle(hdc,((cxClient/2)-40)-180,660,(cxClient/2)-40,730);	//left 5th level 2st

	DrawLineUtil(hdc,230,450,(cxClient/4)-100,((cyClient-360)/2)+300);
	DrawLineUtil(hdc,((cxClient/4)+120),((cyClient-360)/2)+300,((cxClient/2)-40)-180,450);
	DrawLineUtil(hdc,(cxClient/4)-100,((cyClient-360)/2)+360,230,660);
	DrawLineUtil(hdc,((cxClient/2)-40)-180,660,(cxClient/4)+120,((cyClient-360)/2)+360);
	
	PrintText(hdc,cxClient,cyClient);
	return;
}

void PrintText(HDC hdc,int cxClient,int cyClient)
{
	HFONT hMyFont;

	SetBkColor(hdc,RGB(152,251,152));
	SetTextColor(hdc,RGB(255,0,0));
	hMyFont = CreateFont(35,0,0,0,700,0,0,0,0,0,0,0,FF_DONTCARE,"Arial Bold");
	SelectObject(hdc,hMyFont);

	TextOut(hdc,85,40,TEXT("SORTING"),strlen(TEXT("SORTING")));
	TextOut(hdc,(cxClient/2)+85,40,TEXT("TYPES"),strlen(TEXT("TYPES")));
	
	SetBkColor(hdc,RGB(255,255,191));
	TextOut(hdc, 50, cyClient -50, TEXT("TO PROCEED FURTHER, ENTER YOUR DATA"),strlen("TO PROCEED FURTHER, ENTER YOUR DATA"));

	SetBkColor(hdc,RGB(152,251,152));
	hMyFont = CreateFont(25,0,0,0,700,0,0,0,0,0,0,0,FF_DONTCARE,"Arial Bold");
	SelectObject(hdc,hMyFont);
	TextOut(hdc,(cxClient/4)-90,((cyClient-360)/2)+315,TEXT("CHARACTERISTICS"),strlen(TEXT("CHARACTERISTICS")));

	SetBkColor(hdc,RGB(255,228,255));
	SetTextColor(hdc,RGB(0,0,0));
	hMyFont = CreateFont(35,0,0,0,700,0,0,0,0,0,0,0,FF_DONTCARE,"Arial Bold");
	SelectObject(hdc,hMyFont);
	TextOut(hdc,60,130,TEXT("1] Elements listed in order"),strlen(TEXT("1] Elements listed in order")));
	TextOut(hdc,60,199,TEXT("2] Permutations of the original inputs"),strlen(TEXT("2] Permutations of the original inputs")));
	TextOut(hdc,60,230,TEXT("     elements with order"),strlen(TEXT("     elements with order")));

	hMyFont = CreateFont(25,0,0,0,700,0,0,0,0,0,0,0,FF_DONTCARE,"Arial Bold");
	SelectObject(hdc,hMyFont);
	TextOut(hdc,1365,142,TEXT("INSERTION"),strlen(TEXT("INSERTION")));
	TextOut(hdc,1380,252,TEXT("MERGE"),strlen(TEXT("MERGE")));
	TextOut(hdc,1385,362,TEXT("HEAP"),strlen(TEXT("HEAP")));
	TextOut(hdc,1380,472,TEXT("BUBBLE"),strlen(TEXT("BUBBLE")));
	TextOut(hdc,1385,582,TEXT("SHELL"),strlen(TEXT("SHELL")));
	TextOut(hdc,1383,692,TEXT("QUICK"),strlen(TEXT("QUICK")));
	TextOut(hdc,110,390,TEXT("TIME"),strlen(TEXT("TIME")));
	TextOut(hdc,80,420,TEXT("COMPLEXITY"),strlen(TEXT("COMPLEXITY")));
	TextOut(hdc,((cxClient/2)-40)-130,390,TEXT("SPACE"),strlen(TEXT("SPACE")));
	TextOut(hdc,((cxClient/2)-40)-150,420,TEXT("COMPLEXITY"),strlen(TEXT("COMPLEXITY")));
	TextOut(hdc,90,670,TEXT("MEMORY"),strlen(TEXT("MEMORY")));
	TextOut(hdc,70,700,TEXT("REQUIREMENT"),strlen(TEXT("REQUIREMENT")));
	TextOut(hdc,((cxClient/2)-40)-178,680,TEXT("RECURSIVENESS"),strlen(TEXT("RECURSIVENESS")));

	SetBkColor(hdc,RGB(255,255,191));
	SetTextColor(hdc,RGB(0,0,0));
	TextOut(hdc,(cxClient/2)+50,142,TEXT("I] Simple,good for small data sets."),strlen(TEXT("I] Simple,good for small data sets.")));
	TextOut(hdc,(cxClient/2)+50,252,TEXT("II] Merging based on sorted lists.(Step-by-Step)"),strlen(TEXT("II] Merging based on sorted lists.(Step-by-Step)")));
	TextOut(hdc,(cxClient/2)+50,362,TEXT("III] Selection sorts improved version."),strlen(TEXT("III] Selection sorts improved version.")));
	TextOut(hdc,(cxClient/2)+50,472,TEXT("IV] Swaping between consecutive elements."),strlen(TEXT("IV] Swaping between consecutive elements.")));
	TextOut(hdc,(cxClient/2)+50,582,TEXT("V] Insertion sorts improved version."),strlen(TEXT("V] Insertion sorts improved version.")));
	TextOut(hdc,(cxClient/2)+50,692,TEXT("VI] Good for relatively large data."),strlen(TEXT("VI] Good for relatively large data.")));

	return;
}