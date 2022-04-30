#include"CreditScreenHeader.h"

void PlayMusic( void * lpParam );
int g_screen_width;
int g_screen_height;


LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;

	static int cxclient;
	static int cyclient;
    static int xPos;
    static int yPos;

    PAINTSTRUCT ps;
    static HFONT hFont;
    static HFONT hFont1;
    RECT rect;
    int i;
    static int j=0;

    int time_start = 0;
    static BOOL timer_flags[8] = {FALSE};

    TCHAR *arrName[] = {
                        "Darshan Jogi",             // 1
                        "Shweta Patil",             // 2
                        "Smita Peddawad",           // 3
                        "Manoj Nanaware",           // 4
                        "Priyanka Tandulwadkar",    // 5
                        "Kunal Kohinkar",           // 6
                        "Sayali Rishi Kulkarni"     // 7
                        };

    TCHAR *arrD[] = {
                    "Draw diagram for quick sort which shows represention of higlighted line",
                    "Scroll selected client area",
                    "Get data from user and pass that data to sorting functions",
                    "Draw diagram for Insertion sort which shows represention of higlighted line",
                    "Create credit screen",
                    "Show algorithms and initial data",
                    "Draw diagram for quick sort which shows represention of higlighted line"
                    };

    switch(uMsg)
    {
        case WM_SIZE:
		    cxclient = LOWORD(lParam);
		    cyclient = HIWORD(lParam);
            yPos = cyclient - 50;
            hFont = CreateFont(
                                26,
                                0,
                                0,
                                0,
                                FW_DONTCARE,
                                TRUE,
                                FALSE,
                                FALSE,
                                DEFAULT_CHARSET,
                                OUT_OUTLINE_PRECIS,
                                CLIP_DEFAULT_PRECIS,
                                CLEARTYPE_QUALITY,
                                VARIABLE_PITCH,
                                NULL//TEXT("Comic Sans")
                            );

            hFont1 = CreateFont(
                                24,
                                0,
                                0,
                                0,
                                FW_DONTCARE,
                                FALSE,
                                FALSE,
                                FALSE,
                                DEFAULT_CHARSET,
                                OUT_OUTLINE_PRECIS,
                                CLIP_DEFAULT_PRECIS,
                                CLEARTYPE_QUALITY,
                                VARIABLE_PITCH,
                                NULL
                                );
            //for(i = 1, time_start = TIME_START; i <= sizeof(arrName)/sizeof(arrName[0]);i++)
            //_beginthread(PlayMusic,0,NULL);
            for(i = 1, time_start = TIME_START; i <= 21; i++)
            {
                SetTimer(hWnd, i, time_start, NULL);
                time_start += GAP_TIME;
            }
		    break;

	    case WM_CREATE:

            _beginthread(PlayMusic,0,NULL);
            
		    break;
            
        case WM_PAINT:
        {
			{
				hdc = BeginPaint(hWnd, &ps);

				//SelectObject(hdc,hFont);
				SetTextAlign(hdc, TA_CENTER);
				SetBkColor(hdc, RGB(0, 0, 0));
				SetTextColor(hdc, RGB(0, 255, 255));
				//SetTextColor(hdc,RGB(0,255,0));

				for (i = 1; i <= 16; i++)
				{
					if (timer_flags[i - 1] == TRUE)
					{
						//TextOut(hdc, 50, yPos, arrName[i-1], _tcslen(arrName[i-1]));
						//yPos += 40;

						//SetTextAlign(hdc,TA_CENTER);
						SelectObject(hdc, hFont);
						//SetTextColor(hdc,RGB(255,0,255));
						TextOut(hdc, cxclient / 2, yPos, arrName[i - 1], _tcslen(arrName[i - 1]));
						yPos += 25;
						SelectObject(hdc, hFont1);
						//SetTextColor(hdc,RGB(0,255,255));
						TextOut(hdc, cxclient / 2, yPos, arrD[i - 1], _tcslen(arrD[i - 1]));
						yPos += 60;
					}
				}

				if (j >= 12)
				{
					SelectObject(hdc, hFont1);
					TextOut(hdc, cxclient / 2, yPos + 400, TEXT("Specially Thanks To"), _tcslen(TEXT("Specially Thanks To")));
					SelectObject(hdc, hFont);
					TextOut(hdc, cxclient / 2, yPos + 425, TEXT("Yogeshwar Shukla Sir"), _tcslen(TEXT("Yogeshwar Shukla sir")));
				}
				j++;

				EndPaint(hWnd, &ps);
			}
            break;
        }

	    case WM_TIMER:
        {
            if(LOWORD(wParam) < 8 && LOWORD(wParam) > 0)
            {
                timer_flags[LOWORD(wParam) - 1] = TRUE;
                yPos = cyclient-20 * LOWORD(wParam);
                InvalidateRect(hWnd,NULL,TRUE);
                KillTimer(hWnd,LOWORD(wParam));
            }
            else if(LOWORD(wParam) <= 21 && LOWORD(wParam) > 7)
            {
                //timer_flags[LOWORD(wParam) % 8] = FALSE;
                yPos = cyclient-20 * LOWORD(wParam);
                InvalidateRect(hWnd,NULL,TRUE);
                KillTimer(hWnd,LOWORD(wParam));
            }
		    break;
        }
        case WM_DESTROY:
            PostQuitMessage(EXIT_SUCCESS);
            break;
    }

    return (DefWindowProc(hWnd, uMsg, wParam, lParam));
}

void PlayMusicForCreditScreen( void * lpParam )
{
	if(TRUE != PlaySound(TEXT("Intro.wav"),NULL,SND_ASYNC|SND_NODEFAULT))
	{
		MessageBox(NULL,TEXT("PlaySound FAIELD"),TEXT("ERROR"),MB_ICONERROR);
		_endthread();
	}
	_endthread();
}