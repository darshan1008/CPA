#include<Windows.h>
#include<stdio.h>
#include<tchar.h>
#include<process.h>

#define VERSION		"V8"

#include"DebuggingOfSorting.h"

#pragma comment(lib,"gdi32.lib")
#pragma comment(lib,"user32.lib")
#pragma comment(lib, "Winmm.lib")
#pragma comment(lib,"kernel32.lib")

#define ARRAY_SIZE(X)   (sizeof(X)/sizeof(X[0]))
#define BOX_HEIGHT      40
#define BOX_LENGTH      60

#define HEIGHT          600
#define WIDTH           1000

void MusicSplashScreen( void * lpParam );
int FormatedTextOut(HDC hdc,int xPos,int yPos,TCHAR* ap_format,...);
LRESULT CALLBACK WndProc(HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM lParam);
void PlayMusicForCreditScreen(void* lpParam);

/*	START : Global declarations	*/
LP_INSERTION_SORT_VECTOR g_insertionVector;

int g_single_line_height = 100;
static int g_screen_width;
static int g_screen_height;

PSTRINGVECTOR g_pStrVec = NULL;
TCHAR DialogClassName[] = TEXT("DialogClass");

int g_arr[MAX];
int g_CharWidth;
HWND g_MainHwnd;

// Semaphore to synchronise 'Sound' threads in insertion sort
HANDLE ghSemaphore;		

/*	END : Global declarations	*/

