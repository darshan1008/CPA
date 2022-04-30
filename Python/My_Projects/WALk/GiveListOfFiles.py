import os
import sys

def give_All_Dir_File_Count(List_Root):

    

  #  print(List_Root)
    
    dir_count = 0
    file_count = 0
    for Dir in List_Root:
        #print("Directory count  :",Dir[0])
        dir_count += 1
        for dir_name in Dir[2]:
            #print("dir_name : ",dir_name)
            file_count += 1

            
    print("Given Directory contain ",dir_count-1,"Directories")
    print("Given Directory contain ",file_count,"Files")
    return 


def particular_filetype_count(List_Root,file_type):

    file_count = 0

    F_Handle = open("fileName.log","w");
    
    for Dir in List_Root:
        for file in Dir[2]:
            if file.endswith(file_type):
                print(file,file=F_Handle);
                file_count+=1
                
            
    return file_count


def main():
    
    print("Enter the path of Root Directory")
    root_path = input()
    try:
        List_Root = os.walk(root_path)
        
    except FileNotFoundError:
        print("NO such Directory")
        sys.exit(-1)
        
    give_All_Dir_File_Count(List_Root)

    List_Root = os.walk(root_path)
    print("\nEnter File Type [For Ex : '.txt']")
    f_type = input()
    print("Count of ",f_type,"is :",particular_filetype_count(List_Root,f_type))

    
    sys.exit(0)
    
main()
