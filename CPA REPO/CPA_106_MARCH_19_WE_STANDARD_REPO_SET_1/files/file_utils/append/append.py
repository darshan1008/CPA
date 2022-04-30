#! /usr/local/bin/python3 

import sys

def main (argv):
    if len (argv) < 3:
        print (argv[0], "file list") 
        sys.exit (-1) 
    f_op_handle = open (argv[len (argv) - 1], "w") 
    for f_name in argv[1:len (argv)-1]:
        f_ip_handle = open (f_name, "r") 
        for line in f_ip_handle:
            print (line, end='', file=f_op_handle)
        f_ip_handle.close ()
    f_op_handle.close ()
    sys.exit (0) 

main (sys.argv) 
