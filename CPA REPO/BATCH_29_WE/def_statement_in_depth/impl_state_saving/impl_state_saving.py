def f1():
    n = 100
    def f2():
        print("f2:n:", n)
    return f2

X = f1()
X()
