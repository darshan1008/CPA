#! /usr/bin/python3 

def f1 (n):
    def f2 (X): 
        return (X ** n) 
    return f2 

sqrt = f1 (2) 
print (sqrt (10), sqrt (100), sqrt (20))
cube = f1 (3) 
print (cube (10), cube (100), cube (20))
fourth = f1 (4) 
print (fourth (10), fourth (100), fourth (20))

n = int (input ("Enter power:") )
nth_power = f1 (n) 
print (nth_power (10), nth_power (100), nth_power (20)) 


