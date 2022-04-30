#include"BubbleSortHeader.h"
#include<tchar.h>

#define ARRAY_SIZE(X)   (sizeof(X)/sizeof(X[0]))
int FormatedTextOut(HDC hdc,int x,int y,TCHAR* pszFormat,...);

int DrawBubbleSort(HDC hdc,int xPos,int yPos,BUBBLE_DATA bubbleData)
{
    int iHeight = 50;
    int iCounter1 = 0;
    int xPosDrawArrBox = 0;
    RECT rc;
   
    xPosDrawArrBox = xPos + 100;
    if(0 != bubbleData.passNumber)
    {
        //FormatedTextOut(hdc,xPos,yPos,"\n\nPASS %d:\n",bubbleData.passNumber);
    }
    else 
    {
        //FormatedTextOut(hdc,xPos,yPos,"\nARRAY :: ");
        xPos += 100;

        for(iCounter1 = 0; iCounter1 < N ; iCounter1++)
        {
            rc.left = xPosDrawArrBox;
            rc.top = yPos;
            rc.right = rc.left + 50;
            rc.bottom = rc.top + 40;
             Rectangle(hdc,rc.left,rc.top,rc.right,rc.bottom);
            FormatedTextOut(hdc,xPosDrawArrBox+5,yPos+5," %d",bubbleData.arrayObj.pArr[iCounter1]);
           
            xPosDrawArrBox += 60;
        }
        //printf("\t");
        xPos += 50;
        if(bubbleData.swapN1 && bubbleData.swapN2)
        {
            if(bubbleData.swapFlag)
            {
                //FormatedTextOut(hdc,xPos,yPos,"%d > %d ,SWAP",bubbleData.swapN1,bubbleData.swapN2);
            }
            else
            {
                //FormatedTextOut(hdc,xPos,yPos,"%d < %d ,OK",bubbleData.swapN1,bubbleData.swapN2);
            }
        }
    }

    return (iHeight);
}

int FormatedTextOut(HDC hdc,int x,int y,TCHAR* pszFormat,...)
{
  	TCHAR szBuffer[1024] = {""};
	va_list pArgs;
	va_start(pArgs,pszFormat);

	_vsntprintf(szBuffer, ARRAY_SIZE(szBuffer) ,pszFormat,pArgs);
    TextOut(hdc,x,y,szBuffer,strlen(szBuffer));
    return(0);
}