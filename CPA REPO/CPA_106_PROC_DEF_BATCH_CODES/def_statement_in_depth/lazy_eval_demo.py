def f1():
    X = 500 
    def f2():
        print("f2:X:", X)
    del X 
    #X = 500
    f2() 
f1()
