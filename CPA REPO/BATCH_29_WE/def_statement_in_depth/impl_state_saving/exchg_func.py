def f1():
    print("I AM F1")

print("type(f1):", type(f1), "hex(id(f1)):", hex(id(f1)))

def ReceiveFunction(X):
    print("type(X):", type(X), "hex(id(X)):", hex(id(X)))
    X()

ReceiveFunction(f1)


def CreateAndReturn():
    def test():
        print("I AM A TEST FUNCTION")
    print("CreateAndReturn:hex(id(test)):", hex(id(test)))
    return (test)

X1 = CreateAndReturn()
print("Calling X1")
X1()
print("hex(id(X1)):", hex(id(X1)))

X2 = CreateAndReturn()
print("Calling X2:")
X2()
print("hex(id(X2)):", hex(id(X2)))

X3 = CreateAndReturn()
print("Calling X3:")
X3()
print("hex(id(X3)):", hex(id(X3)))    
