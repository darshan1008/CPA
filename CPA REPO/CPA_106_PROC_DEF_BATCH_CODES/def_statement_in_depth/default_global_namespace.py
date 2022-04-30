def print_global_sym_tab():
    D = globals()
    for k in D.keys():
        if k.endswith("__") and k[:2] == "__":
            continue
        print(k) 
    print("-" * 65)
print_global_sym_tab()
n = 100
print_global_sym_tab()
f = 3.14
print_global_sym_tab()


def f():
    print("1:locals():", locals())
    n = 1000
    print("locals():", locals())
    f = 3.14
    print("locals():", locals())
    L = [10, 30, 40]
    print("locals():", locals())
    def g():
        pass
    print("locals():", locals())
    g = 500
    print("locals():", locals())


f()
