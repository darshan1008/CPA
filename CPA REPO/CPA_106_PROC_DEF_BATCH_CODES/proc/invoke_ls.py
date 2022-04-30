import os 
import sys 

def main(): 
    
    print("I am going to execute ls -l / command") 

    os.execlp("ls", "ls", "-l", "/") 

    print("I am done with executing ls -l / command") 


main() 
