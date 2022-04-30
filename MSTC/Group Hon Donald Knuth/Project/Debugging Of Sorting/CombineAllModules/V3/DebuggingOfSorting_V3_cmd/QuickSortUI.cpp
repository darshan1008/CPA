#include<Windows.h>
#include "DebuggingOfSorting.h"
#include "QuickSortHeaders.h"
#include<tchar.h>

//#include<stdbool.h>

int isNewIteration;
int isConditionSatisfied;


enum ArrowType { Horizontal, Vertical};
#define MyTimer 100
static int PAINTFLAG = 0;
static int TimerCount = 0;

const static TCHAR* ppNum[] = { TEXT("50"),TEXT("40"),TEXT("10"),TEXT("20"),TEXT("30")};

void AddArrow(HDC hdc, int StartX, int StartY,enum ArrowType type)
{
	HPEN hPen;
	hPen = CreatePen(PS_DOT, 1, RGB(0, 0, 0));
	SelectObject(hdc, hPen);
	MoveToEx(hdc, StartX, StartY, NULL);
	switch (type)
	{
	case Horizontal:
		LineTo(hdc, StartX + 50, StartY);
		LineTo(hdc, StartX + 40, StartY + 10);
		MoveToEx(hdc, StartX + 50, StartY,NULL);
		LineTo(hdc, StartX + 40, StartY - 10);
		break;
	case Vertical:
		LineTo(hdc, StartX, StartY + 30);
		LineTo(hdc, StartX - 10, StartY + 20);
		MoveToEx(hdc, StartX ,StartY + 30, NULL);
		LineTo(hdc, StartX + 10, StartY + 20);	
		break;
	default:
		break;
	}
}

void AddComparisonOperator(HDC hdc, int startX, int startY)
{
	HPEN hPen;
	hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	SelectObject(hdc, hPen);
	MoveToEx(hdc, startX, startY, NULL);
	LineTo(hdc, startX + 20, startY - 8);
	MoveToEx(hdc, startX, startY, NULL);
	LineTo(hdc, startX + 20, startY + 8);
	MoveToEx(hdc, startX, startY + 4, NULL);
	LineTo(hdc, startX + 20, startY + 12);
}

void AddIndexForArrayBoxes(HDC hdc,int left, int top, int numberOfElements)
{
	int iLeft = left;
	for (int i = 0; i < numberOfElements; i++)
	{
		//TextOut(hdc, iLeft, top, ppIndex[i], lstrlen(ppIndex[i]));
		FormatedTextOut(hdc, iLeft, top, (TCHAR*)"%d",i);
		iLeft = iLeft + 50;
	}
}

void AddDottedLineForLoop(HDC hdc,int x,int y,int CurrentLoop)
{
	HPEN hPen;
	//const static TCHAR* ppLoop[] = { TEXT("Loop1"),TEXT("Loop2"),TEXT("Loop3"),TEXT("Loop4"),TEXT("Loop5") };

	hPen = CreatePen(PS_DOT, 1, RGB(0, 0, 0));
	SelectObject(hdc, hPen);
	MoveToEx(hdc, x, y, NULL);
	LineTo(hdc, x + 300, y);

	SetTextColor(hdc, RGB(255, 0, 0));
	FormatedTextOut(hdc, x + 10, y + 2, (TCHAR*)("Loop"));
	FormatedTextOut(hdc, x + 45 , y + 2, (TCHAR*)"%d", CurrentLoop);
	//TextOut(hdc, x+10, y+2, ppLoop[CurrentLoop], lstrlen(ppLoop[CurrentLoop]));

	/*MoveToEx(hdc, 20, y+20, NULL);
	LineTo(hdc, x, y+20);*/
}

