#! /usr/bin/python3 

import sys

def main (argv):
    if (len (argv) != 2):
        print ("usage error:", argv[0], "file name") 
        sys.exit (-1)
    nr_lines = 0
    nr_chars = 0
    f_handle = open (argv[1]) 
    for line in f_handle:
        nr_lines = nr_lines + 1
        nr_chars = nr_chars + len (line)
    f_handle.close ()
    print ("nr_lines:", nr_lines)
    print ("nr_chars:", nr_chars)
    sys.exit (0) 

main (sys.argv) 

