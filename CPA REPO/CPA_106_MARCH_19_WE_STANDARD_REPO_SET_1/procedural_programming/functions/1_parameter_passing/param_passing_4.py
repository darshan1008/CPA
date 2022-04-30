#! /usr/local/bin/python3 

def f1 (**my_dict):
    print ("my_dict:", my_dict, "type (my_dict):", type (my_dict))
    for key in my_dict:
        print ("key:", key, "value:", my_dict[key])

f1 (a=20, b=30, c="hello")
f1 (**{'a':20, 'b':30, 'c':'hello'})
#f1 ({'a':20, 'b':30, 'c':'Hello'})