void AddSingleBox(HDC hdc, int left, int top, int penstyle, bool bHasStyle)
{
	HPEN hPen;
	HBRUSH hBrush;
	
	hPen = CreatePen(penstyle, 1, RGB(0, 0, 0));
	SelectObject(hdc, hPen);

	if (bHasStyle)
	{	
		hBrush = CreateSolidBrush(RGB(0, 0, 255));
		SelectObject(hdc, CreateHatchBrush(HS_BDIAGONAL, RGB(255,0 , 0)));
	}
	else
	{
		hBrush = CreateSolidBrush(RGB(255, 255, 255));
		SelectObject(hdc, hBrush);
	}

	Rectangle(hdc, left, top, (left + 40), (top + 40));

	DeleteObject(hPen);	
	DeleteObject(hBrush);
}
void SwapNumbers(HDC hdc, int left, int top, int numberOfElements, struct QuickSortData quicksortstruc)
{
	int iLeft = left;
	SetTextColor(hdc, RGB(0, 0, 0));
	
	for (int i = 0; i < numberOfElements; i++)
	{
		AddSingleBox(hdc, iLeft, top, PS_SOLID,FALSE);

		if (i == quicksortstruc.SwapElement.swapIndex1)
		{
			//TextOut(hdc, (iLeft + 10), (top + 10), ppNum[jSwap], lstrlen(ppNum[jSwap]));
			FormatedTextOut(hdc, (iLeft + 10), (top + 10), (TCHAR*)" %d ", quicksortstruc.arrayObj.pArr[quicksortstruc.SwapElement.swapIndex1]);
		}
		else if (i == quicksortstruc.SwapElement.swapIndex2)
		{
			//TextOut(hdc, (iLeft + 10), (top + 10), ppNum[iSwap], lstrlen(ppNum[iSwap]));
			FormatedTextOut(hdc, (iLeft + 10), (top + 10), (TCHAR*)" %d ", quicksortstruc.arrayObj.pArr[quicksortstruc.SwapElement.swapIndex2]);
		}
		else
		{
			TextOut(hdc, (iLeft + 10), (top + 10), ppNum[i], lstrlen(ppNum[i]));
			FormatedTextOut(hdc, (iLeft + 10), (top + 10), (TCHAR*)" %d ", quicksortstruc.arrayObj.pArr[i]);
		}
		iLeft = iLeft + 50;
	}
}

void SetBoxesForArray(HDC hdc,int left, int top, int numberOfElements, int iSwap, int jSwap,int *pArr)
{
	int iLeft = left;
	SetTextColor(hdc, RGB(0, 0, 0));
	bool bHasStyle = FALSE;
	for (int i = 0; i < numberOfElements; i++)
	{
		if (i == iSwap)
		{
			bHasStyle = TRUE;
		}
		else if (i == jSwap)
		{
			bHasStyle = TRUE;
		}

		AddSingleBox(hdc, iLeft, top, PS_SOLID, bHasStyle);

		FormatedTextOut(hdc, (iLeft + 10), (top + 10), (TCHAR*)"%d",pArr[i]);

		iLeft = iLeft + 50;
		bHasStyle = FALSE;
	}
}

void SetSidePane(HDC hdc, int left, int top,int pivote, int i,int j)
{
	//bool  bHasStyle = FALSE;
	const static TCHAR* ppijpivot[] = { TEXT("Pivot"),TEXT("i"),TEXT("j") };
	SetTextColor(hdc, RGB(250, 0, 0));
	TextOut(hdc, left + 350, top + 30, ppijpivot[0], lstrlen(ppijpivot[0]));
	TextOut(hdc, left + 420, top + 30, ppijpivot[1], lstrlen(ppijpivot[1]));
	TextOut(hdc, left + 470, top + 30, ppijpivot[2], lstrlen(ppijpivot[2]));

	HBRUSH hBrush;
	HPEN hPen;

	hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	SelectObject(hdc, hPen);
	hBrush = CreateSolidBrush(RGB(0, 255, 255));
	SelectObject(hdc, hBrush);

	Rectangle(hdc, left + 350, top + 50, (left + 390), (top + 90));
	Rectangle(hdc, left + 400, top + 50, (left + 440), (top + 90));
	Rectangle(hdc, left + 450, top + 50, (left + 490), (top + 90));
	
	SetTextColor(hdc, RGB(0, 0, 0));
	FormatedTextOut(hdc, left + 360, top + 60, (TCHAR*)"%d", pivote);
	FormatedTextOut(hdc, left + 410, top + 60, (TCHAR*)"%d", i);
	FormatedTextOut(hdc, left + 460, top + 60, (TCHAR*)"%d", j);
}

