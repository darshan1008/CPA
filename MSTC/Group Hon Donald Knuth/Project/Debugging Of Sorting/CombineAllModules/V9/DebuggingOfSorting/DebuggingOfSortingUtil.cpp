#include"DebuggingOfSorting.h"
#include<Windows.h>

#include<process.h>

int FormatedTextOut(HDC hdc, int x, int y, TCHAR* pszFormat, ...)
{
	TCHAR szBuffer[1024] = { "" };
	va_list pArgs;
	va_start(pArgs, pszFormat);

	_vsntprintf(szBuffer, ARRAY_SIZE(szBuffer), pszFormat, pArgs);
	TextOut(hdc, x, y, szBuffer, strlen(szBuffer));
	return(0);
}

void PrintPicture(HWND hWnd,HWND *lp_hImage,LPCSTR lv_imagePath,RECT lv_rect)
{
	HBITMAP hBitmap = NULL;
	hBitmap = (HBITMAP)LoadImage(GetModuleHandle(NULL),lv_imagePath,
										 IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

    *lp_hImage = CreateWindow("Static", 
						" ", 
						WS_TABSTOP | WS_VISIBLE | WS_CHILD |SS_BITMAP, 
						lv_rect.left,
						lv_rect.top ,
						lv_rect.right - lv_rect.left, 
						lv_rect.bottom - lv_rect.top, 
						hWnd, 
						NULL, 
						GetModuleHandle(NULL),
						NULL
						);  

    SendMessage(*lp_hImage,STM_SETIMAGE,(WPARAM) IMAGE_BITMAP,(LPARAM)hBitmap);
	return;
}

void DrawLineUtil(HDC hdc,int xsrc,int ysrc,int xdes,int ydes)
{
	MoveToEx(hdc,xsrc,ysrc,NULL);
    LineTo(hdc,xdes,ydes);
}

int AddButton(HWND hWnd,HWND *hBtn,int lv_ID)
{
	(*hBtn) = CreateWindowEx(
							0,     
							TEXT("BUTTON"), 
							TEXT("CONTINUE"), 
							WS_VISIBLE | WS_CHILD , 
							0, 
							0, 
							0, 
							0, 
							hWnd, 
							(HMENU)lv_ID, 
							(HINSTANCE)NULL, 
							NULL
							);

            if (!(*hBtn)) {
                MessageBox(NULL, TEXT("Button Failed."), TEXT("Error"), MB_OK | MB_ICONERROR);
				return -1;
			}
	return SUCCESS;
}

void MusicSplashScreen( void * lpParam )
{
	if(TRUE != PlaySound(TEXT("resources/01_Contra.wav"),NULL,SND_ASYNC|SND_NODEFAULT))
	{
		MessageBox(NULL,TEXT("PlaySound FAIELD"),TEXT("ERROR"),MB_ICONERROR);
		_endthread();
	}
	_endthread();
}

void PrintHeader(HDC hdc)
{
	HFONT hMyFont;

	SetBkColor(hdc,RGB(209,237,242));
	SetTextColor(hdc,RGB(255,0,0));
	hMyFont = CreateFont(25,0,0,0,700,0,1,0,0,0,0,0,FF_DONTCARE,"Arial Bold");
	SelectObject(hdc,hMyFont);

	TextOut(hdc,650,120,TEXT("HON. DONALD KHUTH"),strlen(TEXT("HON. DONALD KHUTH")));

}
