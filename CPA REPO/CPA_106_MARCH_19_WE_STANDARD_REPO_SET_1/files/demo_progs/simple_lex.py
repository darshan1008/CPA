#! /usr/bin/python3

D = dict.fromkeys (["char", "int", "float", "double", "void", "break"], "K")
ip_list = []
op_list = [] 
ip_f_name = "lex.c" 
op_f_name = "lex.out" 

f_handle = open (ip_f_name) 

for line in f_handle: 
    ip_list = line.split ("\n")
    ip_list = ip_list[0].split (" ") 
    print (ip_list) 
    for word in ip_list:
        if (word in D.keys ()) == True:
            op_list.append (D[word])
        else:
            op_list.append ("V")
    op_list.append ("\n")
f_handle.close ()

f_handle = open (op_f_name, "w")
for c in op_list: 
    f_handle.write (c + " ")
f_handle.close () 
