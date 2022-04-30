import os 
import sys 

def main(): 

    x = os.fork() 
    print("This will be executed twice", os.getpid()) 

    if x == 0: 
        # Child with replace whatever it has inherited from 
        # parent by the contents of executable file /bin/ls 
        #os.execlp("ls", "ls", "-l", "/")
        pass
    else: 
        os.wait() 
        print("P: My CHILD IS DEAD", os.getpid()) 

    print("This will be executed only ONCE", os.getpid()) 
    sys.exit(0) 

main() 
