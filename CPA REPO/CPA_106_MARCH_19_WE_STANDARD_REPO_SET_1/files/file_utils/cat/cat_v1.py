#! /usr/bin/python3 

import sys

def main (argv): 
    if len (argv) != 2:
        print ("usage error:", argv[0], "file_name") 
        sys.exit (-1) 
    f_handle = open (argv[1], "r") 
    if f_handle == None:
        print ("Error in opening file", argv[1])
        sys.exit (-1) 
    for line in f_handle:
        print (line, end='') 
    f_handle.close ()
    sys.exit (0) 

main (sys.argv)
