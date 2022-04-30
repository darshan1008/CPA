# f2's access to global n is hidden by
# f1's local n 
n = 10
def f1():
    n = 3.14
    def f2():
        print("f2:n:", n)
    f2()
f1() 

# f2 can bypass local m of f1 and directly access
# global m by using 'global' statement as shown in
# code 
m = 10
def f1():
    m = 3.14
    def f2():
        global m
        print("f2:m:", m)
    f2()
f1()

# if inner function f2 declares a particular variable
# to be global by using 'global' statement and if it
# further uses that variable on LHS then instead of
# that variable getting created in f2, global version
# of that variable will get modified or reassigned

p = 10
def f1():
    p = 3.14
    def f2():
        global p
        p = "Hello"
    f2()
f1()
print("p:", p)

# from python 3.6 onwards if a particular function
# wishes to declare a particular variable global (or nonlocal)
# then such declaration MUST appear before any reference
# to that variable in a function otherwise it's a syntax error
# Till python 3.5 such code used to emit a warning by one used
# to get correct behaviour, (as if global or nonlocal appears
# before any use of that variable)


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










