#! /usr/bin/python3 

def f1 ():
    n = 2
    def f2 (x):
        return x ** n 
    return f2

f1 ()  
