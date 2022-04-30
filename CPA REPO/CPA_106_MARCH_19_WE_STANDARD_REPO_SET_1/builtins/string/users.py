#! /usr/bin/python3

f = open ("/etc/passwd", "r") 

for line in f:
    print ((line.split(":"))[0]) 

s = "Hello" 
print (s[100])
