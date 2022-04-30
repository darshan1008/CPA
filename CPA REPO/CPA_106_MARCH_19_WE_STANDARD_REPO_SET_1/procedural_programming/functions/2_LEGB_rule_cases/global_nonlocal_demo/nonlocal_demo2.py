#! /usr/bin/python3

X = "Hello" 
def f1 (): 
    X = 100 
    def f2 (): 
        X = 200 
        def f3 (): 
            print ("f3:X:", X) 
            X = 500
            nonlocal X 
        print ("f2:X:", X) 
        f3 () 
        print ("f2:X:", X) 
    f2 () 
f1 () 
