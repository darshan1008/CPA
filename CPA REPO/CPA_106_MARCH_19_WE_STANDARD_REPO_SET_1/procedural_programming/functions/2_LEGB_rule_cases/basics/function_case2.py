#! /usr/bin/python3 

# (1) Global X exists
# (2) X is assigned inside function
# (3) If global X statement is missing 
# inside function then attmpt to use X
# before local assignment of X generates 
# error
# Reason : In case of missing global X 
# statement, local assignment of X creates
# a local copy of X, which cannot be used 
# before assignment 
# Therefore, any use of X before local assign
# ment is an error. 

X = 99

def f1 (): 
    print (X) 
    X = 100 

f1 ()
