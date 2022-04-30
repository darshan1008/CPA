
#include "ShowAlgorithmHeader.h"

void DrawLine(HDC hdc,int xsrc,int ysrc,int xdes,int ydes)
{
	MoveToEx(hdc,xsrc,ysrc,NULL);
    LineTo(hdc,xdes,ydes);
}

void PaintDesign(HDC hdc,int cxClient,int cyClient)
{
	HPEN hPen;
	HBRUSH hBrush;
	HFONT hMyFont;
	
	hPen = CreatePen(PS_SOLID,1,RGB(255,105,180));
    SelectObject(hdc,hPen);

    hBrush = CreateSolidBrush(RGB(255,255,255));
    SelectObject(hdc,hBrush);
            
	DrawLine(hdc,0,0,cxClient,0);
	DrawLine(hdc,0,0,0,cyClient);
	DrawLine(hdc,cxClient,0,cxClient,cyClient);
	DrawLine(hdc,0,cyClient,cxClient,cyClient);
	DrawLine(hdc,3*cxClient/10,0,3*cxClient/10,cyClient);


	hBrush = CreateSolidBrush(RGB(255,204,203));
           
	Rectangle(hdc,20,15,(3*cxClient/10)-20,cyClient-20);		//Algorithm area rectangles
	Rectangle(hdc,20,15,(3*cxClient/10)-20,50);
	 SelectObject(hdc,hBrush);
	Rectangle(hdc,40,70,(3*cxClient/10)-40,cyClient-40);

	SetBkColor(hdc,RGB(255,255,255));
	SetTextColor(hdc,RGB(255,0,0));
	hMyFont = CreateFont(25,0,0,0,700,0,1,0,0,0,0,0,FF_DONTCARE,"Arial Bold");
	SelectObject(hdc,hMyFont);

	TextOut(hdc,(3*cxClient/10)/4,20,TEXT("ALGORITHM"),strlen(TEXT("ALGORITHM")));
	DeleteObject(hPen);
    DeleteObject(hBrush);
	
}

void PrintAlgorithm(HDC hdc,int cyChar,int cxCaps)
{
	HFONT hMyFont;
	int iCount,iLine = 3;
	//HDC hdc = CreateCompatibleDC(av_hdc);
	hMyFont = CreateFont(20,0,0,0,700,0,0,0,0,0,0,0,FF_DONTCARE,"Arial Bold");
	SelectObject(hdc,hMyFont);

	SetTextColor(hdc,RGB(0,0,0));
	SetBkColor(hdc,RGB(255,204,203));

	for(iCount = 0; iCount < gpStrVec->iVectorSize; ++iCount,++iLine)
    {
		TextOutA(hdc, X_OFFSET_1 * cxCaps, iLine*cyChar*2, gpStrVec->ppString[iCount], strlen(gpStrVec->ppString[iCount])); 
	}
	//DeleteDC(hdc);
}

