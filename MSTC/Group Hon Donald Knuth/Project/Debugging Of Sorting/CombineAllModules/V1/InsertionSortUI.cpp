#include"InsertionSortHeader.h"
CHAR* label[4] = {TEXT("Given Array"),TEXT("i"),TEXT("j"),TEXT("Key")};
void DrawInsertionSort(HDC hdc, int xPos, int yPos, const INSERTIONSORTDATA insertionSortDataObj)
{
    int i,j;
    int p = 230;
    int q = 280;
    //key,i,j values printing
    for(i = 0; i<3;i++)
    {
        if(i == 0)
        {
            ellipseMagentaColor(hdc, insertionSortDataObj);
            Ellipse(hdc, xPos + p+400, yPos + 120-20, xPos + q+400, yPos + 150-20 );
            textColor(hdc,insertionSortDataObj);
            FormatedTextOut(hdc, xPos + p + 15+400, yPos + 120-20, TEXT("%d"), insertionSortDataObj.arrayObj.i); 
        }
        if(i == 1)
        {
            ellipseYelloColor(hdc, insertionSortDataObj);
            Ellipse(hdc, xPos + p+400, yPos + 120-20, xPos + q+400, yPos + 150-20 );
            textColor(hdc,insertionSortDataObj);
            FormatedTextOut(hdc, xPos + p + 15+400, yPos + 120-20, TEXT("%d"), insertionSortDataObj.arrayObj.j); 
        }      
        if(i == 2)
        {
            ellipseRedColor(hdc, insertionSortDataObj);
            Ellipse(hdc, xPos + p+10+400, yPos + 120-20, xPos + q+10+400, yPos + 150-20 );
            textColor(hdc,insertionSortDataObj);
            FormatedTextOut(hdc, xPos + p + 15+400, yPos + 120-20, TEXT("%d"), insertionSortDataObj.arrayObj.key); 
        }
        p = p + 80;
        q = q + 80;
    }

    //Exchange/ notexchange 
    p = 230;
    q = 280;
    if(insertionSortDataObj.exchangeFlag == ON)
    {
        for(i = 0; i<N;i++)            
        {
            if(insertionSortDataObj.exchangeIndex1 == i || insertionSortDataObj.exchangeIndex2 == i)
            {
                exchangeColor(hdc,insertionSortDataObj);
            }
            else 
            {
                notexchangeColor(hdc,insertionSortDataObj);
            }
            //rectangle + color painting 
            Rectangle(hdc, xPos + p, yPos + 50, xPos + q, yPos + 80);
            
            //values painting
            textColor(hdc, insertionSortDataObj);
            FormatedTextOut(hdc,xPos + p + 10, yPos+50, TEXT("%d"),(insertionSortDataObj.arrayObj.pArr[i]));
            p = p + 80;
            q = q + 80;
        }
    }
    //sorted /unsorted
    p = 230;
    q = 280;
    if(insertionSortDataObj.sortedUnsortedFlag == ON)
    {
        for(i = 0; i<N;i++)
        {
            if(insertionSortDataObj.seperatorIndex >= i)
            {
                sortedColor(hdc,insertionSortDataObj);
            }
            else
            {
                unsortedColor(hdc,insertionSortDataObj);
            }

            Rectangle(hdc, xPos + p, yPos + 100 , xPos + q, yPos + 130);
            //values painting
            textColor(hdc, insertionSortDataObj);
            FormatedTextOut(hdc,xPos + p + 10, yPos+100, TEXT("%d"),(insertionSortDataObj.arrayObj.pArr[i]));
            p = p + 80;
            q = q + 80;
        }
    }
    p = 230;
    q = 280;
    if(insertionSortDataObj.sortedUnsortedFlag == OFF && insertionSortDataObj.exchangeFlag == OFF)
    {
        for(i = 0; i<N;i++)
        {
            Rectangle(hdc, xPos + p, yPos + 100 , xPos + q, yPos + 130);
            //values painting
            textColor(hdc, insertionSortDataObj);
            FormatedTextOut(hdc,xPos + p + 10, yPos+100, TEXT("%d"),(insertionSortDataObj.arrayObj.pArr[i]));
            p = p + 80;
            q = q + 80;
        }
    }


}

