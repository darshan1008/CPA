#! /usr/bin/python3

dict_keywords = dict.fromkeys (['void','char','int','float','double',
                                'break'],"K")

ip_f_name = "lex.c"
op_f_name = "lex.out"
ip_list = [] 
op_list = [] 

ip_f_handle = open (ip_f_name)
for line in ip_f_handle:
    ip_list = line.split ("\n")
    ip_list = ip_list[0].split (" ")
    for word in ip_list:
        if (word in dict_keywords.keys ()):
            op_list.append ("K ")
        else:
            op_list.append ("V ")
    op_list.append ("\n")
ip_f_handle.close ()

op_f_handle = open (op_f_name, "w")
for word in op_list:
    op_f_handle.write (word)
op_f_handle.close ()
