#! /usr/bin/python3 

def f1 (): 
    X = 100 
    def f2 (): 
        print ("f2:X:", X) 
    return f2 

ref_f2 = f1 ()
ref_f2 () 