int AddLineToUI(int CurrentXPos, int CurrentYPos, HDC hdc, struct QuickSortData quicksortstruc)
{
	int retVal = 0;
	bool bUpdateY = FALSE;

	int origYPos = CurrentYPos;

	if (quicksortstruc.isConditionDraw == FALSE && quicksortstruc.isIndexDraw == FALSE && quicksortstruc.isSwapElementDraw == FALSE)
	{
		//const static TCHAR* ppGivenArray[] = { TEXT("Given Array") };
		SetTextColor(hdc, RGB(0, 0, 255));
		//TextOut(hdc, CurrentXPos, CurrentYPos , ppGivenArray[0], lstrlen(ppGivenArray[0]));
		SetBoxesForArray(hdc, CurrentXPos , CurrentYPos + 20 ,N, -1, -1,quicksortstruc.arrayObj.pArr);
		return 70;
	}

	int xOffset = 0;
	int yOffset = 50;

	// if (quicksortstruc.isNewIteration == ON)
	// {
	// 	bUpdateY = TRUE;
	// 	if (quicksortstruc.isSwapElementDraw == OFF)
	// 	{
	// 		if (quicksortstruc.arrayObj.j > 0)
	// 		{
	// 			CurrentYPos += 210;
	// 		}
	// 	}
	// 	else
	// 	{
	// 		CurrentYPos += 420;
	// 	}
	// }
	
	int X = CurrentXPos;
	int Y = CurrentYPos;
	if (quicksortstruc.arrayObj.j > 0)
	{
		xOffset = 50 * quicksortstruc.arrayObj.j;
	}
	
	if (quicksortstruc.isIndexDraw == ON)
	//if(0)
	{
		AddDottedLineForLoop(hdc, X, Y, quicksortstruc.arrayObj.j);
		AddIndexForArrayBoxes(hdc, X + 35, Y + 30, N);		
		SetBoxesForArray(hdc, X + 20, Y + 50, N, -1, -1,quicksortstruc.originalArrayObj.pArr);
		//int initialIVal = quicksortstruc.arrayObj.i - 1;
		if (quicksortstruc.originalArrayObj.pArr[quicksortstruc.arrayObj.j] <= quicksortstruc.arrayObj.pivote)
		{
			SetSidePane(hdc, X + 100, Y, quicksortstruc.arrayObj.pivote, quicksortstruc.arrayObj.i-1, quicksortstruc.arrayObj.j);
		}
		else
		{
			SetSidePane(hdc, X + 100, Y, quicksortstruc.arrayObj.pivote, quicksortstruc.arrayObj.i, quicksortstruc.arrayObj.j);
		}
		
		//return 100;
		retVal = 70;
	}
	X = CurrentXPos;
	Y = CurrentYPos;
	if (quicksortstruc.isConditionDraw == ON )
	//if(0)
	{
		AddArrow(hdc, X + 40 + xOffset, Y + 90, Vertical);
		AddSingleBox(hdc, X + 20 + xOffset, Y + 120, PS_DOT, false);
		FormatedTextOut(hdc, X + 30 + xOffset, Y + 130, (TCHAR*)"%d",quicksortstruc.originalArrayObj.pArr[quicksortstruc.arrayObj.j]);
		AddComparisonOperator(hdc, X + 70 + xOffset, Y + 140);
		AddSingleBox(hdc, X + 100 + xOffset, Y + 120, PS_DOT, false);
		SetTextColor(hdc, RGB(0, 0, 255));
		FormatedTextOut(hdc, X + 110 + xOffset, Y + 130, (TCHAR*)"%d",quicksortstruc.arrayObj.pivote);
		
		//if (ON == quicksortstruc.isConditionSatisfied)
			
		if(quicksortstruc.originalArrayObj.pArr[quicksortstruc.arrayObj.j] <=  quicksortstruc.arrayObj.pivote)
		{
			SetTextColor(hdc, RGB(0, 140, 0));
			FormatedTextOut(hdc, X + 150 + xOffset, Y + 130, (TCHAR*)("Condition TRUE"));
			SetSidePane(hdc, X + 100, Y + 70, quicksortstruc.arrayObj.pivote, quicksortstruc.arrayObj.i, quicksortstruc.arrayObj.j);
		}
		else
		{
			SetTextColor(hdc, RGB(140, 0, 0));
			FormatedTextOut(hdc, X + 150 + xOffset, Y + 130, (TCHAR*)("Condition FALSE"));
		}	 
		//return 5;
		retVal += 100;		
	}

	X = CurrentXPos;
	Y = CurrentYPos;
	if (quicksortstruc.isSwapElementDraw == ON)
	{
		xOffset = (X * quicksortstruc.arrayObj.j) + (25 * quicksortstruc.arrayObj.j) + 10;
		//TextOut(hdc, X + 150 + xOffset, Y + 150, ppFailSuccessCondition[1], lstrlen(ppFailSuccessCondition[1]));
		// AddIndexForArrayBoxes(hdc, X + 35, Y + 200, N);
		// SetBoxesForArray(hdc, X + 20, Y + 220, N, -1, -1,quicksortstruc.arrayObj.pArr);
		// //quicksortstruc.arrayObj.i++;
		////SetSidePane(hdc, X, Y + 170,quicksortstruc.arrayObj.pivote, quicksortstruc.arrayObj.i, quicksortstruc.arrayObj.j);
		// SetTextColor(hdc, RGB(255, 0, 255));
		
		////FormatedTextOut(hdc, X + quicksortstruc.SwapElement.swapIndex1 * 50 + 25, Y + 270, (TCHAR*)"%d           %d",quicksortstruc.SwapElement.swapIndex1,quicksortstruc.SwapElement.swapIndex2);
		////FormatedTextOut(hdc, X + xOffset + 25, Y + 270, (TCHAR*)"%d",quicksortstruc.SwapElement.swapIndex2);
		
		if (quicksortstruc.SwapElement.swapIndex1 != quicksortstruc.SwapElement.swapIndex2)
		{
			SetBoxesForArray(hdc, X + 20, Y + 180, N, quicksortstruc.SwapElement.swapIndex1, quicksortstruc.SwapElement.swapIndex2, quicksortstruc.originalArrayObj.pArr);
			// SetTextColor(hdc, RGB(255, 0, 0));
			// TextOut(hdc, X + 270, Y + 310, ppFailSuccessCondition[2], lstrlen(ppFailSuccessCondition[2]));
			// SwapNumbers(hdc, X + 20, Y + 300, N, quicksortstruc.SwapElement.swapIndex1, quicksortstruc.SwapElement.swapIndex2);
			SwapNumbers(hdc, X + 20, Y + 230, N, quicksortstruc);
			retVal += 110;
		}
		else
		{
		    SetTextColor(hdc, RGB(0, 0,250));
			FormatedTextOut(hdc, X + 650, Y + 130, (TCHAR*)("DO NOT SWAP AS i = j"));
			return retVal;
			retVal += 10;
		}
		// //return 210;	
	}

	return retVal;
}

