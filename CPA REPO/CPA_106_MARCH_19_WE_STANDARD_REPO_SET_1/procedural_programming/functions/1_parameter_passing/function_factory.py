#! /usr/bin/python3 

def f1 (n): 
    def f2 (x):
        return (x ** n) 
    return f2 

ref_f2 = f1 (4) 
print (ref_f2 (2))
print (ref_f2 (3))
print (ref_f2 (4)) 

print ("Which power you want:", end='') 
k = int (input ()) 

kth_power = f1 (k) 
print ("Enter  the number of which to take power:", end='') 
x = int (input ()) 

print (kth_power (x)) 

my_sqrt = f1 (0.5) 
print (my_sqrt (4))

