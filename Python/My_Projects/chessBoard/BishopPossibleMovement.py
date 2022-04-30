
def BishopMove(CurrentPosRow,CurrentPosCol):

    tempRow = CurrentPosRow + 1 ;
    tempCol = CurrentPosCol + 1 ;

    while(tempRow <= 7 and tempCol <= 7):
        print(tempRow,tempCol);
        tempRow += 1 ;                  #R++;
        tempCol += 1 ;                  #C++;

    tempRow = CurrentPosRow - 1 ;
    tempCol = CurrentPosCol - 1 ;

    while(tempRow >= 0 and tempCol >= 0):
        print(tempRow,tempCol);
        tempRow -= 1 ;                  #R--;
        tempCol -= 1 ;                  #C--;

    tempRow = CurrentPosRow + 1 ;
    tempCol = CurrentPosCol - 1 ;
    while(tempRow <= 7 and tempCol>=0):
        print(tempRow,tempCol);
        tempRow += 1;               #R++
        tempCol -= 1;               #C--

    tempRow = CurrentPosRow - 1 ;
    tempCol = CurrentPosCol + 1 ;
    while(tempRow >= 0 and tempCol<= 7):
        print(tempRow,tempCol);
        tempRow -= 1;               #R--
        tempCol += 1;               #C++





print("R C");
BishopMove(4,3);
