#include<Windows.h>
#include<stdio.h>
#include<tchar.h>
#include<process.h>

#include"DebuggingOfSorting.h"

#pragma comment(lib,"gdi32.lib")
#pragma comment(lib,"user32.lib")
#pragma comment(lib,"kernel32.lib")
#pragma comment(lib, "Winmm.lib")

#define ARRAY_SIZE(X)   (sizeof(X)/sizeof(X[0]))
#define BOX_HEIGHT      40
#define BOX_LENGTH      60

#define HEIGHT          600
#define WIDTH           1000

void PlayMusic( void * lpParam );
int FormatedTextOut(HDC hdc,int xPos,int yPos,TCHAR* ap_format,...);
LRESULT CALLBACK WndProc(HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM lParam);

/*	START : Global declarations	*/
LP_INSERTION_SORT_VECTOR g_insertionVector;

int single_line_height = 100;
int g_screen_width;
int g_screen_height;

PSTRINGVECTOR gpStrVec = NULL;
const TCHAR DialogClassName[] = TEXT("DialogClass");

int g_arr[MAX];
int g_CharWidth;
HWND g_MainHwnd;

/*	END : Global declarations	*/

LRESULT CALLBACK DlgProc(HWND hDlg,UINT uMsg,WPARAM wParam,LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd)
{
   
    static TCHAR szClassName[] = TEXT("version1");
    static TCHAR szWindowCaption[] = TEXT("Debugging Of Sorting v1");

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
    g_screen_width = GetSystemMetrics(SM_CXSCREEN);
    g_screen_height = GetSystemMetrics(SM_CYSCREEN);
    hwnd = CreateWindowEx(
                    WS_EX_APPWINDOW,
                    szClassName,
                    szWindowCaption,
                    WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_OVERLAPPEDWINDOW,
                    0-10,
                    0,
                    g_screen_width+20,
                    g_screen_height,
                    (HWND)NULL,
                    (HMENU)NULL,
                    hInstance,
                    NULL
                    );

    if(NULL == hwnd){
        MessageBox((HWND)NULL,TEXT("Could not create application window"),TEXT("CreateWindowEx"),MB_ICONERROR);
        return(EXIT_FAILURE);
    }
    
    //ShowWindow(hwnd,nShowCmd);
    //AnimateWindow(hwnd,7000,AW_VER_NEGATIVE);
	AnimateWindow(hwnd,10000,AW_VER_POSITIVE);
    UpdateWindow(hwnd);

    while(GetMessage(&msg,(HWND)NULL,0,0)){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return((int)msg.wParam);
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
 {
    HDC hdc;
    PAINTSTRUCT ps;

    RECT rc;
    HDC hdcComp;
    BITMAP bmBuffer;
    
    static int cxClient;
    static int cyClient;
    static HBITMAP hbmap;
    static HINSTANCE hInst;
    
    static HWND hImage;
    HBITMAP hBitmap;
	

	/*GetDataFromUser*/
	 WNDCLASSEX wc;
	 static HWND hBtn;
	 static HWND hWndDlgBox;
	 static HWND hShowSortBtn;

	 /*Show Algorithm*/
	 static int cxChar;
	 static int cyChar;
	 static int cxCaps;
	 TEXTMETRIC tm;
	 static int iFlagInsertionSort = FALSE;
	 
	 /*InsertionSort*/
	 static int xPosInsertionSort;
	 static int yPosInsertionSort;
	 static int iInsertionCounter;
	 int line1;
	 int line2;

	 /*QuickSort*/
	 static int xPosQuickSort;
	 static int yPosQuickSort;
	 static int iQuickCounter;
	 int height = 0;

	 /*ScrollBar*/
	 SCROLLINFO si;
	 RECT rect;
 	 int i, x, y, iVertPos, iHorzPos, iPaintBeg, iPaintEnd;

    switch(uMsg)
    {
        case WM_CREATE:
        {
			/*START : SplashScreen*/
			
            _beginthread(PlayMusic,0,NULL);
			g_MainHwnd = hwnd;
            rc.left = 100;
            rc.top = 100;
            rc.right = 200;
            rc.bottom = 200;
            hdc = GetDC(hwnd);
            SetTextColor(hdc,RGB(255,0,0));
            ReleaseDC(hwnd,hdc);
            InvalidateRect(hwnd,NULL,FALSE);
            DrawText(hdc,TEXT("DEMO"),10,&rc,DT_CENTER);

            hBitmap = (HBITMAP)LoadImage(GetModuleHandle(NULL),"resources/hon_donald_knuth_1.bmp", 
                                  IMAGE_BITMAP, g_screen_width, g_screen_height, LR_LOADFROMFILE);

            hImage = CreateWindow("Static", " ", WS_TABSTOP | WS_VISIBLE | WS_CHILD |SS_BITMAP, 
                                    0, 0, g_screen_width, g_screen_height, hwnd, NULL, GetModuleHandle(NULL),NULL);

            SendMessage(hImage,STM_SETIMAGE,(WPARAM) IMAGE_BITMAP,(LPARAM)hBitmap);
            SendMessage(hImage,WM_PAINT,(WPARAM)0,(LPARAM)0);
            SetTimer(hwnd,END_SPLASH,1000,NULL);
			
			/*END : SplashScreen*/
			
			/*START : GetDataFromUser*/
			hInst = (HINSTANCE)((LPCREATESTRUCT)lParam)->hInstance;
            
            wc.cbSize           = sizeof(WNDCLASSEX);
            wc.style            = 0;
            wc.lpfnWndProc      = (WNDPROC)DlgProc;
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

			hBtn = CreateWindowEx(
									0,     
									TEXT("BUTTON"), 
									TEXT("Enter Data"), 
									WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 
									10, 
									10, 
									120, 
									20, 
									hwnd, 
									(HMENU)IDB_OPEN_DLG, 
									(HINSTANCE)hInst, 
									NULL
									);

            if (!hBtn)
            {
                MessageBox(NULL, TEXT("Button Failed."), TEXT("Error"), MB_OK | MB_ICONERROR);
                break;
            }
			ShowWindow(hBtn,FALSE);

			hShowSortBtn = CreateWindowEx(
									0,     
									TEXT("BUTTON"), 
									TEXT("Lets Start"), 
									WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 
									0, 
									0, 
									0, 
									0, 
									hwnd, 
									(HMENU)IDB_SHOW_SORTING, 
									(HINSTANCE)hInst, 
									NULL
									);

            if (!hBtn)
            {
                MessageBox(NULL, TEXT("Button Failed."), TEXT("Error"), MB_OK | MB_ICONERROR);
                break;
            }
			ShowWindow(hShowSortBtn,FALSE);
			/*END : GetDataFromUser*/

			/*START : ShowAlgorithm*/
			hdc = GetDC(hwnd);
			GetTextMetrics(hdc, &tm); 
			ReleaseDC(hwnd, hdc); 
			cxChar = tm.tmAveCharWidth; 
            cyChar = tm.tmHeight + tm.tmExternalLeading; 
			cxCaps = (tm.tmPitchAndFamily & 1 ? 3 : 2) * cxChar / 2;
			/*END : ShowAlgorithm*/

			
            break;

        }
        case WM_SIZE:
        {
			
            cxClient = LOWORD(lParam);
            cyClient = HIWORD(lParam);

			xPosInsertionSort = cxClient * 0.3 + 10;
            yPosInsertionSort = 10;

			xPosQuickSort = cxClient/3;
			yPosQuickSort = 5;

            break;
        }
        case WM_TIMER:
		{
			switch(LOWORD(wParam))
			{
				/*START : SplashScreen*/
				case END_SPLASH:
				{
					DestroyWindow(hImage);
					KillTimer(hwnd,END_SPLASH);
					SetFocus(hwnd);
					ShowWindow(hBtn,TRUE);
					break;
				}
				/*END : SplashScreen*/
				/*START : ShowInsertionSort*/
				case ID_TIMER_INSERTION:
                {
                   
                    line1 = g_insertionVector->pInsertionSort[iInsertionCounter].rangeObj.fromLine;
                    line2 = g_insertionVector->pInsertionSort[iInsertionCounter].rangeObj.toLine;
                    hdc = GetDC(hwnd);
                    
					//DrawInsertionTextOut(hdc, xPosInsertionSort, yPosInsertionSort, g_insertionVector->pInsertionSort[iInsertionCounter]);
					
                    DrawInsertionSort(hdc, xPosInsertionSort, yPosInsertionSort, g_insertionVector->pInsertionSort[iInsertionCounter]);
					PaintDesign(hdc,cxClient,cyClient);
					PrintAlgorithm(hdc, cyChar, cxCaps);
					PrintArrow(hdc,line1,line2, cyChar, cxCaps); 
					  //Testing Purpose
					ReleaseDC(hwnd,hdc);

					yPosInsertionSort += getHeightSquare();
                    iInsertionCounter++;
                    if(iInsertionCounter == g_insertionVector->iVectorSize)
                    {
						KillTimer(hwnd,ID_TIMER_INSERTION);
						SendMessage(hwnd,WM_COMMAND,MAKELPARAM(ID_SHOW_CREDIT_SCREEN,0),0);
					}
                    break;
                }
				/*END : ShowInsertionSort*/

				/*START : ShowQuickSort*/
				case ID_TIMER_QUICK:
				{
					hdc = GetDC(hwnd);
					//FormatedTextOut(hdc,xPosQuickSort,yPosQuickSort, (TCHAR*)("VS:[%d]"),g_pQuicksortVector->iVectorSize);
					//FormatedTextOut(hdc,xPosQuickSort+100,yPosQuickSort, (TCHAR*)("cnt:[%d]"),iQuickCounter);
					height = AddLineToUI(xPosQuickSort,yPosQuickSort, hdc, g_pQuicksortVector->pQuickSortData[iQuickCounter]);
					//DisplayQuicksort(hdc,xPosQuickSort,yPosQuickSort,g_pQuicksortVector->pQuickSortData[iQuickCounter]);
					//height = 20;
					yPosQuickSort += height;
					PaintDesign(hdc,cxClient,cyClient);
					PrintAlgorithm(hdc, cyChar, cxCaps);
					ReleaseDC(hwnd,hdc);
					iQuickCounter++;
					if(iQuickCounter == g_pQuicksortVector->iVectorSize)
					{
                        KillTimer(hwnd,ID_TIMER_QUICK);
						SendMessage(hwnd,WM_COMMAND,MAKELPARAM(ID_SHOW_CREDIT_SCREEN,0),0);
					}
					break;
				}
				/*END : ShowQuickSort*/
			}
			

            break;
		}
        case WM_PAINT:
        {
            hdc = BeginPaint(hwnd,&ps);
            if(TRUE == iFlagInsertionSort)
			{
				
			}
            EndPaint(hwnd,&ps);
            break;
        }
		 case WM_COMMAND:
        {
			switch(LOWORD(wParam))
			{
				/*START : GetDataFromUser*/
				case IDB_OPEN_DLG:
				{
					ShowWindow(g_MainHwnd,FALSE);
					hWndDlgBox = CreateWindowEx(
									WS_EX_DLGMODALFRAME | WS_EX_TOPMOST,
									TEXT("DialogClass"),
									TEXT("Data For Sorting"),
									 WS_VISIBLE | WS_POPUP | WS_CAPTION, 
									(g_screen_width/2) - (DIALOG_WIDTH/2), 
									(g_screen_height/2)- (DIALOG_HEIGHT/2), 
									DIALOG_HEIGHT, 
									DIALOG_WIDTH, 
									hwnd, 
									NULL, 
									(HINSTANCE)hInst, 
									NULL);
					if (!hWndDlgBox)
					{
						MessageBox(NULL, TEXT("Dialog Box Failed."), TEXT("Error"), MB_ICONERROR);
						break;
					}
					InvalidateRect(hwnd,NULL,TRUE);
					SetWindowPos(hShowSortBtn,HWND_BOTTOM,300,300,100,20,SWP_SHOWWINDOW);
					ShowWindow(hBtn,FALSE);
					DestroyWindow(hBtn);
					hBtn = NULL;
					break;
				}
				/*END : GetDataFromUser*/

				/*START : GetDataFromUser*/
				case IDB_SHOW_SORTING:
				{
					if(SELECT == g_sortTypeSelection[0])
					{
						SendMessage(hwnd,WM_COMMAND,MAKELPARAM(ID_SHOW_INSERTION,0),0);
					}
					else if(SELECT == g_sortTypeSelection[1])
					{
						SendMessage(hwnd,WM_COMMAND,MAKELPARAM(ID_SHOW_QUICK,0),0);
					}
					ShowWindow(hShowSortBtn,FALSE);
					DestroyWindow(hShowSortBtn);
					hShowSortBtn = NULL;

					hdc = GetDC(hwnd);
					//FormatedTextOut(hdc,50,100,"%d %d %d %d %d",g_arr[0],g_arr[1],g_arr[2],g_arr[3],g_arr[4]);
					ReleaseDC(hwnd,hdc);
					break;
				}
				/*END : GetDataFromUser*/

				/*START : ShowInsertion*/
				case ID_SHOW_INSERTION :
				{
					//MessageBox(hwnd,TEXT("INSERTION SORT"),TEXT("LOG"),MB_OK);
					
					if(gpStrVec != NULL)
					{
						DestroyStringVector(gpStrVec);
						gpStrVec = NULL;
					}

					gpStrVec = ReadFileInMemory("resources/insertion_algorithm.txt");
					
					FAIL_EXIT_IF(gpStrVec == NULL, "String vector gives error", "ReadFileInMemory");  

					hdc = GetDC(hwnd);
					PaintDesign(hdc,cxClient,cyClient);
					PrintAlgorithm(hdc, cyChar, cxCaps);

					g_insertionVector = CreateInsertionSortVector();
					InsertionSortInMemory(g_arr,N);
					
					iFlagInsertionSort = TRUE;
					//InvalidateRect(hwnd,NULL,TRUE);
					header(hdc, cxClient,cyClient,g_insertionVector->pInsertionSort[0]);
					ReleaseDC(hwnd,hdc);

					si.cbSize = sizeof(SCROLLINFO);
					si.fMask = SIF_RANGE | SIF_PAGE | SIF_POS;
					si.nMin = 0;
					si.nMax = g_insertionVector->iVectorSize - 1;
					si.nPage = cyClient / single_line_height;
					SetScrollInfo(hwnd, SB_VERT, &si, TRUE);

					SetTimer(hwnd,ID_TIMER_INSERTION,1000,(TIMERPROC)NULL);
					break;
				}
				/*END : ShowInsertion*/

				/*START : ShowQuick*/
				case ID_SHOW_QUICK:
				{
					//MessageBox(hwnd,TEXT("QUICK SORT"),TEXT("LOG"),MB_OK);
					if(gpStrVec != NULL)
					{
						DestroyStringVector(gpStrVec);
						gpStrVec = NULL;
					}

					gpStrVec = ReadFileInMemory("resources/quick_sort_algorithm.txt");
					
					FAIL_EXIT_IF(gpStrVec == NULL, "String vector gives error", "ReadFileInMemory");  

					hdc = GetDC(hwnd);
					PaintDesign(hdc,cxClient,cyClient);
					PrintAlgorithm(hdc, cyChar, cxCaps);
					ReleaseDC(hwnd,hdc);

					g_pQuicksortVector = CreateQuicksortVector();
					if(g_pQuicksortVector == NULL)
					{
						exit(-1);
					}
					QuickSortInMemory(g_arr,N);
					SetTimer(hwnd,ID_TIMER_QUICK,1000,(TIMERPROC)NULL);
					break;
				}
				/*END : ShowQuick*/

				/*START : ShowCreditScreen*/
				case ID_SHOW_CREDIT_SCREEN:
				{
					InvalidateRect(hwnd,NULL,TRUE);
					break;
				}
				/*END : ShowCreditScreen */
			}
			break;
		}
		case WM_VSCROLL:
		{
			si.cbSize = sizeof(si);
			si.fMask = SIF_ALL;
			GetScrollInfo(hwnd, SB_VERT, &si);

			iVertPos = si.nPos;

			switch(LOWORD(wParam))
			{
				case SB_TOP:
					si.nPos = si.nMin;
					break;

				case SB_BOTTOM:
					si.nPos = si.nMax;
					break;

				case SB_LINEUP:
					si.nPos -= 1;
					break;

				case SB_LINEDOWN:
					si.nPos += 1;
					break;
			}

			si.fMask = SIF_ALL;
			SetScrollInfo(hwnd, SB_VERT, &si, TRUE);
			GetScrollInfo(hwnd, SB_VERT, &si);

			// SP: Coordinates of valid rectangle
			rect.left = cxClient * 0.2;
            rect.top = cyClient * 0.2;
            rect.right = cxClient;
            rect.bottom = cyClient;

			if(si.nPos != iVertPos)
			{
				ScrollWindow(hwnd, 0, single_line_height * (iVertPos - si.nPos), &rect, &rect);
				//ScrollWindow(hwnd, 0, 30 * (iVertPos - si.nPos), NULL, NULL);
				UpdateWindow(hwnd);
			}
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


void PlayMusic( void * lpParam )
{
	if(TRUE != PlaySound(TEXT("resources/01_Contra.wav"),NULL,SND_ASYNC|SND_NODEFAULT))
	{
		MessageBox(NULL,TEXT("PlaySound FAIELD"),TEXT("ERROR"),MB_ICONERROR);
		_endthread();
	}
	_endthread();
}
