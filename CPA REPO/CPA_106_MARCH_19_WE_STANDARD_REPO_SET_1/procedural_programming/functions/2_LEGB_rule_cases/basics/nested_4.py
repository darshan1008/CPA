#! /usr/bin/python3 

def f1 ():
    X = 100
    def f2 ():
        X = "Hello"
        nonlocal X 
        print ("f2:X:", X) 
    f2 ()
    print ("f1:X:", X) 
f1 ()
