#include"DebuggingOfSorting.h"

int g_sortTypeSelection[2];
int N;

LRESULT CALLBACK DlgProc(HWND hDlg,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
    static HWND hBtnClose;
    static HWND hBtnEleVal;
    static HWND hBtnNextVal;
    static HWND hBtnAddElement;
    
    static HINSTANCE hInst;
	static HWND hEBValueOfN;
    static POINT labelPoint;
    static HWND hRBtnsortingArr[2];
    
    static TCHAR szBuffer[8] = TEXT("0");
   // static int N = 0;
    static int index = 0;
    static int flagRB[2];
    static int flagGetData = UNSET;
    static int flagSortType = UNSET;    

    int i = 0;
    int len = 0;
    int xPos = 100;
    int yPos = 50;
    int iRBIds[] = {ID_RBTN1_DLG,ID_RBTN2_DLG};
    TCHAR *SortAlgName[] = {TEXT("Insertion Sort"),TEXT("Quick Sort")};

	HDC hdc;
    HPEN hPen;
    HBRUSH hBrush;
    PAINTSTRUCT ps;
    COLORREF prevColor;

	switch(uMsg)
	{
		case WM_CREATE:
        {
			g_sortTypeSelection[0] = UNSELECT;
			g_sortTypeSelection[1] = UNSELECT;

			hInst = (HINSTANCE)((LPCREATESTRUCT)lParam)->hInstance;
		
            hBtnClose = CreateWindowEx(
									0,     
									TEXT("BUTTON"), 
									TEXT("Close"), 
									WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 
									(DIALOG_WIDTH/2) ,
                                    DIALOG_HEIGHT - 200 , 
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


            for(i = 0; i < 2 ; i++,yPos += 50)
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

            //yPos += 40;
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

            //xPos = 100;
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

            //xPos = 300;
            hBtnEleVal = CreateWindowEx(
							0,
							TEXT("EDIT"),
							NULL,
							WS_BORDER | WS_CHILD | WS_VISIBLE | ES_NUMBER,
							xPos,
							yPos + 40,//yPos + 20, 
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

        //    if(SET == flagRB)
        //     {
        //         for(i = 0 ; i < 2 ; i++)
        //         {
        //             if(SELECT == flagRB[i])
        //             {

        //             }
        //         }
        //     }
            
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
                        FormatedTextOut(hdc,labelPoint.x + (i * 50),(labelPoint.y + 140) ,TEXT("%d"),i);
                        FormatedTextOut(hdc,labelPoint.x + (i * 50),(labelPoint.y + 160) ,TEXT("%d"),g_arr[i]);
                    }
                    
                    if(index == N)
                    {
                        EnableWindow(hBtnEleVal,FALSE);
                        EnableWindow(hBtnNextVal,FALSE);
                        EnableWindow(hBtnAddElement,FALSE);
                    }
                }
            }
            EndPaint(hDlg,&ps);
        }
		case WM_COMMAND:
		{
			switch(LOWORD(wParam))
            {
            case ID_CLOSE_DLG:
				ShowWindow(g_MainHwnd,TRUE);
                DestroyWindow(hDlg);
                break;
            case ID_RBTN1_DLG:
                flagSortType = SET;
				g_sortTypeSelection[0] = SELECT;
				g_sortTypeSelection[1] = UNSELECT;
                break;
            case ID_RBTN2_DLG:
                flagSortType = SET;
				g_sortTypeSelection[0] = UNSELECT;
				g_sortTypeSelection[1] = SELECT;

                break;
            case IDB_ADDELE_BUTTON:
                    GetWindowText(hEBValueOfN, szBuffer, 8);
                    N = atoi(szBuffer);
                    if(N > 5)
                        N = 5;
                    else if(N < 3)
                        N = 3;
                    
                    flagGetData = SET;
                    InvalidateRect(hDlg,NULL,FALSE);
                break;

            case IDB_NEXTVAL_BUTTON:
                
                GetWindowText(hBtnEleVal, szBuffer, 8);
                g_arr[index] = atoi(szBuffer);
                index ++;
                memset(szBuffer,0,8);
                SetWindowText(hBtnEleVal, szBuffer);
                InvalidateRect(hDlg,NULL,FALSE);

                break;
			}

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
