#! /usr/bin/python3 

X = "Hello" 
print ("g:X:", X, "hex (id (X)):", hex (id (X))) 
def f1 (): 
    X = 100 
    def f2 (): 
        #UnboundLocalError 
        #global X 
        print ("f2:X:", X, "hex (id (X)):", hex (id (X)))
        #global X
        X = 300
        print ("f2:X:", X, "hex (id (X)):", hex (id (X)))
    f2 () 
f1 () 
print ("g:X:", X, "hex (id (X)):", hex ( id (X)))
