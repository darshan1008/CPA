#! /usr/bin/python3 

def f1 (): 
    def f2 (): 
        print ("3:In f2") 
    print ("1:type (f2):", type (f2), "hex (id (f2)):", hex (id (f2))) 
    return f2

X = f1 () 
print ("2:type (X):", type (X), "hex (id (X)):", hex (id (X))) 
X ()


