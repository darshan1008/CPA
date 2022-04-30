#! /usr/bin/python3 

def f1 (): 
    n = 2 
    def f2 (X): 
        return (X ** n)
    return f2 

ref_f2 = f1 () 
print (ref_f2 (10))
print (ref_f2 (20)) 