void header(HDC hdc, int cxClient,int cyClient,INSERTIONSORTDATA insertionData)
{
    CHAR* noteArray[] = {TEXT("Note - "),TEXT("- Sorted Array"),TEXT("- UnSorted Array"),TEXT("- Exchange Array")};
    
    int i;                              /*loop variable */
    int p = 150,q = 200;                /*given array rectangle control variable*/
    int x = 10;                         /*note ,sortedArray, unSortedArray text control variable*/
    int k = 0;                          /*formatted value control variable*/
    int m = 180;                        /*note rectangle control variable*/
    int n = 220;   
    int xPos = cxClient/4*1;
    int yPos = 0;
    
    // Square around window
    Rectangle(hdc,0,0,cxClient,cyClient);

    //separation line 30 - 70 for window
    rectangleBordercolorAndFillColorMagenta(hdc, insertionData);
    MoveToEx(hdc,xPos,yPos,NULL);
    LineTo(hdc,xPos,cyClient);

    //Note section start here
    //line for Note
    MoveToEx(hdc,xPos,yPos + 40,NULL);
    LineTo(hdc,cxClient,yPos + 40);

    //displaying Note Sorted Array and UnSorted Array
    for(i = 0; i<4; i++)
    {
        noteColor(hdc,insertionData);
        TextOut(hdc,xPos + x,yPos + 5,noteArray[i],strlen(noteArray[i]));
        x = x + 220;
        if( i == 3)
        {
            x = x + 300;
        }
    }

    //Painting rectangle for colors of sorted,unsorted,exchange array
    for(i = 0; i<3;i++)
    {   
        if(i == 0)
        {
            sortedColor(hdc, insertionData);
        }
        if(i == 1)
        {
            unsortedColor(hdc, insertionData);
            m = m + 220;
            n = n + 220;
        }
        if(i == 2)
        {
            exchangeColor(hdc, insertionData);
            m = m + 225;
            n = n + 225;
        }
        Rectangle(hdc, xPos + m, yPos + 5,xPos + n, yPos + 35);   
    }

    //Note Section end here
}

void sortedColor(HDC hdc, INSERTIONSORTDATA insertionDataObj)
{
    insertionDataObj.hPen = CreatePen(PS_SOLID,1,RGB(255,0,255));
    SelectObject(hdc,insertionDataObj.hPen);
    insertionDataObj.hBrush = CreateSolidBrush(RGB(0,255,0));
    SelectObject(hdc,insertionDataObj.hBrush);  
    
}
void unsortedColor(HDC hdc, INSERTIONSORTDATA insertionDataObj)
{
    insertionDataObj.hPen = CreatePen(PS_SOLID,1,RGB(255,0,255));
    SelectObject(hdc,insertionDataObj.hPen);
    insertionDataObj.hBrush = CreateSolidBrush(RGB(0,255,255));
    SelectObject(hdc,insertionDataObj.hBrush); 
}
void exchangeColor(HDC hdc, INSERTIONSORTDATA insertionDataObj)
{
    insertionDataObj.hPen = CreatePen(PS_SOLID,1,RGB(255,0,255));
    SelectObject(hdc,insertionDataObj.hPen);
    insertionDataObj.hBrush = CreateSolidBrush(RGB(0,0,255));
    SelectObject(hdc,insertionDataObj.hBrush);
}
void notexchangeColor(HDC hdc,INSERTIONSORTDATA insertionDataObj)
{
    insertionDataObj.hPen = CreatePen(PS_SOLID,1,RGB(255,0,255));
    SelectObject(hdc,insertionDataObj.hPen);
    insertionDataObj.hBrush = CreateSolidBrush(RGB(255,255,255));
    SelectObject(hdc,insertionDataObj.hBrush);   
}
void rectangleBordercolorAndFillColorMagenta(HDC hdc,INSERTIONSORTDATA insertionDataObj)
{
    insertionDataObj. hPen = CreatePen(PS_SOLID,1,RGB(255,0,255));
    SelectObject(hdc,insertionDataObj.hPen);
    insertionDataObj.hBrush = CreateSolidBrush(RGB(255,255,255));
    SelectObject(hdc,insertionDataObj.hBrush);
}
void rectangleBordercolorAndFillColorWhite(HDC hdc,INSERTIONSORTDATA insertionDataObj)
{
    insertionDataObj.hPen = CreatePen(PS_SOLID,1,RGB(255,255,255));
    SelectObject(hdc,insertionDataObj.hPen);
    insertionDataObj.hBrush = CreateSolidBrush(RGB(255,255,255));
    SelectObject(hdc,insertionDataObj.hBrush);  
}
void ellipseYelloColor(HDC hdc,INSERTIONSORTDATA insertionDataObj)
{
    insertionDataObj.hMyFont_1 = CreateFont(30,0,0,0,700,0,0,0,0,0,0,0,FF_DONTCARE,"Arial Bold");
    SelectObject(hdc,insertionDataObj.hMyFont_1);

    insertionDataObj.hBrush = CreateSolidBrush(RGB(255,255,0));
    SelectObject(hdc,insertionDataObj.hBrush);
    insertionDataObj.hPen = CreatePen(PS_SOLID,1,RGB(255,0,255));
    SelectObject(hdc,insertionDataObj. hPen);
}
void ellipseMagentaColor(HDC hdc,INSERTIONSORTDATA insertionDataObj)
{
        insertionDataObj.hMyFont_1 = CreateFont(30,0,0,0,700,0,0,0,0,0,0,0,FF_DONTCARE,"Arial Bold");
    SelectObject(hdc,insertionDataObj.hMyFont_1);

    insertionDataObj.hBrush = CreateSolidBrush(RGB(255,0,255));
    SelectObject(hdc,insertionDataObj.hBrush);
    insertionDataObj.hPen = CreatePen(PS_SOLID,1,RGB(255,0,255));
    SelectObject(hdc,insertionDataObj.hPen);
}
void ellipseRedColor(HDC hdc,INSERTIONSORTDATA insertionDataObj)
{
        insertionDataObj.hMyFont_1 = CreateFont(30,0,0,0,700,0,0,0,0,0,0,0,FF_DONTCARE,"Arial Bold");
    SelectObject(hdc,insertionDataObj.hMyFont_1);

    insertionDataObj.hBrush = CreateSolidBrush(RGB(0,128,128));
    SelectObject(hdc,insertionDataObj.hBrush);
    insertionDataObj.hPen = CreatePen(PS_SOLID,1,RGB(255,0,255));
    SelectObject(hdc,insertionDataObj.hPen);
}
void ellipseWhiteColor(HDC hdc,INSERTIONSORTDATA insertionDataObj)
{
        insertionDataObj.hMyFont_1 = CreateFont(30,0,0,0,700,0,0,0,0,0,0,0,FF_DONTCARE,"Arial Bold");
    SelectObject(hdc,insertionDataObj.hMyFont_1);

    insertionDataObj.hBrush = CreateSolidBrush(RGB(255,255,255));
    SelectObject(hdc,insertionDataObj.hBrush);
    insertionDataObj.hPen = CreatePen(PS_SOLID,1,RGB(255,255,255));
    SelectObject(hdc,insertionDataObj.hPen);
}
void textColor(HDC hdc,INSERTIONSORTDATA insertionDataObj)
{
    insertionDataObj.hMyFont_1 = CreateFont(30,0,0,0,700,0,0,0,0,0,0,0,FF_DONTCARE,"Arial Bold");
    SelectObject(hdc,insertionDataObj.hMyFont_1);
    SetBkColor(hdc,RGB(255,255,255));
    SetTextColor(hdc,RGB(255, 0, 85));
}
void labelColor(HDC hdc, INSERTIONSORTDATA insertionDataObj)
{
    insertionDataObj.hMyFont_1 = CreateFont(30,0,0,0,700,0,0,0,0,0,0,0,FF_DONTCARE,"Arial Bold");
    SelectObject(hdc,insertionDataObj. hMyFont_1);
    SetBkColor(hdc,RGB(255,255,255));
    SetTextColor(hdc,RGB(0,0,0));
}
void noteColor(HDC hdc, INSERTIONSORTDATA insertionDataObj)
{
    insertionDataObj.hMyFont_1 = CreateFont(25,0,0,0,700,0,0,0,0,0,0,0,FF_DONTCARE,"Arial Bold");
    SelectObject(hdc,insertionDataObj.hMyFont_1);
    SetBkColor(hdc,RGB(255,255,255));
    SetTextColor(hdc,RGB(200, 191, 231));
}
void counterF(HDC hdc, int xPos, int yPos)
{
    static int iterationCount = 1;
     
    FormatedTextOut(hdc, xPos, yPos + 120, TEXT("Iteration - %d"), iterationCount);
    iterationCount++;

}
int getHeightSquare()
{
    int height = 50;
    return height;
}
#define ARRAY_SIZE(X)   (sizeof(X)/sizeof(X[0]))
int FormatedTextOut(HDC hdc,int x,int y,TCHAR* pszFormat,...)
{
  	TCHAR szBuffer[1024] = {""};
	va_list pArgs;
	va_start(pArgs,pszFormat);

	_vsntprintf(szBuffer, ARRAY_SIZE(szBuffer) ,pszFormat,pArgs);
    TextOut(hdc,x,y,szBuffer,strlen(szBuffer));
    return(0);
}

