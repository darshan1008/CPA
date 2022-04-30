#! /usr/bin/python3 

import sys

def main (argv): 
    if len (argv) != 3:
        print (argv[0], "f_name size") 
        sys.exit (-1) 
    suffix = argv[2][len(argv[2])-1] 
    if suffix.isalpha ():
        if suffix == "k" or suffix == "K":
            print ("In KB") 
        elif suffix == "m" or suffix == "M":
            print ("In MB") 
    else:
        print ("In Bytes") 


    sys.exit (0) 

main (sys.argv) 
