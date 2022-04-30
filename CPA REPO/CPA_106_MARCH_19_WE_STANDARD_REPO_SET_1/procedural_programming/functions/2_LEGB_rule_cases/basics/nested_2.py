#! /usr/bin/python3 

def f1 ():
    X = 100
    def f2 ():
        print ("f2:X:", X) 
        X = 200 
    f2 ()
    print ("f1:X:", X) 
f1 ()
