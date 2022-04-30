#! /usr/local/bin/python3 

# Using variable number of argument using *operator

e = '-' * 60

def f1 (*v1):
    print ("v1:", v1, "type (v1):", type (v1))
    print (e) 

f1 (10)
f1 (10, 20, 30)
f1 (10, True, 3.14)
f1 ([1,2,3], {4,5,6}, (7,8,9), {1:"Hello", 2:(2,3,4)})
f1 ("Hello", "Python", "World") 
f1 (True, 10, 3.14, "Hello", [1,2,3], {1:"Hello"}, (1,2,3), 
    {2,3,4,5,6})

def f2 (v1, v2, *v5, v3, v4):
    print ("v1:", v1, "type (v1):", type (v1)) 
    print ("v2:", v2, "type (v2):", type (v2))
    print ("v3:", v3, "type (v3):", type (v3)) 
    print ("v4:", v4, "type (v4):", type (v4)) 
    print ("v5:", v5, "type (v5):", type (v5)) 
    print (e) 

#f2 (10, 20, 30, 40, v4=50, v3=60)
#f2 ("Hello", "Python", 10, 20, 30, 40, 50, v3="foo", v4="World") 
#f2 (10, 20, 30, 40) 
#f2 (10, 20, *([1,2,3], (1,2,3), {1,2,3}), v4=10000, v3=200000)
#f2 (10, 20, 30, 40, *(True,False, [1,2,3], {3,4,5}))

