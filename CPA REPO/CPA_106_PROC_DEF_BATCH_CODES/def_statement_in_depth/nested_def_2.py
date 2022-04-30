def f1(): 
    X = [1,2,3,4]
    print("HERE") 
    for x in X: 
        print(x) 
    def f2(): 
        print("function2") 
        def f3(): 
            b = True
            print(b) 
        print("function2 end") 
    f2() 
f1() 
print("END") 
