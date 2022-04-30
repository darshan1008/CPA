
// #############  Drwaing ##########//
/*
	Color Toggling on Key C
*/


#include <windows.h>
#include <stdio.h>
#include <string.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include "MyResource.h"

// libpath 
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "kernel32.lib")
#pragma comment(lib, "Winmm.lib")

#define TJ_POINT_RADIUS 2

//Coloring scheme values
#define MONO_COLOR      0
#define MULTI_COLOR     1

#ifndef size_t
#define size_t long int
#endif

typedef int BRUSH_SIZE;


int RENDER_SMOOTHING_FLAG=0;	
	
	
int G_POINTS_PLOTED=0;
int MUSIC_PLAY_STATUS=TRUE;
int COLOR_SCHEME=MONO_COLOR;


COLORREF red=RGB(255,0,0); 
COLORREF green=RGB(0,255,0); 
COLORREF blue=RGB(0,0,255); 
COLORREF orange=RGB(255,165,0); 
COLORREF cyan=RGB(0,255,255); 
COLORREF magenta=RGB(255,0,255); 
COLORREF yellow=RGB(255,215,0); 
COLORREF skyblue=RGB(0,191,255); 


#define VISULIZER_RED_PEN     1
#define VISULIZER_GREEN_PEN   2
#define VISULIZER_BLUE_PEN    3
#define VISULIZER_ORAGNE_PEN  4
#define VISULIZER_CYAN_PEN    5
#define VISULIZER_MGENTA_PEN  6
#define VISULIZER_YELLOW_PEN  7
#define VISULIZER_SKYBLUE_PEN 8


int CLIENT_XArea,CLIENT_YArea;
int CLIENT_XMouse,CLIENT_YMouse;


//int SCREEN_X_SHIFT=(1920/2)-(312); 
//int SCREEN_Y_SHIFT=(1080/2)-(564);


int SCREEN_X_SHIFT; 
int SCREEN_Y_SHIFT;

//int SPAWN_RATE=7;
int particle_count=0;

typedef struct tagmyPoint
{
    int xPosition;
    int yPosition;
    int xVelocity;
    int yVelocity;
    //int xAcceleration;
    //int yAcceleration;
    int dead;  //by default when myPoint spawns it is not dead  
    COLORREF * color; 
}TJ_POINT,*PTJ_POINT,**PPTJ_POINT;

typedef struct tagVector
{
    PPTJ_POINT list;
    //tagmyPoint ** list;
	int count;
}VECTOR,*PVECTOR;

PVECTOR CreateVector(void);
int PushElement(PVECTOR pVector,PTJ_POINT pPoint);
void DestroyVector(PVECTOR pVector);
void PopElement(PVECTOR pVector,int index);
int mygetline(char **line ,size_t * char_cnt, FILE * fp);
PTJ_POINT CreatePoint(int xPos,int yPos, int xVel, int yVel);
double getDistance(int x1,int y1, int x2,int y2 );

//int IsDead(PTJ_POINT pPoint);

///MY Circle
bool MyCircle(int iXCenter,int iYCenter,int radius,HDC hdc);

PVECTOR PointVector;

void setMsg(void);
FILE *fp;

