#! /usr/bin/python3 

def f1 (): 
    print ("in f1")
    def f2 (): 
        print ("in f2") 
    print ("type (f2):", type (f2)) 
    print ("hex (id (f2)):", hex (id (f2)))

f1 () 
