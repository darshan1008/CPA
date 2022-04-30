def f1():
    k = 500
    print("1:f1:k:", k)
    def f2():
        p = 200
        def f3():
            k = 700
            nonlocal k
            print("f3:k:", k)
        f3()
    f2()
    print("2:f1:k:", k)
f1()
