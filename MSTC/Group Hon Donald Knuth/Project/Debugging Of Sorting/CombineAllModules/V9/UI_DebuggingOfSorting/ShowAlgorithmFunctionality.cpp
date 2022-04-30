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
	hMyFont = CreateFont(20,0,0,0,700,0,0,0,0,0,0,0,FF_DONTCARE,"Arial Bold");
	SelectObject(hdc,hMyFont);

	SetTextColor(hdc,RGB(0,0,0));
	SetBkColor(hdc,RGB(255,204,203));

	for(iCount = 0; iCount < g_pStrVec->iVectorSize; ++iCount,++iLine)
    {
		TextOutA(hdc, X_OFFSET_1 * cxCaps, iLine*cyChar*2, g_pStrVec->ppString[iCount], strlen(g_pStrVec->ppString[iCount])); 
	}
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
		(iLine2 >= g_pStrVec->iVectorSize-3))		//argument checking
	{		
		MessageBox((HWND)NULL,TEXT("INVALID ARGUMENTS"),TEXT("PrintArrow"),MB_ICONERROR);
		DeleteDC(hdc);
		return(EXIT_FAILURE);
    }


	if(iLine1 >= 5 && g_pStrVec->iVectorSize < 16)			//for line1 jumping non numbered lines(for insertion sort)
		iLine1++;
	else if (iLine1 >= 5 && g_pStrVec->iVectorSize > 16)		//for line1 jumping non numbered lines(for quick sort)
		iLine1 = iLine1 + 3;
	
	if(iLine2 >= 5 && g_pStrVec->iVectorSize < 16)			//for line2 jumping non numbered lines(for insertion sort)
		iLine2++;
	else if (iLine2 >= 5 && g_pStrVec->iVectorSize > 16)		//for line2 jumping non numbered lines(for quick sort)
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
		if(( iCount == 5 && g_pStrVec->iVectorSize < 16) || (( iCount>=6 && iCount <=8) && g_pStrVec->iVectorSize > 16))
			continue;	
		
		TextOutA(hdc, X_OFFSET_1 * cxCaps +15, ((iCount+3)*cyChar*2), TEXT("-->"), strlen(TEXT("-->")));
	}
	DeleteDC(hdc);
	return 0;
}

int PrintArrowForBubbleSort(HDC hdc, int iLine1, int iLine2, int cyChar, int cxCaps)
{
	int iCount;

	PrintAlgorithm(hdc, cyChar, cxCaps);			//Repainting for removing arrows from privious call
	if (iLine1 == 0 || iLine2 == 0)
	{
		return (0);
	}

	iLine1++;
	iLine2++;

	SetBkColor(hdc, RGB(144, 238, 144));						//setting background color for arrow

	if (iLine1 == iLine2)								//for printing arrow on single line
	{
		DeleteDC(hdc);
		return 0;
	}

	for (iCount = iLine1; iCount <= iLine2; iCount++)
	{
		if ((iCount == 5 && g_pStrVec->iVectorSize < 16) || ((iCount >= 6 && iCount <= 8) && g_pStrVec->iVectorSize > 16))
			continue;

		TextOutA(hdc, X_OFFSET_1 * cxCaps + 15, ((iCount ) * cyChar * 2), TEXT("-->"), strlen(TEXT("-->")));
	}
	DeleteDC(hdc);
	return 0;
}

