def f(): 
    print("I am in function f") 
    def g(): 
        print("I am in function g") 
    g() 
    print("About to return from function f") 
f() 
