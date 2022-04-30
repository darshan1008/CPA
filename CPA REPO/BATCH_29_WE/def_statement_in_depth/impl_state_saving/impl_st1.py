L = [10, 20, 30, 40]
print("global:L:", L, "hex(id(L)):", hex(id(L)))
def f(X):
    print("f:X:", X, "hex(id(X)):", hex(id(X)))
f(L)


def g():
    L = []
    return L

X1 = g()
print("X1:", X1) 
X2 = g()
print("X2:", X2) 
X3 = g()
print("X3:", X3)


"""
def create_stack():
    L = []
    return L

def create_stack():
    return list() 

def push(stack, element):
    stack.append(element)

def pop(stack):
    if len(stack) == 0:
        raise ValueError("cannot pop from empty stack")
    return L.pop()

def top(stack):
    if len(stack) == 0:
        raise ValueError("Cannot examine top of empty stack")
    return stack[-1]
"""










    


    









