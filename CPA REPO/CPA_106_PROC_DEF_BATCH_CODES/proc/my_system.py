import os 
import sys 

def my_system(cmd_line): 

    if type(cmd_line) != str: 
        raise TypeError("Bad type for command line") 
    
    cmd_lst = cmd_line.split(" ") 

    x = os.fork() 

    if x == 0: 
        if cmd_lst[0][0] == "/": 
            os.execv(cmd_lst[0], cmd_lst) 
        else: 
            os.execvp(cmd_lst[0], cmd_lst) 
    else: 
        os.wait() 

def main(): 

    cmd_line1 = "date" 
    cmd_line2 = "ls -l /" 

    my_system(cmd_line1) 
    my_system(cmd_line2) 

    sys.exit(0) 

main() 
