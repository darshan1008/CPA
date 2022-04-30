def PowerFunctionFactory(n):
    if type(n) != int and type(n) != float:
        raise TypeError("Bad type for : power") 
    def ComputePower(x):
        if type(x) != int and type(x) != float:
            raise TypeError("Bad type for : base") 
        return (x**n)
    return (ComputePower)

def main():

    SquareFunc = PowerFunctionFactory(2)
    CubeFunc = PowerFunctionFactory(3)
    KthPower = PowerFunctionFactory(int(input("Enter K:")))

    iBase = int(input("Enter base:"))

    print("Square:", SquareFunc(iBase))
    print("Cube:", CubeFunc(iBase))
    print("KthPower:", KthPower(iBase))

main()

