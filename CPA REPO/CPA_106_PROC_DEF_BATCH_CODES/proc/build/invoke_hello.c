#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <sys/types.h> 
#include <sys/wait.h> 

int main(void) 
{
	pid_t pid; 
	int ret; 

	pid = fork(); 
	if(pid == 0) 
		execl("./hello.exe", "hello.exe", (char*)0); 
	else
		wait(&ret); 
	
	printf("ret = %hhu\n", *(unsigned char*)((char*)&ret + 1)); 
	return (0); 
}
