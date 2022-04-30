def f1():
    X = 100
    def f2():
        print("f2:X:", X)
    del X
    f2() 
f1()
