#! /usr/bin/python3 

D = dict.fromkeys (["void", "char", "int", "float", "double", "break"], "K")
L3 = [] 
f = open ("lex.c") 
for x in f:
    print (x)
    L = x.split ("\n") 
    L1 = L[0].split (" ")
    print (L1) 
    for y in L1:
        if y in D.keys ():
            L3.append ("K ")
        else:
            L3.append ("V ") 
    L3.append ("\n")
print (L3)

f = open ("lex.out", "w") 
for x in L3:
    f.write (x)
