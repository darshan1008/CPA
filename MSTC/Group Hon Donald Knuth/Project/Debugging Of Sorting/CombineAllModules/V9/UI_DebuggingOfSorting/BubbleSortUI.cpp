#include"BubbleSortHeader.h"
#include<tchar.h>

int FormatedTextOut(HDC hdc, int x, int y, TCHAR* pszFormat, ...);
int DrawBubbleSort(HDC hdc,int xPos,int yPos,BUBBLE_DATA bubbleData)
{
    int iHeight = 50;
    int iCounter1 = 0;
    int xPosDrawArrBox = 0;
    RECT rc;
	HPEN hPen;
	HPEN hOldPen;
	HBRUSH hBrush;
	int iFlag = 0;

    xPosDrawArrBox = xPos + 100;
	iHeight = 50;
    if(0 != bubbleData.passNumber)
    {
        FormatedTextOut(hdc,xPos + 20,yPos,"\n\nPASS %d:\n",bubbleData.passNumber);
		return (30);
    }
    else 
    {
        xPos += 100;
		hPen = CreatePen(BS_SOLID, 2, RGB(0, 0, 0));
		hOldPen = (HPEN)SelectObject(hdc, hPen);
		
        for(iCounter1 = 0; iCounter1 < N ; iCounter1++)
        {
            rc.left = xPosDrawArrBox;
            rc.top = yPos;
            rc.right = rc.left + 50;
            rc.bottom = rc.top + 40;
            
			if (bubbleData.swapIndex1 == iCounter1 || bubbleData.swapIndex2 == iCounter1)
			{
				if (bubbleData.swapFlag)
				{
					hPen = CreatePen(BS_SOLID, 2, RGB(255, 0, 0));
					hOldPen = (HPEN)SelectObject(hdc, hPen);
					hBrush = CreateSolidBrush(RGB(180, 180, 180));
					iFlag = 1;
				}
				else
				{
					hPen = CreatePen(BS_SOLID, 2, RGB(0, 255, 0));
					hOldPen = (HPEN)SelectObject(hdc, hPen);
					hBrush = CreateSolidBrush(RGB(255, 255, 255));
					iFlag = 2;
				}
			}
			else
			{
				hPen = CreatePen(BS_SOLID, 2, RGB(0, 0, 0));
				hOldPen = (HPEN)SelectObject(hdc, hPen);
				hBrush = CreateSolidBrush(RGB(255, 255, 255));
			}
			SelectObject(hdc, hBrush);
			SelectObject(hdc, hPen);
			Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
			FormatedTextOut(hdc, xPosDrawArrBox + 5, yPos + 5, " %d", bubbleData.arrayObj.pArr[iCounter1]);
            xPosDrawArrBox += 60;
        }
		SelectObject(hdc, hOldPen);
    }

	if (iFlag == 1)
	{
		FormatedTextOut(hdc,xPos + 350,yPos+5,"%d > %d ,SWAP", bubbleData.arrayObj.pArr[bubbleData.swapIndex1], bubbleData.arrayObj.pArr[bubbleData.swapIndex2]);
	}
	else
	{
		FormatedTextOut(hdc, xPos + 350, yPos+5, "%d < %d ,OK", bubbleData.arrayObj.pArr[bubbleData.swapIndex1], bubbleData.arrayObj.pArr[bubbleData.swapIndex2]);
	}
    return (iHeight);
}
