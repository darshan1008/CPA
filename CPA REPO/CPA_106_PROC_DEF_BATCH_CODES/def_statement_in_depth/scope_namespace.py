


n = 10
print("g:id(n):", id(n))

def f1():
    n = 3.14
    print("f1:id(n):", id(n))
    def f2():
        n = "Hello" 
        print("f2:id(n):", id(n))
    f2()
f1()

    
