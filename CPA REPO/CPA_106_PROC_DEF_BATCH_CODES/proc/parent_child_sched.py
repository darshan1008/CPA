import os 
import sys 
import time 

def main(): 
    
    x = os.fork() 

    if x == 0: 
        while True: 
            print("C:pid = %d ppid = %d" % (os.getpid(), os.getppid()))
            time.sleep(1) 
    else: 
        while True: 
            print("P:pid = %d ppid = %d" % (os.getpid(), os.getppid()))
            time.sleep(2) 

    sys.exit(0) 

main() 
