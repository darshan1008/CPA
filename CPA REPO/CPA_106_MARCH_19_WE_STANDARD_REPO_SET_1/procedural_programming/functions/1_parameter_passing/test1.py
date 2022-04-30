#! /usr/bin/python3 

def f1 (): 
    print ("in f1") 
    def f2 (): 
        print ("in f2")
    print ("hex (id (f2)):", hex (id (f2))) 
    print ("type (f2):", type (f2))
    print ("f1:I am going to return reference of object which is currently pointed to by f2") 
    return (f2) 

x = f1 ()
print ("hex (id (x)):", hex (id (x)))
print ("type (x):", type (x))
x () 
