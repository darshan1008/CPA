"""Purpose of this utility is to emulate total build, -c (Compile + Assembler) and 
-S (Compile only) option of built-in gcc command. 
Invokes: 
    #python3 pygcc.py <src>.c    ---> <src>.exe 
    #python3 pygcc.py -S <src>.c ---> <src>.S 
    #python3 pygcc.py -c <src>.c ---> <src>.o 
Bult-in commands used: 
    #gcc <src>.c -o <src>.exe   for total build 
    #gcc -S -o <src>.S <src>.c  for compile only 
    #as -o <src>.o <src>.c      for assembly 
    #ld -o <src>.exe -lc -dynamic-linker /lib64/ld-linux-x86-64.so.2 <src>.o -e main 
""" 

import os 
import sys 

def main(argc, argv): 
    
    src_file_name = None
    
    if argc == 2: 
        src_file_name = argv[1] 
    elif argc == 3: 
        src_file_name = argv[2] 
    else: 
        print("Usage Error") 
        sys.exit(-1) 

    if not src_file_name.endswith(".c"): 
        print("Bad file extension for source file") 
        sys.exit(-1) 

    is_compile = False
    is_assemble = False
    is_link = False

    if argc == 2: 
        is_compile = True
        is_assemble = True 
        is_link = True 
    elif argc == 3: 
        if argv[1] == '-S': 
            is_compile = True 
        elif argv[1] == '-c': 
            is_compile = True
            is_assemble = True 
        else: 
            print("Usage Error") 
            sys.exit(-1) 

    assembly_file_name = src_file_name[:-2] + ".S" 
    object_file_name = src_file_name[:-2] + ".o" 
    exe_file_name = src_file_name[:-2] + ".exe" 

    if is_compile: 
        x = os.fork() 
        if x == 0: 
            os.execlp("gcc", "gcc", "-S", "-o", assembly_file_name, src_file_name) 
        else: 
            r = os.wait() 
            # Check whether child exited successfully or not 
            # if not then print error log and exit 
            # if yes then go ahead 
            if is_assemble: 
                x = os.fork() 
                if x == 0: 
                    os.execlp("as", "as", "-o", object_file_name, assembly_file_name) 
                else:
                    os.wait() 
                    if is_link: 
                        x = os.fork() 
                        if x == 0: 
                            os.execlp("ld", "ld", "-o", exe_file_name, "-lc", "-dynamic-linker", 
                                        "/lib64/ld-linux-x86-64.so.2", object_file_name, "-e", "main") 
                        else:
                            os.wait() 
    sys.exit(0) 

main(len(sys.argv), sys.argv) 
