#! /usr/bin/python3 

print ("Enter variable name:", end='')
var_name = input ()

S, V, I = 0, 1, 2
state = S

for i in range (len (var_name)):
    if state == S:
        if (var_name[i].isalpha () == True) or (var_name[i] == "_"):
            state = V
        else:
            state = I
        continue
    elif state == V: 
        if (var_name[i].isalnum () == True) or (var_name[i] == "_"):
            state = V
        else:
            state = I
        continue
    elif state == I:
        continue    

if state == V:
    print (var_name, "is a valid variable name") 
elif state == I:
    print (var_name, "is an invalid variable name") 
else:
    print ("Error in state machine") 
