import os 
import sys 

def main(argc, argv): 
    
    cmd_line = [] 

    if argc == 2: 
        cmd_line.append("gcc") 
        cmd_line.append(argv[1]) 
    elif argc == 3: 
        cmd_line.append("gcc") 
        cmd_line.append(argv[1]) 
        cmd_line.append("-o") 
        cmd_line.append(argv[2]) 
    else: 
        print("Usage Error:%s src_path OR %s src_path exe_path" % (argv[0], argv[0])) 
        sys.exit(-1) 

    x = os.fork() 
    if x == 0: 
        os.execvp("gcc", cmd_line) 
    else: 
        os.wait() 
 
    sys.exit(0) 

main(len(sys.argv), sys.argv) 
