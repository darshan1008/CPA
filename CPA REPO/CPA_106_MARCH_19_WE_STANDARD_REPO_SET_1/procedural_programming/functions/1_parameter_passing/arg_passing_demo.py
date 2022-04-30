#! /usr/bin/python3 

import sys

num1   = 10 
f_num1 = 3.14
str1   = "Hello" 
lst1   = [1,2,3]

def main (argv): 
    test_function (num1, f_num1, str1, lst1)
    print ("main:num1:", num1, sep='')
    print ("main:f_num1:", f_num1, sep='')
    print ("main:str1:", str1, sep='') 
    print ("main:lst1:", lst1, sep='')
    sys.exit (0) 

def test_function (v1, v2, v3, v4): 
    if v1 is num1:
        print ("1:v1:Yes") 
    if v2 is f_num1:
        print ("1:v2:Yes") 
    if v3 is str1:
        print ("1:v3:Yes")
    if v4 is lst1:
        print ("1:v4:Yes") 

    v1 = 25
    if v1 is num1:
        print ("2:v1:Yes")
    else:
        print ("2:v1:No") 

    v2 = 45.65
    if v2 is f_num1:
        print ("2:v2:Yes") 
    else:
        print ("2:v2:No") 

    v3 = v3[0:3] 
    if v3 is str1:
        print ("2:v3:Yes")
    else:
        print ("2:v3:No") 

    v4.append (100) 
    if v4 is lst1:
        print ("2:v4:Yes")
    else:
        print ("2:v4:No") 

main (sys.argv) 
