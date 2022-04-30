def f1():
    n = 3.14
    def f2():
        global n
        n = 500
    f2()
f1()
print("global:n:", n) 

def f1():
    k = 100
    def f2():
        global k
        print("f2:k:", k)
        k = 500
    f2()
f1()
print("global:k:", k)   
