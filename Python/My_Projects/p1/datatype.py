#intino = 10

import sys
import os

def main(argc,argv):
    if type(argc)!= int:
        raise InvalidTypeError("BAD TYPE ERROR")
    if type(argv) != list:
        raise InvalidTypeError("BAD TYPE ERROR")


    print(argv)
    fd = open(argv[1])
    data = fd.read()

    print(data)

    if data[0] == 'i':
        if data[1] == 'n':
           if data[2] == 't':
               data = data.replace('int',"")

    print("data" , data)
    
    data="i=10"
    c = compile(data,mode="single",filename="fakename")
    exec(c)
    print(i)

    

main(len(sys.argv),sys.argv)


s="n=10"
c = compile(s,mode="single",filename="fakename")
exec(c)
print(n)
