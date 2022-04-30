print("START") 
def f1(): 
    print("In f1") 
    n = 500 
    print("n:", 500) 
    def f2(): 
        X = 3.14
        print("X:", 3.14) 
    L = [10, 20, 30, 40] 
    for x in L: 
        print(x)
    def f3(): 
        D = {"a":1, "b":2, "c": 3} 
        for k in D.keys():
            print(k, D[k]) 
        def f4(): 
            print("In f4") 
        T = (1, 2, 3)
        print("T:", T) 
        f4() 
    s1 = "Hello"
    s2 = "World" 
    f2()
    print(s1+s2) 
    f3() 
print("Is this an end?") 
f1() 

        
