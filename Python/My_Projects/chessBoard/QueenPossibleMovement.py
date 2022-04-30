def QueenMove(CurrentPosRow,CurrentPosCol):

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



    temp = 0;

    if(CurrentPosCol >=0):
        temp = CurrentPosCol+1;
        while(temp < 8):
            print(CurrentPosRow,temp);
            temp += 1;

    if(CurrentPosCol < 8):
        temp = CurrentPosCol-1;
        while(temp < 7 and temp >=0 ):
            print(CurrentPosRow,temp);
            temp -= 1;

    if(CurrentPosRow >= 0):
        temp = CurrentPosRow + 1;
        while(temp < 8):
            print(temp,CurrentPosCol);
            temp += 1;

    if(CurrentPosRow < 8):
        temp = CurrentPosRow - 1;
        while(temp < 7 and temp >=0 ):
            print(temp,CurrentPosCol);
            temp -= 1 ;


print("R C");
QueenMove(4,3);