int PrintArrow(HDC hdc,int iLine1,int iLine2,int cyChar,int cxCaps)
{
	int iCount;
	
	PrintAlgorithm(hdc,cyChar,cxCaps);			//Repainting for removing arrows from privious call
	if(iLine1 == 0 || iLine2 == 0)
	{
		return (0);
	}
	iLine1++;
	iLine2++;
	if(	(iLine1 < 2 || iLine2 < 2) ||
		(iLine1 > iLine2) || 
		(iLine2 >= gpStrVec->iVectorSize-3))		//argument checking
	{		
		MessageBox((HWND)NULL,TEXT("INVALID ARGUMENTS"),TEXT("PrintArrow"),MB_ICONERROR);
		DeleteDC(hdc);
		return(EXIT_FAILURE);
    }


	if(iLine1 >= 5 && gpStrVec->iVectorSize < 16)			//for line1 jumping non numbered lines(for insertion sort)
		iLine1++;
	else if (iLine1 >= 5 && gpStrVec->iVectorSize > 16)		//for line1 jumping non numbered lines(for quick sort)
		iLine1 = iLine1 + 3;
	
	if(iLine2 >= 5 && gpStrVec->iVectorSize < 16)			//for line2 jumping non numbered lines(for insertion sort)
		iLine2++;
	else if (iLine2 >= 5 && gpStrVec->iVectorSize > 16)		//for line2 jumping non numbered lines(for quick sort)
		iLine2 = iLine2 + 3;
	
	SetBkColor(hdc, RGB(144,238,144));						//setting background color for arrow

	if(iLine1 == iLine2)								//for printing arrow on single line
	{
		TextOutA(hdc, X_OFFSET_1 * cxCaps +15, ((iLine1+3)*cyChar*2), TEXT("-->"), strlen(TEXT("-->")));
		DeleteDC(hdc);
		return 0;
	}

	for(iCount = iLine1; iCount <= iLine2; iCount++)
	{
		if(( iCount == 5 && gpStrVec->iVectorSize < 16) || (( iCount>=6 && iCount <=8) && gpStrVec->iVectorSize > 16))
			continue;	
		
		TextOutA(hdc, X_OFFSET_1 * cxCaps +15, ((iCount+3)*cyChar*2), TEXT("-->"), strlen(TEXT("-->")));
	}
	DeleteDC(hdc);
	return 0;
}


void ReleaseAll(void)
{
    if(gpStrVec != NULL)
    {
        DestroyStringVector(gpStrVec); 
        gpStrVec = NULL; 
    }
}



PSTRINGVECTOR ReadFileInMemory(LPSTR lpFileName)
{
    #define BUFFER_SIZE 48

    FILE* fp = NULL; 
    CHAR chBuffer[BUFFER_SIZE]; 
    PCHAR pStr = NULL; 
    int iStrLen; 
	PSTRINGVECTOR lp_stringVec = NULL;
    fp = fopen(lpFileName, "r");
    FAIL_EXIT_IF(fp == NULL, "Could not open input file", "fopen");  

    lp_stringVec = CreateStringVector(); 

    memset(chBuffer, 0, BUFFER_SIZE); 
    while(fgets(chBuffer, BUFFER_SIZE, fp) != NULL)
    {
        iStrLen = strnlen_s(chBuffer, BUFFER_SIZE); 
        pStr = (PCHAR)Xcalloc(1, iStrLen+1); 
        strncpy(pStr, chBuffer, iStrLen); 
        PushBack(lp_stringVec, pStr); 
        memset(chBuffer, 0, BUFFER_SIZE); 
    }

    fclose(fp); 
    fp = NULL;     
    
    return (lp_stringVec); 
}

PSTRINGVECTOR CreateStringVector(void)
{
    PSTRINGVECTOR pStrVec = NULL; 

    pStrVec = (PSTRINGVECTOR)Xcalloc(1, sizeof(STRINGVECTOR)); 
    return (pStrVec); 
}

int PushBack(PSTRINGVECTOR pStrVec, CHAR* pNewString)
{
    pStrVec->iVectorSize += 1; 
    pStrVec->ppString = (CHAR**)realloc(pStrVec->ppString, pStrVec->iVectorSize * sizeof(PCHAR)); 
    pStrVec->ppString[pStrVec->iVectorSize - 1] = pNewString; 
    return (SUCCESS); 
}

int DestroyStringVector(PSTRINGVECTOR pStrVec)
{
    int iCnt; 
    for(iCnt = 0; iCnt < pStrVec->iVectorSize; ++iCnt)
        free(pStrVec->ppString[iCnt]); 
    free(pStrVec->ppString);
    free(pStrVec);  
    return (SUCCESS); 
}

LPVOID Xcalloc(size_t cbSize, size_t cbSizePerElement)
{
    LPVOID pNewObject = NULL; 

    pNewObject = calloc(cbSize, cbSizePerElement); 
    FAIL_EXIT_IF(pNewObject == NULL, "Out of virtual memory", "calloc"); 

    return (pNewObject); 
}
