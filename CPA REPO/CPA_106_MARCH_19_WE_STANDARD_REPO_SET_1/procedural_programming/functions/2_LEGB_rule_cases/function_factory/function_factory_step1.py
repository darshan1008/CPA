#! /usr/bin/python3 

def f1():
    X = 100 
    def f2 (): 
        X = 200 
        print ("f2:X:", X, "hex (id (X)):", hex (id (X)))
    f2 () 
    print ("f1:X:", X, "hex (id (X)):", hex (id (X))) 
f1 () 
