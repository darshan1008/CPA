#! /usr/local/bin/python3 

# Fixed number of positional arguments

end_l = '-' * 60

def f1 (v1, v2, v3):
    print ("v1:", v1, "type (v1):", type (v1))
    print ("v2:", v2, "type (v2):", type (v2))
    print ("v3:", v3, "type (v3):", type (v3))
    
f1 (10, 20, 30)
print (end_l)
f1 (10, True, 3.14)
print (end_l) 
f1 ("Hello", "Python", "World") 
print (end_l)
f1 ([1,2,3], {4,5,6}, (10, 20, 30))
print (end_l) 
f1 ({1:"Hello", 2:"World"}, "Hello", [1,2,(4,5,6)])
print (end_l) 

#f1 (10, 20) #TypeError:Missing positional argument with name
#f1 (10, 20, 30, 40) # TypeError:Expected n but given > n




