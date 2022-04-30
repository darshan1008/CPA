import os 
import sys 

x = os.fork()
print("P&C:What kind of sorcery is this?") 
print("P&C:x:", x) 


if x == 0: 
    print("C:I AM A CHILD") 
    print("C:my pid = ", os.getpid()) 
    print("C:my parent's id = ", os.getppid())
else:
    print("P:I AM A PARENT") 
    print("P:my pid = ", os.getpid()) 
    print("P:my parent id = ", os.getppid()) 

sys.exit(0) 
