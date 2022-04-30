#! /usr/bin/python3 

import sys

def f1 ():
    def f2 ():
        X = 100
        print ("f2:X:", X, sep='')
    return (f2) 

def f3 ():
    def f4 (X):
        print ("f4:X:", X, sep='')
    return (f4)

def f5 ():
    n = 4
    def f6 (X):
        return (X ** n) 
    return (f6) 

def f7 (n):
    def f8 (X):
        return (X**n)
    return (f8) 

def main ():
    ref_f2 = f1 ()
    ref_f2 ()
    ref_f4 = f3 ()
    ref_f4 (100)
    ref_f4 (200)
    action = f5 ()
    print ("action(2):", action (2)) 
    print ("action(3):", action (3))
    my_square = f7 (2) 
    print ("my_square (2):", my_square (2))
    print ("my_square (3):", my_square (3))
    my_cube = f7 (3)
    print ("my_cube (2):", my_cube (2))
    print ("my_cube (9):", my_cube (9))
    sys.exit (0) 
    
main ()

