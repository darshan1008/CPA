#! /usr/bin/python3 

import sys

def main (argv):
    if len (argv) < 2: 
        print ("usage error:", argv[0], "file list") 
        sys.exit (-1) 
    for f_name in argv[1:]:
        try:
            f_handle = open (f_name, "r")
        except FileNotFoundError:
            print (f_name, "not found") 
            print ("Do you want to continue[Y/n]:", end='')
            ans = input ()
            if (ans == "y" or ans == "Y"):
                continue
            else:
                sys.exit (-1) 
        for line in f_handle:
            print (line, end='') 
        f_handle.close ()

    sys.exit (0) 

main (sys.argv)
