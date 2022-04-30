#! /usr/local/bin/python3 

import sys

def f1 (n1, n2, *n3, n5=10, n6=[10,20,30], **n4):
    print ("n1:", n1)
    print ("n2:", n2)
    print ("n3:", n3)
    print ("n4:", n4)
    print ("n5:", n5)
    print ("n6:", n6)

def f2 (n1, n2, *n3, v1, v2, **n4):
    print ("n1:", n1) 
    print ("n2:", n2)
    print ("n3:", n3) 
    print ("n4:", n4) 
    print ("v1:", v1)
    print ("v2:", v2)


def main ():
    #f1 (10, 20, 30, 40, 50, a=10, b=20, c=[1,2,3], d="Hello") 
    #f2 (10, 20, *(30, 40, 50), **{'a':10, 'b':20, 'c':[1,2,3], 'd':'hello'})
    f2 (10, 20, 30, 40, 50, v1=10000, v2=20000, a=10, b=20, c=[1,2,3], d="Hello")
    sys.exit (0)

main ()
