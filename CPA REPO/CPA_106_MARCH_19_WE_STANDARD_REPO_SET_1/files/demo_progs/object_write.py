#! /usr/bin/python 

L1 = [1, 2, 4] 
L2 = [6,7,8] 
f = open ("foo.txt", 'w') 
f.write ("%d,%d,%d\n" % (L1[0], L1[1], L1[2]))
f.write (str (L2[0]) + str (L2[1]) + str (L2[2]) + "\n")
f.close ()
