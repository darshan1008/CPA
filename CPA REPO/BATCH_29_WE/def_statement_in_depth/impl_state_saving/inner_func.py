def f1():
    n = 10
    def f2():
        print("n:", n)
    f2()
f1()


def F():
    print("I am in F")
    def G():
        print("I am an inner function G")
    return (G)

X = F()
print("Call to global X")
X()
