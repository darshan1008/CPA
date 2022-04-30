#! /usr/bin/python3 

X = "Hello" 
print ("g:X:", X, "hex (id (X)):", hex (id (X))) 
def f1 (): 
    X = 100 
    def f2 (): 
        global X
        print ("f2:X:", X, "hex (id (X)):", hex (id (X)))
        X = 300
        print ("f2:X:", X, "hex (id (X)):", hex (id (X)))
    f2 ()
    print ("f1:X:", X, "hex (id (X)):", hex (id (X)))
f1 () 
print ("g:X:", X, "hex (id (X)):", hex ( id (X)))
