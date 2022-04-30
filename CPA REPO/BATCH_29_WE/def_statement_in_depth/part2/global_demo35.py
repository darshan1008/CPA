print("HELLO")
k = 100
def f1():
    k = 3.14
    def f2():
        print("f2:k:", k)
        global k
        L = [10, 20, 30]
        for x in L:
            print("f2:x:", x)
    f2()
f1()
