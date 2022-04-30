#! /usr/bin/python3 

e = '-' * 60

def f1 (v1, v2, v3): 
    print ("v1:", v1, "type (v1):", type (v1))
    print ("v2:", v2, "type (v2):", type (v2))
    print ("v3:", v3, "type (v3):", type (v3))

f1 (v3=10, v1="Hello", v2=[1,2,3])
print (e)
f1 (10, v3="World", v2={1,2,3}) 
print (e) 
# f1 (10, v2="hello", v1="foo", v3=100)
# Multiple values for certain argument 
# 1. Positional 2. Keyoword
# Only one can be specified at a time 

# f1 (10, v2=20, 30)
# f1 (10, v3=30, 20) 
# positional argument cannot be given after 
# keyword argument 