void ReleaseAll(void)
{
    if(g_pStrVec != NULL)
    {
        DestroyStringVector(g_pStrVec); 
        g_pStrVec = NULL; 
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
    errno_t ret = fopen_s(&fp,lpFileName, "r");
    FAIL_EXIT_IF(fp == NULL, "Could not open input file", "fopen");  

    lp_stringVec = CreateStringVector(); 

    memset(chBuffer, 0, BUFFER_SIZE); 
    while(fgets(chBuffer, BUFFER_SIZE, fp) != NULL)
    {
        iStrLen = strnlen_s(chBuffer, BUFFER_SIZE); 
        pStr = (PCHAR)Xcalloc(1, iStrLen+1); 
        strncpy_s(pStr, BUFFER_SIZE, chBuffer, iStrLen);
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
	CHAR** ppTemp = NULL;
	ppTemp = (CHAR * *)realloc(pStrVec->ppString, pStrVec->iVectorSize * sizeof(PCHAR));

	pStrVec->ppString = ppTemp;
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

/* Showing Information Window */

void DrawWelcomeWindow(HDC hdc, int cxClient, int cyClient)
{
	HPEN hPen;
	HBRUSH hBrush;

	hPen = CreatePen(PS_SOLID, 2, RGB(255, 105, 180));
	SelectObject(hdc, hPen);

	hBrush = CreateSolidBrush(RGB(255, 255, 191));
	SelectObject(hdc, hBrush);
	Rectangle(hdc, 0, 0, cxClient, cyClient);//Whole window rectangle
	DrawLineUtil(hdc, 0, cyClient - 60, cxClient, cyClient - 60);
	DrawLineUtil(hdc, cxClient / 2, 0, cxClient / 2, cyClient - 60);
	
	HFONT hMyFont;
	RECT rect;

	SetBkColor(hdc, RGB(152, 251, 152));
	SetTextColor(hdc, RGB(255, 0, 0));
	hMyFont = CreateFont(25, 0, 0, 0, 600, 0, 0, 0, 0, 0, 0, 0, FF_DONTCARE, "Arial Bold");
	SelectObject(hdc, hMyFont);

	hBrush = CreateSolidBrush(RGB(152, 251, 152));
	SelectObject(hdc, hBrush);

	Rectangle(hdc, 50, 30, 250, 60);			//Left 1st level 
	rect.left = 50;
	rect.top = 30;
	rect.right = 250;
	rect.bottom = 60;
	TCHAR text1[32] = TEXT("SORTING");
	DrawText(hdc, text1, -1, &rect, DT_CENTER);

	Rectangle(hdc, (cxClient / 2) + 50, 30, (cxClient / 2) + 250, 60);			//Right 1st level
	rect.left = (cxClient / 2) + 50;
	rect.top = 30;
	rect.right = (cxClient / 2) + 250;
	rect.bottom = 60;
	TCHAR text2[32] = TEXT("TYPES");
	DrawText(hdc, text2, -1, &rect, DT_CENTER);
	
	hBrush = CreateSolidBrush(RGB(255, 228, 255));
	SelectObject(hdc, hBrush);
	Rectangle(hdc, 50, 80, (cxClient / 2) - 40, 200);						//Left second level 

	PrintText(hdc, cxClient, cyClient);
	return;
}

void PrintText(HDC hdc, int cxClient, int cyClient)
{
	HFONT hMyFont;
	
	SetBkColor(hdc, RGB(152, 251, 152));
	SetTextColor(hdc, RGB(255, 0, 0));
	hMyFont = CreateFont(25, 0, 0, 0, 600, 0, 0, 0, 0, 0, 0, 0, FF_DONTCARE, "Arial Bold");
	SelectObject(hdc, hMyFont);

	SetBkColor(hdc, RGB(255, 228, 255));
	SetTextColor(hdc, RGB(0, 0, 0));
	hMyFont = CreateFont(20, 0, 0, 0, 400, 0, 0, 0, 0, 0, 0, 0, FF_DONTCARE, "Arial Bold");
	SelectObject(hdc, hMyFont);
	
	TextOut(hdc, 60, 90, TEXT("1] Elements listed in order"), strlen(TEXT("1] Elements listed in order")));
	TextOut(hdc, 60, 130, TEXT("2] Permutations of the original inputs elements with order"), strlen(TEXT("2] Permutations of the original inputs elements with order")));
	
	hMyFont = CreateFont(25, 0, 0, 0, 700, 0, 0, 0, 0, 0, 0, 0, FF_DONTCARE, "Arial Bold");
	SelectObject(hdc, hMyFont);
	
	SetBkColor(hdc, RGB(60, 250, 30));

	int len = strlen(TEXT("CHARACTERISTICS :: "));
	int yPos = cyClient / 3;
	int xPos = 50;

	xPos = 50; yPos = cyClient / 3;
	SetBkColor(hdc, RGB(200, 180, 250));
	TextOut(hdc, xPos, yPos, TEXT("CHARACTERISTICS :: "), len);

	xPos += 20; yPos += 40;
	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, RGB(50,50,250));
	TextOut(hdc, xPos, yPos, TEXT("Stability"), strlen(TEXT("Stability")));
	
	xPos += 60; yPos += 40;
	TextOut(hdc, xPos, yPos, TEXT("Parallelism"), strlen(TEXT("Parallelism")));

	xPos += 40; yPos += 40;
	TextOut(hdc, xPos, yPos, TEXT("Adaptability"), strlen(TEXT("Adaptability")));

	xPos += 60; yPos += 40;
	TextOut(hdc, xPos, yPos, TEXT("Time Complexity"), strlen(TEXT("Time Complexity")));

	xPos += 60; yPos += 40;
	TextOut(hdc, xPos, yPos, TEXT("Space Complexity"), strlen(TEXT("Space Complexity")));
	
	xPos += 30; yPos += 40;
	TextOut(hdc, xPos, yPos, TEXT("Recursive / non-recursive "), strlen(TEXT("Recursive / non-recursive ")));


	xPos = 50; yPos += 80;

	hMyFont = CreateFont(28, 0, 0, 0, 700, 0, 0, 0, 0, 0, 0, 0, FF_DONTCARE, "Arial Bold");
	SelectObject(hdc, hMyFont);
	SetTextColor(hdc, RGB(180, 100,0));
	TextOut(hdc, xPos,yPos, TEXT("To Proceed, click here..."), strlen("To Proceed, click here..."));

	SetBkColor(hdc, RGB(255, 255, 191));
	SetTextColor(hdc, RGB(0, 0, 0));
	yPos = 120;
	
	hMyFont = CreateFont(25, 0, 0, 0, 700, 0, 0, 0, 0, 0, 0, 0, FF_DONTCARE, "Calibri");
	SelectObject(hdc, hMyFont);
	const int gap_1 = 80;
	const int gap_2 = 20;
	SetBkMode(hdc, TRANSPARENT);

	TextOut(hdc, (cxClient / 2) + gap_2, yPos, TEXT("I] Simple,good for small data sets."), strlen(TEXT("I] Simple,good for small data sets.")));
	Ellipse(hdc, cxClient - 200, yPos - 20 , cxClient - 50, yPos + 40);
	TextOut(hdc, cxClient - 170, yPos , TEXT("INSERTION"), strlen(TEXT("INSERTION")));
	yPos += gap_1;

	TextOut(hdc, (cxClient / 2) + gap_2, yPos, TEXT("II] Merging based on sorted lists.(Step-by-Step)"), strlen(TEXT("II] Merging based on sorted lists.(Step-by-Step)")));
	Ellipse(hdc, cxClient - 200, yPos - 20, cxClient - 50, yPos + 40);
	TextOut(hdc, cxClient - 160, yPos, TEXT("MERGE"), strlen(TEXT("MERGE")));
	yPos += gap_1;
	
	TextOut(hdc, (cxClient / 2) + gap_2, yPos, TEXT("III] Selection sorts improved version."), strlen(TEXT("III] Selection sorts improved version.")));
	Ellipse(hdc, cxClient - 200, yPos - 20, cxClient - 50, yPos + 40);
	TextOut(hdc, cxClient - 150, yPos, TEXT("HEAP"), strlen(TEXT("HEAP")));
	yPos += gap_1;

	TextOut(hdc, (cxClient / 2) + gap_2, yPos, TEXT("IV] Swaping between consecutive elements."), strlen(TEXT("IV] Swaping between consecutive elements.")));
	Ellipse(hdc, cxClient - 200, yPos - 20, cxClient - 50, yPos + 40);
	TextOut(hdc, cxClient - 160, yPos, TEXT("BUBBLE"), strlen(TEXT("BUBBLE")));
	yPos += gap_1;

	TextOut(hdc, (cxClient / 2) + gap_2, yPos, TEXT("V] Insertion sorts improved version."), strlen(TEXT("V] Insertion sorts improved version.")));
	Ellipse(hdc, cxClient - 200, yPos - 20, cxClient - 50, yPos + 40);
	TextOut(hdc, cxClient - 150, yPos, TEXT("SHELL"), strlen(TEXT("SHELL")));
	yPos += gap_1;

	TextOut(hdc, (cxClient / 2) + gap_2, yPos, TEXT("VI] Good for relatively large data."), strlen(TEXT("VI] Good for relatively large data.")));
	Ellipse(hdc, cxClient - 200, yPos - 20, cxClient - 50, yPos + 40);
	TextOut(hdc, cxClient - 160, yPos, TEXT("QUICK "), strlen(TEXT("QUICK")));

	return;
}

void DrawInsertionWindow(HDC hdc, int cxClient, int cyClient)
{
	HPEN hPen;
	HBRUSH hBrush;

	hPen = CreatePen(PS_SOLID, 1, RGB(255, 105, 180));
	SelectObject(hdc, hPen);

	hBrush = CreateSolidBrush(RGB(255, 255, 191));
	SelectObject(hdc, hBrush);
	Rectangle(hdc, 0, 0, cxClient, cyClient);					//Whole window rectangle
	DrawLineUtil(hdc, 0, 70, cxClient, 70);
	DrawLineUtil(hdc, 0, 380, cxClient, 380);
	DrawLineUtil(hdc, 250, 575, 600, 475);
	DrawLineUtil(hdc, 250, 575, 600, 575);
	DrawLineUtil(hdc, 250, 575, 600, 675);
	DrawLineUtil(hdc, 950, 575, 1000, 575);
	DrawLineUtil(hdc, 1200, 575, 1250, 575);
	DrawLineUtil(hdc, 950, 675, 1000, 675);
	DrawLineUtil(hdc, 0, 740, cxClient, 740);

	hBrush = CreateSolidBrush(RGB(152, 251, 152));
	SelectObject(hdc, hBrush);
	Rectangle(hdc, 50, 90, 250, 140);			//Rectangle for concept

	Rectangle(hdc, 50, 550, 250, 600);			//For Details
	Rectangle(hdc, 600, 450, 950, 500);			//For In-place sorting
	Rectangle(hdc, 600, 550, 950, 600);			//Time Complexity
	Rectangle(hdc, 600, 650, 950, 700);			//Space Complexity
	Rectangle(hdc, 1000, 550, 1200, 600);		//Best
	Rectangle(hdc, 1250, 550, 1520, 600);		//Avg & worst
	Rectangle(hdc, 1000, 650, 1200, 700);		//next to Space complixity 

	PrintTextInsertion(hdc, cxClient, cyClient);
	return;
}

void PrintTextInsertion(HDC hdc, int cxClient, int cyClient)
{
	HFONT hMyFont;

	SetBkColor(hdc, RGB(152, 251, 152));
	SetTextColor(hdc, RGB(255, 0, 0));
	hMyFont = CreateFont(25, 0, 0, 0, 600, 0, 0, 0, 0, 0, 0, 0, FF_DONTCARE, "Arial Bold");
	SelectObject(hdc, hMyFont);

	SetBkColor(hdc, RGB(255, 255, 191));
	TextOut(hdc, 50, cyClient - 100, TEXT("TO PROCEED FURTHER, CLICK HERE"), strlen("TO PROCEED FURTHER, CLICK HERE"));

	SetBkColor(hdc, RGB(152, 251, 152));
	hMyFont = CreateFont(30, 0, 0, 0, 700, 0, 0, 0, 0, 0, 0, 0, FF_DONTCARE, "Arial Bold");
	SelectObject(hdc, hMyFont);
	SetTextColor(hdc, RGB(0, 0, 0));
	TextOut(hdc, 630, 457, TEXT("IN-PLACE SORTING"), strlen(TEXT("IN-PLACE SORTING")));
	TextOut(hdc, 630, 557, TEXT("TIME COMPLEXITY"), strlen(TEXT("TIME COMPLEXITY")));
	TextOut(hdc, 630, 657, TEXT("SPACE COMPLEXITY"), strlen(TEXT("SPACE COMPLEXITY")));
	TextOut(hdc, 1020, 557, TEXT("BEST = O(n)"), strlen(TEXT("BEST = O(n)")));
	TextOut(hdc, 1255, 557, TEXT("AVG/WORST = O(n^2)"), strlen(TEXT("AVG/WORST = O(n^2)")));
	TextOut(hdc, 1070, 657, TEXT("O(1)"), strlen(TEXT("O(1)")));

	SetBkColor(hdc, RGB(255, 255, 191));
	SetTextColor(hdc, RGB(0, 0, 0));

	TextOut(hdc, 50, 155, TEXT("I] Considers one element from given data set(key)."),
		strlen(TEXT("I] Considers one element from given data set(key).")));

	TextOut(hdc, 50, 195, TEXT("II] Checks it with the largest data from previously sorted list."),
		strlen(TEXT("II] Checks it with the largest data from previously sorted list.")));

	TextOut(hdc, 50, 235, TEXT("III] If the key is smaller, shifts all large values to create space & insert it at correct position."),
		strlen(TEXT("III] If the key is smaller, shifts all large values to create space & insert it at correct position.")));

	TextOut(hdc, 50, 275, TEXT("IV] If key is greater,leaves it at its place & considers nest element for comparison."),
		strlen(TEXT("IV] If key is greater,leaves it at its place & considers nest element for comparison.")));

	TextOut(hdc, 50, 315, TEXT("v] Repeats until all elements are covered."),
		strlen(TEXT("v] Repeats until all elements are covered.")));


	return;
}

void DrawQuickWindow(HDC hdc, int cxClient, int cyClient)
{
	HPEN hPen;
	HBRUSH hBrush;

	hPen = CreatePen(PS_SOLID, 1, RGB(255, 105, 180));
	SelectObject(hdc, hPen);

	hBrush = CreateSolidBrush(RGB(255, 255, 191));
	SelectObject(hdc, hBrush);
	Rectangle(hdc, 0, 0, cxClient, cyClient);					//Whole window rectangle
	DrawLineUtil(hdc, 0, 70, cxClient, 70);
	DrawLineUtil(hdc, 0, 355, cxClient, 355);
	DrawLineUtil(hdc, 250, 575, 600, 400);
	DrawLineUtil(hdc, 250, 575, 600, 575);
	DrawLineUtil(hdc, 250, 575, 600, 750);
	DrawLineUtil(hdc, 950, 575, 1000, 575);
	DrawLineUtil(hdc, 1200, 575, 1250, 575);
	DrawLineUtil(hdc, 950, 750, 1000, 750);
	DrawLineUtil(hdc, 150, 550, 150, 420);
	DrawLineUtil(hdc, 150, 600, 150, 730);
	DrawLineUtil(hdc, 0, cyClient - 50, cxClient, cyClient - 50);

	hBrush = CreateSolidBrush(RGB(152, 251, 152));
	SelectObject(hdc, hBrush);
	Rectangle(hdc, 50, 90, 250, 140);			//Rectangle for concept

	Rectangle(hdc, 50, 550, 250, 600);			//For Details
	Rectangle(hdc, 50, 380, 350, 420);			//For In-place sorting
	Rectangle(hdc, 50, 730, 360, 770);			//Developed by

	Rectangle(hdc, 600, 380, 950, 420);			//For Divide and conqure
	Rectangle(hdc, 600, 550, 950, 600);			//Time Complexity
	Rectangle(hdc, 600, 730, 950, 770);			//Space Complexity
	Rectangle(hdc, 1000, 550, 1230, 600);		//Best
	Rectangle(hdc, 1250, 550, 1520, 600);		//Avg & worst
	Rectangle(hdc, 1000, 730, 1200, 770);		//next to Space complixity

	PrintTextQuick(hdc, cxClient, cyClient);
	return;
}

void PrintTextQuick(HDC hdc, int cxClient, int cyClient)
{
	HFONT hMyFont;

	SetBkColor(hdc, RGB(152, 251, 152));
	SetTextColor(hdc, RGB(255, 0, 0));
	hMyFont = CreateFont(35, 0, 0, 0, 700, 0, 0, 0, 0, 0, 0, 0, FF_DONTCARE, "Arial Bold");
	SelectObject(hdc, hMyFont);

	TextOut(hdc, (cxClient / 2) - 138, 20, TEXT("QUICK SORT"), strlen(TEXT("QUICK SORT")));
	TextOut(hdc, 75, 100, TEXT("CONCEPT"), strlen(TEXT("CONCEPT")));
	TextOut(hdc, 80, 558, TEXT("DETAILS"), strlen(TEXT("DETAILS")));

	SetBkColor(hdc, RGB(255, 255, 191));
	TextOut(hdc, 50, cyClient - 45, TEXT("TO PROCEED FURTHER, CLICK HERE"), strlen("TO PROCEED FURTHER, CLICK HERE"));

	SetBkColor(hdc, RGB(152, 251, 152));
	hMyFont = CreateFont(30, 0, 0, 0, 700, 0, 0, 0, 0, 0, 0, 0, FF_DONTCARE, "Arial Bold");
	SelectObject(hdc, hMyFont);
	SetTextColor(hdc, RGB(0, 0, 0));

	TextOut(hdc, 630, 386, TEXT("DIVIDE AND CONQUER"), strlen(TEXT("DIVIDE AND CONQUER")));
	TextOut(hdc, 75, 386, TEXT("IN-PLACE SORTING"), strlen(TEXT("IN-PLACE SORTING")));
	TextOut(hdc, 650, 560, TEXT("TIME COMPLEXITY"), strlen(TEXT("TIME COMPLEXITY")));
	TextOut(hdc, 650, 735, TEXT("SPACE COMPLEXITY"), strlen(TEXT("SPACE COMPLEXITY")));
	TextOut(hdc, 1003, 557, TEXT("BEST = O(n*log(n))"), strlen(TEXT("BEST = O(n*log(n))")));
	TextOut(hdc, 1275, 557, TEXT("WORST = O(n^2)"), strlen(TEXT("WORST = O(n^2)")));
	TextOut(hdc, 1050, 735, TEXT("O(log n)"), strlen(TEXT("O(log n)")));
	TextOut(hdc, 52, 735, TEXT("Developed by Tony Hoare"), strlen(TEXT("Developed by Tony Hoare")));

	SetBkColor(hdc, RGB(255, 255, 191));
	SetTextColor(hdc, RGB(0, 0, 0));
	TextOut(hdc, 50, 155, TEXT("I] Selects pivot element from given dataset."),
		strlen(TEXT("I] Selects pivot element from given dataset.")));

	TextOut(hdc, 50, 195, TEXT("II] Pivot partitions the data into 2 non-empty sets."),
		strlen(TEXT("II] Pivot partitions the data into 2 non-empty sets.")));

	TextOut(hdc, 50, 235, TEXT("III] Comparison of pivot with every data element brings pivot at a position where leftside values are less and rightside"),
		strlen(TEXT("III] Comparison of pivot with every data element brings pivot at a position where leftside values are less and rightside")));

	TextOut(hdc, 50, 275, TEXT("      values are greater than it."),
		strlen(TEXT("      values are greater than it.")));

	TextOut(hdc, 50, 315, TEXT("v] Recursively executes step 3 for generated 2 sets."),
		strlen(TEXT("v] Recursively executes step 3 for generated 2 sets.")));

	return;
}