LRESULT CALLBACK DlgProc(HWND hDlg,UINT uMsg,WPARAM wParam,LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd)
{
    static TCHAR szClassName[] = TEXT("class name");
    static TCHAR szWindowCaption[] = TEXT("Debugging Of Sorting " VERSION);

	HWND hwnd = NULL;
    HICON hIcon  = NULL;
    HICON hIconSm = NULL;
	HBRUSH hBrush = NULL;
	HCURSOR hCursor = NULL;

    MSG msg;
    WNDCLASSEX wndEx;

	/*	Create a global semaphore sync object for
		sound threads synchronisation in 'Insertion Sort' */
	ghSemaphore = CreateSemaphore(NULL, 1, 1, NULL);
	if (NULL == ghSemaphore)
	{
		return(EXIT_FAILURE);
	}
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

    hIcon = LoadIcon(hInstance,(LPCSTR)IDI_ICON_1);
    if(NULL == hIcon){
        MessageBox((HWND)NULL,TEXT("Could not obtain icon"),TEXT("LoadIcon"),MB_ICONERROR);
        return(EXIT_FAILURE);
    }

    hIconSm =LoadIcon(hInstance,(LPCSTR)IDI_ICON_1);
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

#define MAIN_WND_WIDTH		1380
#define MAIN_WND_HEIGHT		750

    g_screen_width = GetSystemMetrics(SM_CXSCREEN);
    g_screen_height = GetSystemMetrics(SM_CYSCREEN);
    hwnd = CreateWindowEx(
                    WS_EX_APPWINDOW,
                    szClassName,
                    szWindowCaption,
                    /*WS_VSCROLL|*/WS_MAXIMIZE|WS_OVERLAPPEDWINDOW | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME ,
                    0,/*CW_USEDEFAULT,(g_screen_width/2 - MAIN_WND_WIDTH/2),*/
					0,/*CW_USEDEFAULT,(g_screen_height/2 - MAIN_WND_HEIGHT/2),*/
					MAIN_WND_WIDTH, /*CW_USEDEFAULT,*/		//g_screen_width + 30, //CW_USEDEFAULT
					MAIN_WND_HEIGHT,/*CW_USEDEFAULT,*/		//g_screen_height - 10,//CW_USEDEFAULT
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
	AnimateWindow(hwnd,6000,AW_VER_POSITIVE);
    UpdateWindow(hwnd);

    while(GetMessage(&msg,(HWND)NULL,0,0)){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

	CloseHandle(ghSemaphore);
    return((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
 {
    HDC hdc;
    PAINTSTRUCT ps;

    RECT rc;
    HDC hdcComp;
    BITMAP bmBuffer;
    
	static HBITMAP hbmap;
	static HINSTANCE hInst;
	static int cxClient = MAIN_WND_WIDTH - 50;
	static int cyClient = MAIN_WND_HEIGHT - 50;
    
	HBITMAP hBitmap;
    static HWND hImage;
    
	/*GetDataFromUser*/
	WNDCLASSEX wc;
	static HWND hBtn;
	static HWND hWndDlgBox;
	static HWND hLetsStartBtn;

	/*Show Algorithm*/
	TEXTMETRIC tm;
	static int cxChar;
	static int cyChar;
	static int cxCaps;
	static int iFlagInsertionSort	= FALSE;
	static int iFlagBubbleSort		= FALSE;

	/**/
	int line1 = 0;
	int line2 = 0;
	int height = 0;

	/*InsertionSort*/
	static int xPosInsertionSort;
	static int yPosInsertionSort;
	static int iInsertionCounter;
	
	/*BubbleSort*/
	int xPosBubbleSort;
	int yPosBubbleSort;
	static int iBubbleCounter;

	int i;
	
	int iCounter2;
	static int iCounter;

	/**/
	static int iFlagWelcomeWindow = FALSE;
	static int iFlagShowSortingInfo = FALSE;
	HPEN hPen;
	HBRUSH hBrush;
	static HWND hWelcomeImage = NULL;

	static int vectorStartIndex = 0;

	static HWND hBtnNext;

	/*menu handling*/
	static HMENU hMainMenu = NULL;
	static HMENU hSubMenu_1[5];

    switch(uMsg)
    {
        case WM_CREATE:
		{
			/*START : SplashScreen*/

			{
				_beginthread(MusicSplashScreen, 0, NULL);
				g_MainHwnd = hwnd;
				rc.left = 100;
				rc.top = 100;
				rc.right = 200;
				rc.bottom = 200;
				hdc = GetDC(hwnd);
				SetTextColor(hdc, RGB(255, 0, 0));
				ReleaseDC(hwnd, hdc);
				InvalidateRect(hwnd, NULL, FALSE);
				
				hBitmap = (HBITMAP)LoadImage(GetModuleHandle(NULL), "resources/hon_donald_knuth_1.bmp",
					IMAGE_BITMAP, g_screen_width, g_screen_height, LR_LOADFROMFILE);

				hImage = CreateWindow("Static", " ", WS_TABSTOP | WS_VISIBLE | WS_CHILD | SS_BITMAP,
					0, 0, g_screen_width, g_screen_height, hwnd, NULL, GetModuleHandle(NULL), NULL);

				SendMessage(hImage, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hBitmap);
				SendMessage(hImage, WM_PAINT, (WPARAM)0, (LPARAM)0);
				SetTimer(hwnd, END_SPLASH, 10000, NULL);
			}
			/*END : SplashScreen*/

			/*START : GetDataFromUser*/

			{
				hInst = (HINSTANCE)((LPCREATESTRUCT)lParam)->hInstance;

				wc.cbSize = sizeof(WNDCLASSEX);
				wc.style = 0;
				wc.lpfnWndProc = (WNDPROC)DlgProc;
				wc.cbClsExtra = 0;
				wc.cbWndExtra = 0;
				wc.hInstance = (HINSTANCE)hInst;
				wc.hIcon = NULL;
				wc.hIconSm = NULL;
				wc.hCursor = LoadCursor(NULL, IDC_ARROW);
				wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
				wc.lpszMenuName = NULL;
				wc.lpszClassName = DialogClassName;
				if (!RegisterClassEx(&wc))
				{
					MessageBox(NULL, TEXT("Failed To Register The Dialog Class."), TEXT("Error"), MB_OK | MB_ICONERROR);
					break;
				}

				hBtn = CreateWindowEx(
					0,
					TEXT("BUTTON"),
					TEXT("Enter Data"),
					WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
					0,
					0,
					140,
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
				ShowWindow(hBtn, FALSE);

				hLetsStartBtn = CreateWindowEx(
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

				if (!hLetsStartBtn)
				{
					MessageBox(NULL, TEXT("Button Failed."), TEXT("Error"), MB_OK | MB_ICONERROR);
					break;
				}
				ShowWindow(hLetsStartBtn, FALSE);
			}

			/*END : GetDataFromUser*/


			/*next prev buttons*/
			hBtnNext = CreateWindowEx(
				0,
				TEXT("BUTTON"),
				TEXT("Next"),
				WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
				0,
				0,
				140,
				20,
				hwnd,
				(HMENU)IDB_NEXT_STEP_BUTTON,
				(HINSTANCE)hInst,
				NULL
			);

			if (!hBtnNext)
			{
				MessageBox(NULL, TEXT("Button Failed."), TEXT("Error"), MB_OK | MB_ICONERROR);
				break;
			}
			ShowWindow(hBtnNext, FALSE);

			/*START : ShowAlgorithm*/

			{
				hdc = GetDC(hwnd);
				GetTextMetrics(hdc, &tm);
				ReleaseDC(hwnd, hdc);
				cxChar = tm.tmAveCharWidth;
				cyChar = tm.tmHeight + tm.tmExternalLeading;
				cxCaps = (tm.tmPitchAndFamily & 1 ? 3 : 2) * cxChar / 2;
			}
			/*END : ShowAlgorithm*/

			/*START : Menu Handling */
			{
				hMainMenu = CreateMenu();
				hSubMenu_1[0] = CreateMenu();

				hSubMenu_1[2] = CreateMenu();
				AppendMenu(hSubMenu_1[2], MF_STRING, ID_GET_DATA, (LPCSTR)"&Enter Data");
				AppendMenu(hMainMenu, MF_POPUP, (UINT_PTR)hSubMenu_1[2], (LPCSTR)"&Show all");

				hSubMenu_1[3] = CreateMenu();
				AppendMenu(hMainMenu, MF_STRING, ID_EXIT, (LPCSTR)"&Exit");

				SetMenu(hwnd, hMainMenu);
			}
			/*END : Menu Handling */
            break;

        }
        
		case WM_SIZE:
        {
            cxClient = LOWORD(lParam);
            cyClient = HIWORD(lParam);
			
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
					SetWindowPos(hBtn, HWND_BOTTOM, 100, cyClient - 100, 140, 20, SWP_SHOWWINDOW);
					ShowWindow(hBtn,TRUE);
					
					iFlagWelcomeWindow = TRUE;

					InvalidateRect(hwnd,NULL,TRUE);
					break;
				}
				/*END : SplashScreen*/

				/*START : ShowInsertionSort*/
				case ID_TIMER_INSERTION:
                {
					if(iInsertionCounter >= g_insertionVector->iVectorSize)
                    {
						KillTimer(hwnd,ID_TIMER_INSERTION);
						SendMessage(hwnd,WM_COMMAND,MAKEWPARAM(ID_SHOW_CREDIT_SCREEN,0),0);
						break;
					}

					iFlagInsertionSort = TRUE;
					//iFlagBubbleSort = TRUE;
					//SendMessage(hwnd,WM_VSCROLL,MAKEWPARAM(SB_LINEDOWN,0),0);
					
					//MessageBox(hwnd,TEXT("ID_TIMER_INSERTION"),TEXT("Log"),MB_OK);

                    break;
                }
				/*END : ShowInsertionSort*/

				/*START : ShowBubbleSort*/
				case ID_TIMER_BUBBLE:
				{
					if (iBubbleCounter > g_bubbleVector->iVectorSize)
					{
						KillTimer(hwnd, ID_TIMER_BUBBLE);
						SendMessage(hwnd, WM_COMMAND, MAKELPARAM(ID_SHOW_CREDIT_SCREEN, 0), 0);
						break;
					}
					iFlagBubbleSort = TRUE;
					//iBubbleCounter++;
					//SendMessage(hwnd,WM_VSCROLL,MAKEWPARAM(SB_LINEDOWN,0),0);
					InvalidateRect(hwnd, NULL, TRUE);
					//MessageBox(hwnd, "ID_TIMER_BUBBLE", "ID_TIMER_BUBBLE", 0);
					break;
				}
				/*END : ShowBubbleSort*/				
			}
			
            break;
		}
        
		case WM_PAINT:
        {
            hdc = BeginPaint(hwnd,&ps);
			
			if(TRUE == iFlagWelcomeWindow)
			{
				iFlagWelcomeWindow = FALSE;
				DrawWelcomeWindow(hdc,cxClient,cyClient);
			}
			
			else if(TRUE == iFlagShowSortingInfo)
			{
				iFlagShowSortingInfo = FALSE;
				
				if(SELECT == g_sortTypeSelection[0]) //Insertion Sort
				{
					//Insertion Sort
				}
				else if(SELECT == g_sortTypeSelection[1]) //Quick Sort
				{
					//Quick Sort
				}
				
			}
			
			else if(TRUE == iFlagInsertionSort && iInsertionCounter < g_insertionVector->iVectorSize)
			{
				iFlagInsertionSort = FALSE;
				
				xPosInsertionSort = cxClient * 0.3 ;
  	       		yPosInsertionSort = 50;
				header(hdc,xPosInsertionSort, 0,g_insertionVector->pInsertionSort[0]);
			
				for(i = vectorStartIndex; i <= iInsertionCounter; ++i)
				{
					DrawInsertionSort(hdc, xPosInsertionSort, yPosInsertionSort, g_insertionVector->pInsertionSort[i]);
					PaintDesign(hdc,cxClient,cyClient);
					PrintAlgorithm(hdc, cyChar, cxCaps);

					yPosInsertionSort += 50;
				}
				if (yPosInsertionSort > cyClient - 100)
				{
					vectorStartIndex++;
				}
				line1 = g_insertionVector->pInsertionSort[i-1].rangeObj.fromLine;
				line2 = g_insertionVector->pInsertionSort[i-1].rangeObj.toLine;
				PrintArrow(hdc,line1,line2, cyChar, cxCaps); 

				/*TODO : PlaySound*/
				
				if (TRUE == g_insertionVector->pInsertionSort[i - 1].iSound1)
				{
					EnableWindow(hBtnNext, false);			// Disable 'Next' button	
					if (WAIT_OBJECT_0 == WaitForSingleObject(ghSemaphore, 0))
					{
						_beginthread(InsertionSortSound1, 0, NULL);
					}
					if (WAIT_OBJECT_0 == WaitForSingleObject(ghSemaphore, INFINITE))
					{
						EnableWindow(hBtnNext, true);		// Enable 'Next' button
						ReleaseSemaphore(ghSemaphore, 1, NULL);
					}
				}
				// Play sound (2)
				else if(TRUE == g_insertionVector->pInsertionSort[i - 1].iSound2)
				{
					EnableWindow(hBtnNext, false);			// Disable 'Next' button
					if (WAIT_OBJECT_0 == WaitForSingleObject(ghSemaphore, 0))
					{
						_beginthread(InsertionSortSound2, 0, NULL);
					}
					if (WAIT_OBJECT_0 == WaitForSingleObject(ghSemaphore, INFINITE))
					{
						EnableWindow(hBtnNext, true);		// Enable 'Next' button
						ReleaseSemaphore(ghSemaphore, 1, NULL);
					}
				}
				iInsertionCounter++;
			}
		
			else if (TRUE == iFlagBubbleSort)
			{
				iFlagBubbleSort = FALSE;
				
				PaintDesign(hdc, cxClient, cyClient); 
				PrintAlgorithm(hdc, cyChar, cxCaps);
				SetBkMode(hdc, TRANSPARENT);
				xPosBubbleSort = cxClient * 0.3 ;
				yPosBubbleSort = 30;
				for (iCounter = vectorStartIndex; iCounter < iBubbleCounter; iCounter++)
				{
					yPosBubbleSort += DrawBubbleSort(hdc, xPosBubbleSort, yPosBubbleSort, g_bubbleVector->pBubbleSort[iCounter]);
				}

				line1 = g_bubbleVector->pBubbleSort[iCounter].rangeObj.fromLine;
				line2 = g_bubbleVector->pBubbleSort[iCounter].rangeObj.toLine;
				PrintArrowForBubbleSort(hdc, line1, line2, cyChar, cxCaps);

				iBubbleCounter++;
				if (yPosBubbleSort > cyClient - 100)
					vectorStartIndex++;				
			}
			
			EndPaint(hwnd,&ps);
            break;
        }
		
		case WM_COMMAND:
        {
			switch(LOWORD(wParam))
			{
				/* START : GetDataFromUser */
				case IDB_OPEN_DLG:
				{
					/*ByPass this flow*/
					
					if(0)
					{
						g_arr[0] = 10;
						g_arr[1] = 40;
						g_arr[2] = 30;
						g_arr[3] = 20;
						g_arr[4] = 50;
						N = 5;

						SendMessage(hwnd, WM_COMMAND, MAKEWPARAM(ID_SHOW_INSERTION, 0), 0);
				
						ShowWindow(hBtn, FALSE);
						DestroyWindow(hBtn);
						hBtn = NULL;
						//g_sortTypeSelection[QUICK_SORT] = SELECT;
						//SetWindowPos(hBtnNext, HWND_BOTTOM, (3 * cxClient / 10) /2, cyClient - 100, 140, 20, SWP_SHOWWINDOW);
						//ShowWindow(hBtnNext, TRUE);
						//SendMessage(hwnd, WM_COMMAND, MAKEWPARAM(IDB_OPEN_DLG, 0), 0);
						//SendMessage(hwnd, WM_COMMAND, MAKEWPARAM(ID_SHOW_CREDIT_SCREEN, 0), 0);

						break;
					}
					
					iInsertionCounter = 0;
					iBubbleCounter = 0;
					EnableWindow(hBtnNext, true);
					ShowWindow(g_MainHwnd,FALSE);
					KillTimer(hwnd, ID_TIMER_BUBBLE);

					hWndDlgBox = CreateWindowEx(
									WS_EX_DLGMODALFRAME | WS_EX_TOPMOST,
									TEXT("DialogClass"),
									TEXT("Data For Sorting"),
									 WS_VISIBLE | WS_POPUP | WS_CAPTION, 
									(g_screen_width/2) - (DIALOG_WIDTH/2), 
									(g_screen_height/2)- (DIALOG_HEIGHT/2), 
									DIALOG_HEIGHT,
									DIALOG_WIDTH+40,
									hwnd, 
									NULL, 
									(HINSTANCE)hInst, 
									NULL);
					if (!hWndDlgBox)
					{
						MessageBox(NULL, TEXT("Dialog Box Failed."), TEXT("Error"), MB_ICONERROR);
						break;
					}

					iFlagWelcomeWindow = FALSE;
					InvalidateRect(hwnd,NULL,TRUE);

					ShowWindow(hBtn,FALSE);
					DestroyWindow(hBtn);
					hBtn = NULL;

					ShowWindow(hLetsStartBtn, FALSE);
					DestroyWindow(hLetsStartBtn);
					hLetsStartBtn = NULL;

					break;
				}
				/* END : GetDataFromUser */

				/*START : GetDataFromUser*/
				case IDB_SHOW_SORTING:
				{
					DestroyWindow(hWndDlgBox);
					hWndDlgBox = NULL;
					
					vectorStartIndex = 0;

					SetWindowPos(hBtnNext, HWND_BOTTOM, (3 * cxClient / 10) /2, cyClient - 100, 140, 20, SWP_SHOWWINDOW);
					ShowWindow(hBtnNext, TRUE);

					if(SELECT == g_sortTypeSelection[INSERTION_SORT])
					{
						SendMessage(hwnd,WM_COMMAND,MAKEWPARAM(ID_SHOW_INSERTION,0),0);
					}
					else if(SELECT == g_sortTypeSelection[BUBBLE_SORT])
					{
						SendMessage(hwnd, WM_COMMAND, MAKEWPARAM(ID_SHOW_BUBBLE, 0), 0);
					}
					
					break;
				}
				/*END : GetDataFromUser*/

				/*START : ShowInsertion*/
				case ID_SHOW_INSERTION :
				{
					if(g_pStrVec != NULL)
					{
						DestroyStringVector(g_pStrVec);
						g_pStrVec = NULL;
					}

					g_pStrVec = ReadFileInMemory("resources/insertion_algorithm.txt");
					
					FAIL_EXIT_IF(g_pStrVec == NULL, "String vector gives error", "ReadFileInMemory");  

					g_insertionVector = CreateInsertionSortVector();
					InsertionSortInMemory(g_arr,N);
					
					hdc = GetDC(hwnd);
					PaintDesign(hdc,cxClient,cyClient);
					PrintAlgorithm(hdc, cyChar, cxCaps);
					header(hdc, cxClient,cyClient,g_insertionVector->pInsertionSort[0]);
					ReleaseDC(hwnd,hdc);

					iFlagInsertionSort = TRUE;
					InvalidateRect(hwnd, NULL, true);

					break;
				}
				/*END : ShowInsertion*/

				/*START : BubbleSort*/
				case ID_SHOW_BUBBLE:
				{
					if (g_pStrVec != NULL)
					{
						DestroyStringVector(g_pStrVec);
						g_pStrVec = NULL;
					}

					g_pStrVec = ReadFileInMemory("resources/bubble_sort_algorithm.txt");

					FAIL_EXIT_IF(g_pStrVec == NULL, "String vector gives error", "ReadFileInMemory");

					g_bubbleVector = CreateBubbleSortVector();
					if (g_bubbleVector == NULL)
					{
						exit(-1);
					}
					BubbleSortInMemory(g_arr, N);

					/*EnableScrollBar(hwnd, SB_VERT, ESB_ENABLE_BOTH);
					si.cbSize = sizeof(SCROLLINFO);
					si.fMask = SIF_RANGE | SIF_PAGE;
					si.nMin = 0;
					si.nMax = g_bubbleVector->iVectorSize - 1;
					SetScrollInfo(hwnd, SB_VERT, &si, TRUE);*/

					iFlagBubbleSort = true;
					InvalidateRect(hwnd, NULL, true);
					break;
				}
				/*END : BubbleSort*/

				case IDB_NEXT_STEP_BUTTON:
				{
					if (SELECT == g_sortTypeSelection[INSERTION_SORT])
					{
						if (g_insertionVector->iVectorSize <= iInsertionCounter)
						{
							ShowWindow(hBtnNext, false);
							break;
						}
						iFlagInsertionSort = true;

					}
					
					else if (SELECT == g_sortTypeSelection[BUBBLE_SORT])
					{
						iFlagBubbleSort = true;
						SetTimer(hwnd, ID_TIMER_BUBBLE, 3000, (TIMERPROC)NULL);
						EnableWindow(hBtnNext, false);
					}
					
					InvalidateRect(hwnd, NULL, true);
					break;
				}

				case ID_EXIT:
				{
					STARTUPINFO obj;
					PROCESS_INFORMATION pi;
					
					memset(&obj, 0, sizeof(obj)); 
					memset(&pi, 0, sizeof(pi));
					obj.cb = sizeof(obj);

					TCHAR *filePath = TEXT("CreditScreenUI.exe");
					BOOL bRet = FALSE;
					bRet = CreateProcess(
								filePath,
								NULL,
								NULL,
								NULL,
								FALSE,
								0,
								NULL,
								NULL,
								&obj,
								&pi
								);
					if (bRet == FALSE)
					{
						int err = GetLastError();

						MessageBox(hwnd, TEXT("CreateProcessA"), TEXT("LOG"), MB_ICONERROR);
						break;
					}
					SendMessage(hwnd, WM_DESTROY, 0, 0);
					break;
				}
				
				case ID_GET_DATA:
				{
					SendMessage(hwnd, WM_COMMAND, MAKEWPARAM(IDB_OPEN_DLG, 0), 0);
					break;
				}
			}
			break;
		}
	
		case WM_DESTROY:
        {
			if (g_pStrVec)
			{
				DestroyStringVector(g_pStrVec);
				g_pStrVec = NULL;
			}

			if (g_insertionVector)
			{
				DestroyInsertionSortVector(g_insertionVector);
				g_insertionVector = NULL;
			}

			if (g_bubbleVector)
			{
				DestroyBubbleSortVector(g_bubbleVector);
				g_bubbleVector = NULL;
			}

            PostQuitMessage(0);
            break;
        }
    }
    return (DefWindowProc(hwnd,uMsg,wParam,lParam));
}
