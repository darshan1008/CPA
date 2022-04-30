#! /usr/bin/python3 

import random 

L = [] 
i = 0 
while i < 10:
    L.append (random.randint (0, 1000)) 
    i = i + 1

for j in range (1, len (L)):
    key = L[j] 
    i   = j - 1 
    while i > -1 and L[i] > key:
        L[i+1] = L[i] 
        i = i - 1
    L[i+1] = key 

for x in range (len (L)):
    print ("L[",x,"]:", L[x])




