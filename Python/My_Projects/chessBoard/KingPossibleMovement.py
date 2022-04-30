def KingMove(R,C):

    if(R<7):
        print(R+1,C);

    if(R>0):
        print(R-1,C);

    if(C<7):
        print(R,C+1);

    if(C>0):
        print(R,C-1);

    if(R>0 and C>0):
        print(R-1,C-1);

    if(R < 7 and C < 7 ):
        print(R+1,C+1);

    if(R>0 and C<7):
        print(R-1,C+1);

    if(R<7 and C>0):
        print(R+1,C-1);

print("R C");
KingMove(5,7);
