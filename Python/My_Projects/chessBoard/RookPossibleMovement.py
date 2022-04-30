def RookMove(CurrentPosRow,CurrentPosCol):
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
RookMove(0,0);
