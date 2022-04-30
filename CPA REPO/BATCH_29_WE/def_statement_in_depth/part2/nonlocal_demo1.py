n = 10000
def f1():
    n = 500
    print("1:f1:n:", n)
    def f2():
        p = 200
        def f3():
            nonlocal n
            n = 1000
            print("f3:n:", n)
        f3()
    f2()
    print("2:f1:n:", n) 
f1() 


def f1():
    k = 0
    def g1():
        nonlocal k 
        k = k + 1
    def g2():
        nonlocal k

        k = k + 1

        k = k + 1

    def g3():
        nonlocal k
        k = k + 1
    g1()
    g2()
    g3()
    print("files opened by inner functions:", k)
f1()

def f1():
    k = 10
    def f2():
        p = 200
        def f3():
            nonlocal k
            print("f3:k:", k) 
        f3()
    del k
    f2()
f1() 







    




     
