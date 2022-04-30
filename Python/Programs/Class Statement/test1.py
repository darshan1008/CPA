
class T1:
    a = 10
    b = 20
    c = a+b
    print(c)

    def f1():
        print("In f1,a is ",T1.a)
#T1.f1()
#print("At global : ",T1.a)

print("type(T1)",type(T1))
print(T1.__dict__)


t1 = T1()
print("type(t1)",type(t1))
print(t1.__dict__)
