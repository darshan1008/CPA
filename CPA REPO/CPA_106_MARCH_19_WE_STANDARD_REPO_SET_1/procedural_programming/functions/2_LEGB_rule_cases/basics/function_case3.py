#! /usr/bin/python3 

# (1) Global X exists 
# (2) Local scope is introduced by procedure f1 
# (3) If we write global X in f1, then any subsequent
# assignment of X in f1 (after global X) DOES NOT 
# RESULT INTO CREATION OF NEW X. INSTEAD GLOBAL X 
# is USED. 

X = 99 
print ("main:X", X) 

def f1 ():
    X = "Hello"
    del (X) 
    global X  
    print ("f1:X:", X) 

f1 ()
print ("main:X:", X)
