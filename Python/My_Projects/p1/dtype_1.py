import sys

print(len(sys.argv))

if len(sys.argv) == 2:
    fd = open(sys.argv[1],'r')
else:
    print("Enter file name as command line argument")
    sys.exit(-1)


data = fd.read()

print(data)

if data[0] == 'i':
    if data[1] == 'n':
        if data[2] == 't':
            data = data.replace('int',"")

print("data" , data)

c = compile(data,mode="single",filename="fakename")
exec(c)

print("is",i_no)

fd.close()

sys.exit(0)
    


