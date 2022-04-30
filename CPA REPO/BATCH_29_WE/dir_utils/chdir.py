import sys 
import os 

def main(argc, argv): 
    
    if argc != 2: 
        print("Usage Error : %s" % (argv[0], )) 
        sys.exit(-1) 

    pwd = os.getcwd() 
    print("Present Working Directory:", pwd) 

    os.chdir(argv[1]) 

    pwd = os.getcwd() 
    print("Present Working Directory:", pwd) 
    
    sys.exit(0) 

main(len(sys.argv), sys.argv) 