void DrawInsertionTextOut(HDC hdc,int xPosOri,int yPos,INSERTIONSORTDATA insertObj)
{
    int iCounter2 = 0;
    HFONT hMyFont;
    int xPos = xPosOri;
    hMyFont = CreateFont(20,0,0,0,700,0,0,0,0,0,0,0,FF_DONTCARE,"Arial Bold");
	SelectObject(hdc,hMyFont);
    FormatedTextOut(hdc,xPos,yPos,"A:: ");
    xPos += 30;
    for(iCounter2 = 0; iCounter2 < N ; iCounter2++, xPos+=30)
    {
        FormatedTextOut(hdc,xPos,yPos," %d ",insertObj.arrayObj.pArr[iCounter2]);
    }
   
    xPos += 50;
    FormatedTextOut(hdc,xPos,yPos,"\ti : [%d]",insertObj.arrayObj.i);
    xPos += 70;
    FormatedTextOut(hdc,xPos,yPos,"\tj : [%d]",insertObj.arrayObj.j);
    xPos += 70;
    FormatedTextOut(hdc,xPos,yPos,"\tkey : [%d]",insertObj.arrayObj.key);
    xPos += 120;
    FormatedTextOut(hdc,xPos,yPos,"\texchangeFlag : [%d]",insertObj.exchangeFlag);
}