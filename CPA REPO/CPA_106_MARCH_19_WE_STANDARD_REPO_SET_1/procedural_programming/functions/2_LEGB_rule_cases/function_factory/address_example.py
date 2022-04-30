#! /usr/bin/python3 

def f1 (): 

    L = [10, 20, 30] 
    print ("f1:L:", L, "hex (id (L)):", hex (id (L))) 
    return (L) 

X = f1 () 
print ("g:X:", X, "hex (id (X)):", hex (id (X))) 

