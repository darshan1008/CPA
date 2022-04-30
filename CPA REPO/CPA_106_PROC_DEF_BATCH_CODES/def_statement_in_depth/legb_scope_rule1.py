X = 10
print("g:X:", X, "hex(id(X)):", hex(id(X)))
def f1():
    X = 3.14
    print("f1:X:", X, "hex(id(X)):", hex(id(X)))

    def f2():
        X = "Hello"
        print("f2:X:", X, "hex(id(X)):", hex(id(X)))

        def f3():
            X = (10, 20, 30 ,40)
            print("f3:X:", X, "hex(id(X)):", hex(id(X)))

            def f4():
                print("f4:X:",X, "hex(id(X):", hex(id(X)))

                def f5():
                    X = 900000

                f5()

            f4()

        f3()

    f2()
f1()
