#include"DebuggingOfSorting.h"


int g_sortTypeSelection[SORT_TYPE_COUNT];
int N;
HWND hBtnClose;
HWND hBtnEleVal;
HWND hBtnNextVal;

LRESULT CALLBACK DlgProc(HWND hDlg,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
    static HWND hBtnAddElement;
    
    static HINSTANCE hInst;
	static HWND hEBValueOfN;
    static POINT labelPoint;
    static HWND hRBtnsortingArr[SORT_TYPE_COUNT];
    
    static TCHAR szBuffer[8] = TEXT("0");
    static int index = 0;
    static int flagRB[SORT_TYPE_COUNT];
    static int flagGetData = UNSET;
    static int flagSortType = UNSET;    

    int i = 0;
    int len = 0;
    int xPos = 100;
    int yPos = 80;
	int iRBIds[SORT_TYPE_COUNT] = { ID_RBTN1_DLG,ID_RBTN3_DLG };
    TCHAR *SortAlgName[SORT_TYPE_COUNT] = {
					TEXT("Insertion Sort"),
					TEXT("Bubble Sort"),
					};

	HDC hdc;
    HPEN hPen;
    HBRUSH hBrush;
    PAINTSTRUCT ps;
    COLORREF prevColor;
	static RECT rc;

	switch(uMsg)
	{
		case WM_CREATE:
        {
			N = 0;
			index = 0;
			flagSortType = UNSET;
			memset(g_arr, 0, sizeof(g_arr) / sizeof(g_arr[0]));
			memset(szBuffer, 0, sizeof(szBuffer) / sizeof(szBuffer[0]));
			memset(g_sortTypeSelection, 0, sizeof(int) * SORT_TYPE_COUNT);
			
			if (hBtnEleVal && hBtnNextVal && hBtnAddElement)
			{
				EnableWindow(hBtnEleVal, TRUE);
				EnableWindow(hBtnNextVal, TRUE);
				EnableWindow(hBtnAddElement, TRUE);
			}
			

			hInst = (HINSTANCE)((LPCREATESTRUCT)lParam)->hInstance;
		
            hBtnClose = CreateWindowEx(
									0,     
									TEXT("BUTTON"), 
									TEXT("Close"), 
									WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 
									(DIALOG_WIDTH/2) ,
                                    DIALOG_HEIGHT - 160 , 
									80, 
									20, 
									hDlg, 
									(HMENU)ID_CLOSE_DLG, 
									(HINSTANCE)hInst, 
									NULL
									);

             if (!hBtnClose)
			 {
                MessageBox(NULL, TEXT("Dialog Button Failed."), TEXT("Error"), MB_OK | MB_ICONERROR);
				break;
			 }


            for(i = 0; i < SORT_TYPE_COUNT; i++,yPos += 50)
            {
                hRBtnsortingArr[i] =CreateWindowEx(
									    0,     
                                        TEXT("BUTTON"), 
                                        SortAlgName[i], 
                                         WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON, 
                                        xPos, 
                                        yPos, 
                                        150, 
                                        30, 
                                        hDlg, 
                                        (HMENU)iRBIds[i], 
                                        (HINSTANCE)hInst, 
                                        NULL
									);
                if (!hRBtnsortingArr[i])
                {
                    MessageBox(NULL, TEXT("Radio Button Failed."), TEXT("Error"), MB_OK | MB_ICONERROR);
                    break;
                }
            }

            labelPoint.y = yPos;
            labelPoint.x = xPos; 
            xPos += 180;
            hEBValueOfN = CreateWindowEx(
							0,
							TEXT("EDIT"),
							NULL,
							WS_BORDER | WS_CHILD | WS_VISIBLE | ES_NUMBER,
							xPos,
							yPos,
							30,
							20,
							hDlg,
							(HMENU)ID_EB_VALUE_OF_N,
							(HINSTANCE)hInst,
							NULL
							);
            if (!hEBValueOfN)
            {
                MessageBox(NULL, TEXT("EDIT BOX Failed."), TEXT("Error"), MB_OK | MB_ICONERROR);
                break;
            }

            yPos += 40;
            hBtnAddElement = CreateWindowEx(
                        0,     
                        TEXT("BUTTON"), 
                        TEXT("Add Element"), 
                        WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 
                        xPos,
                        yPos, 
                        100, 
                        20, 
                        hDlg, 
                        (HMENU)IDB_ADDELE_BUTTON, 
                        (HINSTANCE)hInst, 
                        NULL
                        );
			if(!hBtnAddElement)
            {
                MessageBox(NULL, TEXT("Dialog Button Failed."), TEXT("Error"), MB_OK | MB_ICONERROR);
				break;
            }
            xPos = 300;
            hBtnNextVal = CreateWindowEx(
                        0,     
                        TEXT("BUTTON"), 
                        TEXT("Next Value"), 
                        WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 
                        xPos,
                        yPos + 80, 
                        100, 
                        20, 
                        hDlg, 
                        (HMENU)IDB_NEXTVAL_BUTTON, 
                        (HINSTANCE)hInst, 
                        NULL
                        );
			if(!hBtnAddElement)
            {
                MessageBox(NULL, TEXT("Dialog Button Failed."), TEXT("Error"), MB_OK | MB_ICONERROR);
				break;
            }
            ShowWindow(hBtnNextVal,SW_HIDE);

            hBtnEleVal = CreateWindowEx(
							0,
							TEXT("EDIT"),
							NULL,
							WS_BORDER | WS_CHILD | WS_VISIBLE | ES_NUMBER,
							xPos,
							yPos + 40,
							60,
							20,
							hDlg,
							(HMENU)ID_EB_ELE_VALUE,
							(HINSTANCE)hInst,
							NULL
							);
            if (!hBtnEleVal)
            {
                MessageBox(NULL, TEXT("EDIT BOX Failed."), TEXT("Error"), MB_OK | MB_ICONERROR);
                break;
            }
            ShowWindow(hBtnEleVal,SW_HIDE);

			break;
        }
        case WM_PAINT:
        {
            /*TODO START*/
                /*
                    Draw border to dailog box with attractive colors and lines.
                    use DIALOG_WIDTH and DIALOG_HEIGHT macro for positions while draw lines.
                */
            /*TODO END*/

            hdc = BeginPaint(hDlg,&ps);
            SetBkMode(hdc,TRANSPARENT);

            {
                hPen = CreatePen(PS_SOLID,1,RGB(255,105,180));
                SelectObject(hdc,hPen);

                hBrush = CreateSolidBrush(RGB(255,255,191));
                SelectObject(hdc,hBrush);

                Rectangle(hdc,1,1,DIALOG_HEIGHT,DIALOG_WIDTH);
                
                hBrush = CreateSolidBrush(RGB(152,251,152));
                SelectObject(hdc,hBrush);

                Rectangle(hdc,50,30,DIALOG_HEIGHT-50,DIALOG_WIDTH-30);
                
                len = _tcslen(TEXT("Enter element count (N) : "));
                TextOut(hdc,labelPoint.x,labelPoint.y,TEXT("Enter element count (N) : "),len);
                
                xPos = labelPoint.x + 50 + (len * 7);
                
                FormatedTextOut(hdc,xPos,labelPoint.y,TEXT("Note : Min:[%d], Max:[%d]"),MIN,MAX);
                FormatedTextOut(hdc,xPos,labelPoint.y+20,"N = %d",N);
            }
            if(SET == flagGetData)
            {
                if(UNSET == flagSortType)
                {
                    prevColor = SetTextColor(hdc,RGB(255,0,0));

                    TextOut(hdc,DIALOG_WIDTH - 200,50,TEXT("SELECT SORT TYPE"),_tcslen(TEXT("SELECT SORT TYPE")));
                    SetTextColor(hdc,prevColor);
                }
                else if(index <= N)
                {
                    ShowWindow(hBtnNextVal,SW_SHOW);
                    ShowWindow(hBtnEleVal,SW_SHOW);
                    FormatedTextOut(hdc,labelPoint.x,labelPoint.y + 80,TEXT("Enter Value Element [ %d ]: "),index);

                    for(i = 0 ; i < index; i++)
                    {
                        FormatedTextOut(hdc,labelPoint.x + (i * 50),(labelPoint.y + 150) ,TEXT("%d"),i);
                        FormatedTextOut(hdc,labelPoint.x + (i * 50),(labelPoint.y + 170) ,TEXT("%d"),g_arr[i]);
                    }
                    
                }
            }
            EndPaint(hDlg,&ps);
        }
		case WM_COMMAND:
		{
			if (LOWORD(wParam) == ID_RBTN1_DLG || LOWORD(wParam) == ID_RBTN3_DLG)
			{
				flagSortType = SET;
				memset(g_sortTypeSelection, 0, sizeof(int)* SORT_TYPE_COUNT);
			}
			
			switch(LOWORD(wParam))
            {
				case ID_CLOSE_DLG:
				{
					if (SELECT != g_sortTypeSelection[INSERTION_SORT] &&
						SELECT != g_sortTypeSelection[BUBBLE_SORT] 					)
					{
						MessageBox(hDlg, TEXT("Please select sorting type."), TEXT("WARNING"), MB_ICONEXCLAMATION);
						break;
					}
					else if (N == 0)
					{
						MessageBox(hDlg, TEXT("Please enter valid number for 'N'."), TEXT("WARNING"), MB_ICONEXCLAMATION);
						break;

					}
					else if (index < N)
					{
						MessageBox(hDlg, TEXT("Insufficient number of elements.\nEnter value for all index."), TEXT("WARNING"), MB_ICONEXCLAMATION);
						break;
					}

					GetWindowRect(g_MainHwnd, &rc);
					SetWindowPos(g_MainHwnd, NULL, rc.left, rc.top, rc.right, rc.bottom, SWP_SHOWWINDOW);
					DestroyWindow(hDlg);
					ShowWindow(g_MainHwnd, TRUE);
				
					SendMessage(g_MainHwnd, WM_COMMAND, MAKEWPARAM(IDB_SHOW_SORTING, 0), 0);
					break;
				}
				case ID_RBTN1_DLG:
					g_sortTypeSelection[INSERTION_SORT] = SELECT;
					break;
   
				case ID_RBTN3_DLG:
					g_sortTypeSelection[BUBBLE_SORT] = SELECT;
					break;

				case IDB_ADDELE_BUTTON:
						GetWindowText(hEBValueOfN, szBuffer, sizeof(szBuffer));
						N = atoi(szBuffer);
						if(N > 5)
							N = 5;
						else if(N < 3)
							N = 3;
                    
						flagGetData = SET;
						InvalidateRect(hDlg,NULL,FALSE);
					break;

				case IDB_NEXTVAL_BUTTON:
				{
					if (index == N)
					{
						MessageBox(hDlg, TEXT("You entered sufficient elements.\nPlease press close button."), TEXT("Error"), MB_ICONERROR);
						break;
					}
					GetWindowText(hBtnEleVal, szBuffer, 8);
					g_arr[index] = atoi(szBuffer);
					index++;
					memset(szBuffer, 0, 8);
					SetWindowText(hBtnEleVal, szBuffer);
					InvalidateRect(hDlg, NULL, FALSE);

					break;
				}
			}

			hdc = GetDC(hDlg);

			ReleaseDC(hDlg, hdc);

            if(SET == flagSortType)
            {
                for(i = 0 ; i < 2 ; i++)
                {
                    if(LOWORD(wParam) == iRBIds[i])
                    {
                        flagRB[i] = SELECT;
                    }
                    else
                    {
                        flagRB[i] = UNSELECT;
                    }
                }
            }

			break;
		}
	}
    return(DefWindowProc(hDlg,uMsg,wParam,lParam));
}
