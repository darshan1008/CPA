# white means down

def WhitePawnMove(RowPos,ColPos):
    if(RowPos > 5):
        print(RowPos - 2,ColPos);
    if(RowPos > 0):
        print(RowPos - 1,ColPos);


def BlackPawnMove(RowPos,ColPos):
    if(RowPos < 2):
        print(RowPos + 2,ColPos);
    if(RowPos  < 7):
        print(RowPos + 1,ColPos);

print("White \nR C");
WhitePawnMove(1,1);
print("Black \nR C");
BlackPawnMove(3,2);