//2. Hollywood Principal
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//3
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow) //ncmwindow show the window on how it should be shown e.g. maximized minimized or hidden etc.
{

    //My Addon

    PointVector=CreateVector();  //Create Point Vector
	 
	fp = fopen("point.txt","rb+");
	
	int iColor;
	char * token=NULL;
	char * line=NULL;
	size_t line_size;
	 PTJ_POINT pPoint;
	int xCordinate=0;
	int yCordinate=0;
	COLORREF color;
	int    isCuurentTokenX=0;
/*	
	NAME, SURNAME
	LINUS,TORVALDS
*/

	while(mygetline(&line,&line_size,fp)!=-1)
		{
		
			token = strtok(line,",");
			while(token != NULL) 
			{   
				if(isCuurentTokenX == 0)
				{
					//reading X co-ordinate
					xCordinate=atoi(token);
					isCuurentTokenX=1;
				}else if(isCuurentTokenX == 1)
				{
					//reading Y co-ordinate
					yCordinate=atoi(token);
					//isCuurentTokenX++;
					isCuurentTokenX=0;
				}
				//fprintf(stdout,"%s",ret);  //this will not return entire match but all character in between match till new line char
				token=strtok(NULL,",");
				//fprintf(stdout,"%s",line);

			}
					
			//printf(" X : %d , Y : %d\n",xCordinate,yCordinate);
			
			//pPoint=CreatePoint(xCordinate+SCREEN_X_SHIFT,yCordinate+SCREEN_Y_SHIFT,0,0);   //Pushing offsetedvalues;
			pPoint=CreatePoint(xCordinate,yCordinate,0,0);    //Offset only values 
			
			
			PushElement(PointVector,pPoint);
			
			particle_count+=1;  //Global variable to keep track of points on screen
			
     	free(line);
     	line=NULL;
      } 
	  

	//4. Data
	WNDCLASSEX wndclass; //  style
	HWND hwnd;	// Handle == Pointer to Window
	//MSG msg;
	MSG msg={};	//Current msg
	
	TCHAR szAppName[] = TEXT("MSTC"); // name of class 
    TCHAR szWindowCaption[] = TEXT("Guru Darshan : MSTC !!!");

	//5. Code : Fill the struct 
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra = 0; // additional
	wndclass.cbWndExtra = 0; // additional

	wndclass.lpfnWndProc = WndProc; // it actully funcptr
	wndclass.hInstance = hInstance; // 1st param

	 wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(MYICONSM));
	 wndclass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(MYICONSM));
	 
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);

	wndclass.lpszClassName = szAppName; // Group Name ""
	wndclass.lpszMenuName = NULL; // used in project

	// 6
	RegisterClassEx(&wndclass);

	// 7  Create window and return its
	hwnd = CreateWindow(szAppName, // class style
						szWindowCaption,    //Windows Caption name
						WS_OVERLAPPEDWINDOW,	   // Style of wnd
						CW_USEDEFAULT,				// x cord
						CW_USEDEFAULT,				// y cord
						1920,				// width
						1080,				// height
						(HWND)NULL,                 // hWndParent
						(HMENU)NULL,				// hMenu
						hInstance,					// 1st 
						NULL);						// No lpParam (used for additional data)

	
	// 8  memset
	AnimateWindow(hwnd , 3000 , AW_CENTER); //AW_VER_POSITIVE
//	ShowWindow(hwnd, SW_MAXIMIZE);
	UpdateWindow(hwnd); // VIMP

	// 9. Message Loop
	
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
		

	// 10
    DestroyVector(PointVector); //Destroy Point Vector
	PointVector = NULL;

	return((int)msg.wParam);
}


