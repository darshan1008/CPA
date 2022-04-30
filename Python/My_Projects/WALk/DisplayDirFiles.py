import os
import sys

def main(argc,argv):

    cur_dir = os.getcwd()
    
    print(cur_dir)
    
    wObj = os.walk(cur_dir)

    for Dir in wObj:
        print(wObj)
        for DirList in Dir[1]:
            print(DirList)
        for FileList in Dir[2]:
            print(FileList)
        
    
    sys.exit(0)

main(len(sys.argv),sys.argv)
