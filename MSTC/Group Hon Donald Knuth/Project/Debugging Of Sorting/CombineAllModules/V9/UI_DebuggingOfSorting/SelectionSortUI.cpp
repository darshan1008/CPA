#include"SelectionSortHeader.h"

int FormatedTextOut(HDC hdc, int x, int y, TCHAR* pszFormat, ...);

int DrawSelectionSort(HDC hdc, int xPos, int yPos, SELECTION_DATA bubbleData)
{
	size_t iCounter = 0;
	int iCounter2 = 0;
	for (iCounter = 0; iCounter < g_selectionVector->iVectorSize; iCounter++)
	{
		FormatedTextOut(hdc,xPos,yPos,"A:: ");
		for (iCounter2 = 0; iCounter2 < N; iCounter2++)
		{
			FormatedTextOut(hdc, xPos+30, yPos, " %d", (g_selectionVector->pSelectionSort[iCounter]).arrayObj.pArr[iCounter2]);
		}

		//FormatedTextOut(hdc, xPos, yPos,"i:%d", g_selectionVector->pSelectionSort[iCounter].arrayObj.i);
		//printf("\tj:%d",pVector->pSelectionSort[iCounter].arrayObj.j);

		FormatedTextOut(hdc, xPos+30, yPos,"\tsmallele:%d",(g_selectionVector->pSelectionSort[iCounter]).arrayObj.pArr[g_selectionVector->pSelectionSort[iCounter].smallEleIndex]);
		FormatedTextOut(hdc, xPos+100, yPos,"smallele: %d", g_selectionVector->pSelectionSort[iCounter].smallEleIndex);
		FormatedTextOut(hdc, xPos+100, yPos,"swap: %d", g_selectionVector->pSelectionSort[iCounter].swapIndex);
		FormatedTextOut(hdc, xPos+100, yPos,"swapFlag: %d", g_selectionVector->pSelectionSort[iCounter].swapFlag);
	}
	return 0;
}