// 11 a 
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	// 11 b
    static int cxClient, cyClient, cxChar, cyChar, cxMouse,cyMouse;
    HDC hdc = NULL; 
	
	HPEN HLinePen;
	HPEN HOldPen;
    COLORREF color;
	
	TEXTMETRIC tm; 
    PAINTSTRUCT ps; 
	int xAccel;
    int yAccel;
	int pointIndex;
	//RECT Cliet_Rect;
	double point_distance;
	
	//for image
	HDC hdcComp;
	static HINSTANCE hInst;
	static HBITMAP hbmap;
	HGDIOBJ prevHGDIObj = NULL;
	BITMAP bmBuffer;
	RECT rc;

    switch (iMsg)
	{
		// very 1st Msg
	case WM_CREATE:
			hInst = (HINSTANCE)((LPCREATESTRUCT)lParam)->hInstance;

		//	MessageBox(NULL, TEXT("Lord Vitthal By MSTC"), TEXT("Window Created"),  MB_OK);
	       	SetTimer(hwnd, 1,370, NULL);
            hdc = GetDC(hwnd); 
            GetTextMetrics(hdc, &tm);
            cxChar = tm.tmAveCharWidth; 
            cyChar = tm.tmHeight + tm.tmExternalLeading; 
            //GetClientRect(hwnd, &Cliet_Rect);
			//SCREEN_X_SHIFT=(Cliet_Rect.right/2)-(312);
			//SCREEN_Y_SHIFT=(Cliet_Rect.bottom/2)-(564);

			ReleaseDC(hwnd, hdc); 
            hdc = NULL; 
    	break;

        case WM_SIZE: 
            cxClient = LOWORD(lParam); 
            cyClient = HIWORD(lParam); 
            CLIENT_XArea = cxClient;
            CLIENT_YArea = cyClient;
			
			//Maintaing Image offset to Keep drawing atthe center
		
			SCREEN_X_SHIFT=(cxClient/2)-(312/2);  //Images's rect's (max x ) right position was 312
			SCREEN_Y_SHIFT=(cyClient/2)-(564/2);  //Images's rect's (max Y)  bottom position was 564
			
            break; 


        case WM_MOUSEMOVE:
            cxMouse = LOWORD(lParam);
            cyMouse = HIWORD(lParam);
			CLIENT_XMouse=cxMouse;
			CLIENT_YMouse=cyMouse;
            break;

		case WM_KEYDOWN:
	
			if(wParam == 'M' || wParam == 'm')
			{
				//Togle code
				if(MUSIC_PLAY_STATUS==TRUE)
				{
					MUSIC_PLAY_STATUS=FALSE;
					PlaySound(NULL, NULL, SND_FILENAME | SND_ASYNC );
				}
				else
				{
					MUSIC_PLAY_STATUS=TRUE;
					PlaySound(TEXT("music.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP );
				}
			}
			
			if(wParam == 'C' || wParam == 'c')
			{
				//Togle the coloring scheme
				if( COLOR_SCHEME == MONO_COLOR )
				{
					COLOR_SCHEME = MULTI_COLOR;
				}else if(COLOR_SCHEME == MULTI_COLOR )
				{
					COLOR_SCHEME = MONO_COLOR;
				}
				
			}
			
			case VK_SPACE:
				//splash
				hbmap = LoadBitmap(hInst, MAKEINTRESOURCE(MY_BITMAP));

				//hdc = BeginPaint(hwnd, &ps);
				hdcComp = CreateCompatibleDC(hdc);
				prevHGDIObj = SelectObject(hdcComp, hbmap);
				GetObject(hbmap, sizeof(BITMAP), &bmBuffer); // retrieves dimension of a bitmap
				GetClientRect(hwnd, &rc);
				
				BitBlt(hdc, (rc.right - bmBuffer.bmWidth)/3, (rc.bottom - bmBuffer.bmHeight)/3, (int)bmBuffer.bmWidth , (int)bmBuffer.bmHeight, hdcComp, 0, 0, SRCCOPY); // performs bit block transfer from memory DC to hdc returned from BeginPaint
				//StretchBlt(hdc, 0, 0, rc.right, rc.bottom, hdcComp, 0, 0, bmBuffer.bmWidth, bmBuffer.bmHeight, SRCCOPY);
				
				SelectObject(hdcComp, prevHGDIObj);
				DeleteDC(hdcComp);
				EndPaint(hwnd, &ps);
				break;
			
			break;
			
        case WM_PAINT: 
            hdc = BeginPaint(hwnd, &ps); 
            
			if(RENDER_SMOOTHING_FLAG=1)
			{
					
				if( COLOR_SCHEME == MONO_COLOR )
				{
					HLinePen=CreatePen(PS_SOLID, 4 , orange);
				}
				
				HOldPen=(HPEN)SelectObject(hdc,HLinePen);
				for(pointIndex=0; pointIndex < G_POINTS_PLOTED ; pointIndex++)
				{
					
					if(pointIndex!=0)
					{
						
						point_distance=getDistance(PointVector->list[pointIndex-1]->xPosition,
																	PointVector->list[pointIndex-1]->yPosition,
																	PointVector->list[pointIndex]->xPosition,
																	PointVector->list[pointIndex]->yPosition);
																	
						if(point_distance <= 30)  //To sanitization of the lines between unconnected parts
						{
							
							
							//MoveToEx(hdc,PointVector->list[pointIndex-1]->xPosition,PointVector->list[pointIndex-1]->yPosition,NULL);
							//LineTo(hdc,PointVector->list[pointIndex]->xPosition,PointVector->list[pointIndex]->yPosition);
							
							//Ploting point with offseted value calculation
							MoveToEx(hdc,PointVector->list[pointIndex-1]->xPosition+SCREEN_X_SHIFT,PointVector->list[pointIndex-1]->yPosition+SCREEN_Y_SHIFT,NULL);
							LineTo(hdc,PointVector->list[pointIndex]->xPosition+SCREEN_X_SHIFT,PointVector->list[pointIndex]->yPosition+SCREEN_Y_SHIFT);
							
						}
					}
					

				}
				
				
				DeleteObject(HLinePen);
				SelectObject(hdc,HOldPen);
				
				EndPaint(hwnd, &ps); 
				hdc = NULL;
				RENDER_SMOOTHING_FLAG = 0;
				setMsg();

			}
		break;


     case WM_TIMER:
		{
        //SpawnLoop(PointVector);	
		//AdvanceLoop(PointVector);
		if(G_POINTS_PLOTED == 0 && MUSIC_PLAY_STATUS==TRUE)
		{
			PlaySound(TEXT("music.wav"), NULL, SND_FILENAME | SND_ASYNC );
		}
		
		if(G_POINTS_PLOTED != PointVector->count && RENDER_SMOOTHING_FLAG==0 ) 
		{
			RENDER_SMOOTHING_FLAG=1;
			G_POINTS_PLOTED++;
			
			InvalidateRect(hwnd, NULL, FALSE);
        	}
			else
			{
			MUSIC_PLAY_STATUS=FALSE;
		}
		
		return 0;
		}
		
		break;


	case WM_DESTROY:
		//MessageBox(NULL, TEXT("Happy Birthday , Sir !!!"), TEXT("Credit Window "), MB_OK);
		DeleteObject(hbmap);
		fclose(fp);

		PostQuitMessage(0);
		break;
	}

	// 12
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}


bool MyCircle(int iXCenter,int iYCenter,int radius,HDC hdc)
{
    return(Ellipse(hdc,(iXCenter-radius),(iYCenter-radius),(iXCenter+radius),(iYCenter+radius)));
}


int mygetline(char **line ,size_t * char_cnt, FILE * fp)
{
	long int BUFF_SIZE=64;
	long int BUFF_INCREMENT=64;
	
	long int FILE_READ_POINT=0;
	long int FILE_CHAR_COUNT=0;

	fseek(fp,0,SEEK_CUR);
	FILE_READ_POINT=ftell(fp);
	
	int i;
	int LINE_END=0;
	
	
	fseek(fp,FILE_READ_POINT,SEEK_SET);
	 
	 while(LINE_END!=1)
	 {
	 	fseek(fp,FILE_READ_POINT,SEEK_SET);
	 
	 BUFF_SIZE=BUFF_SIZE+BUFF_INCREMENT;
	 
	 
	 	*line=(char *)realloc(*line, sizeof(char)*BUFF_SIZE);
       
       
    if(fgets(*line,BUFF_SIZE,fp)!=NULL)
    {
       
       for(i=0;i<(BUFF_SIZE-1) -1;i++)
       {
   
       	if((*line)[i]=='\0' )
       	{
       	       LINE_END=1;
       	       *char_cnt=BUFF_SIZE;
       	       break;
       	}
       	//puts(" Inside For Loop ");
       }
      
      //BUFF_MULTIPLIER++;
    }
	else  //this case handles last line in file
    {
    	  LINE_END=1;
    	  *char_cnt=0;
    }
	 }
	 
	 fseek(fp,0,SEEK_CUR);
	FILE_READ_POINT=ftell(fp);
      
      //to hceck if we reached file end
      fseek(fp,0,SEEK_END);
      FILE_CHAR_COUNT=ftell(fp);
      
      //printf(" TOTAL CHAR %ld  CURENT READ %ld\n",FILE_CHAR_COUNT,FILE_READ_POINT);
      
      if(FILE_READ_POINT==FILE_CHAR_COUNT)
      {
           return (-1);
      }
	  else
      {
          fseek(fp,FILE_READ_POINT,SEEK_SET);
          return (0);
      }
}


PVECTOR CreateVector(void)
{
    PVECTOR pVector=NULL;
    pVector=(PVECTOR)malloc(sizeof(VECTOR));
    pVector->list=NULL;
    pVector->count=0;
    return pVector;
}

void DestroyVector(PVECTOR pVector)
{
    int i=0;
    for (i=0;i<pVector->count;i++)
    {
        free(pVector->list[i]);
		pVector->list[i]=NULL;
    }
    free(pVector->list);
    pVector->list=NULL;
    pVector->count=0;
    free(pVector);
    pVector=NULL;
}



int PushElement(PVECTOR pVector,PTJ_POINT pPoint)
{
    pVector->count += 1;
    pVector->list=(PPTJ_POINT)realloc(pVector->list,pVector->count*sizeof(PTJ_POINT));
	
    pVector->list[pVector->count-1]=pPoint;
	
    return (EXIT_SUCCESS);
}


void PopElement(PVECTOR pVector,int index)
{
    if(index < 0 || index >= pVector->count)
		return;
	
	free(pVector->list[index]);
	pVector->list[index] = NULL;
	
	int i;
	for(i=index;i < pVector->count-1 ;i++)
	{
		pVector->list[i] = pVector->list[i+1];
		pVector->list[i+1] = NULL;
	}
	
	pVector->count-=1;
}

PTJ_POINT CreatePoint(int xPos,int yPos, int xVel, int yVel)
{
    PTJ_POINT pPoint=NULL;
	pPoint=(PTJ_POINT)malloc(sizeof(TJ_POINT));
    pPoint->xPosition=xPos;
    pPoint->yPosition=yPos;
    pPoint->xVelocity=xVel;
    pPoint->yVelocity=yVel;
	pPoint->dead=0;
    return pPoint;
}

double getDistance(int x1,int y1, int x2,int y2 )
{
	//@ Return the distance between 2 points using euclidian distance formula;
	double distance;
	int delta_x = x2-x1;
	int delta_y = y2-y1;
	
	distance = pow(pow(delta_x,2.0f) + pow(delta_y,2.0f), (0.5f));
	return (distance);
}

void setMsg(void)
{
/*	GetClientRect(hwnd, &rc);
		//SetBkColor(hdc, RGB(0, 0, 255));
		SelectObject(ghdc, CreateFont(50, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, TEXT("Cambria")));
		SetTextColor(ghdc, RGB(200, 0, 0));
		SetBkColor(ghdc, TRANSPARENT);
		SetBkMode(ghdc, TRANSPARENT);
	
	str = TEXT("इवलेसे रोप लावियेले द्वारी | त्याचा वेलू गेला गगनावरी ||");
*/
}