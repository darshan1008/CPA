#! /usr/bin/python3 

import sys

def main (argv):
    if (len(argv) != 3):
        print ("usage error:", argv[0], "lex_file_name lex_out_name")
        sys.exit (-1) 

    ip_file_name = argv[1]
    op_file_name = argv[2] 

    dict_keywords = dict.fromkeys (["void", "char", "int", "float", 
                                    "double", "break"], "K")
    ip_list = []
    op_list = [] 

    ip_f_handle = open (ip_file_name)
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
    
    op_f_handle = open (op_file_name, "w") 
    for c in op_list:
        op_f_handle.write (c)
    op_f_handle.close ()

    sys.exit (0) 

main (sys.argv) 
