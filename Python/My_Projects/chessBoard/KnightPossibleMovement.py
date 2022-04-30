

lBlack = [];
lWhite = [0,0,0,0,0,0,0,0];

iCounter= 0;

while(iCounter<8):
	iCounter += 1
	lBlack.append(lWhite)




def KnightMove(RowPos,ColPos):
	# print possible horse positions : by checking  up-down by-2 and left-right by-1 	
	if(RowPos >= 2):
		if(ColPos >= 0 and ColPos < 7):
			print (RowPos-2,"",ColPos+1);
		if(ColPos >2 and RowPos <=7 ):
			print (RowPos-2,"",ColPos-1);
	
	if(RowPos < 6):
		if(ColPos >= 0 and ColPos < 7):
			print (RowPos+2,"",ColPos+1);
		if(ColPos >2 and RowPos <=7 ):
			print (RowPos+2,"",ColPos-1);
			
			
	# print possible horse positions : by checking up-down by-1 and legt-right by-2
	if(ColPos > 1):
		if(RowPos >= 0 and RowPos < 7):
			print (RowPos+1,"",ColPos-2);
		if(RowPos <=7 and RowPos >0 ):
			print (RowPos-1,"",ColPos-2);
			
	if(ColPos < 6):
		if(RowPos >= 0 and RowPos < 7):
			print (RowPos+1,"",ColPos+2);
		if(RowPos <= 7 and RowPos > 0 ):
			print (RowPos-1,"",ColPos+2);



	



iKnightPosRow = 4;
iKnightPosCol = 0;
print("R : Row     C: Column\n");
print ("R "+" C");
KnightMove(iKnightPosRow,iKnightPosCol);

 
#print lBlack[0][6]




