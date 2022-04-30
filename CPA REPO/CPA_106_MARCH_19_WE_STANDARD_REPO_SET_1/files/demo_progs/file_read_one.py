#! /usr/bin/python3

f = open ("basic_file_ops.py") 

for line in f:
    line.rstrip ("\n")
    print ("line:", line) 