void DisplayQuicksort(HDC hdc,int xPos,int yPos,QUICKSORTDATA dataObj)
{
		//MoveToEx(hdc,(cxClient/3 ) - 50,yPos,NULL);
		//LineTo(hdc,cxClient/2,yPos);
		int iCounter2;
		FormatedTextOut(hdc,xPos,yPos, (TCHAR*)"A:: ");
		xPos += 30;
		for(iCounter2 = 0; iCounter2 < N ; iCounter2++, xPos+=30)
		{
			FormatedTextOut(hdc,xPos,yPos, (TCHAR*)" %d ",dataObj.arrayObj.pArr[iCounter2]);
		}
		xPos += 30;
		//xPos = (cxClient/3);
		FormatedTextOut(hdc,xPos,yPos, (TCHAR*)"\ti : [%d]",dataObj.arrayObj.i);
		xPos += 50;
		FormatedTextOut(hdc,xPos,yPos, (TCHAR*)"\tj : [%d]",dataObj.arrayObj.j);
		xPos += 50;
		FormatedTextOut(hdc,xPos,yPos, (TCHAR*)"\tpivote : [%d]",dataObj.arrayObj.pivote);
		xPos += 50;
		FormatedTextOut(hdc,xPos,yPos, (TCHAR*)"\tswitch:[%d]",dataObj.isSwapElementDraw);
		xPos += 100;
		if(ON == dataObj.isSwapElementDraw)
		{
			FormatedTextOut(hdc,xPos,yPos, (TCHAR*)"\t[1]:[%d]",dataObj.SwapElement.swapIndex1);
			xPos += 100;
			FormatedTextOut(hdc,xPos,yPos, (TCHAR*)"\t[2]:[%d]",dataObj.SwapElement.swapIndex2);
			
		}

		//MoveToEx(hdc,(cxClient/3 ) - 50,yPos,NULL);
		//LineTo(hdc,cxClient/2,yPos);
		
}
