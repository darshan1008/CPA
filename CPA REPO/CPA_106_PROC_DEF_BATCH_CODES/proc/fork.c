#include <stdio.h> 
#include <stdlib.h> 
#include <errno.h> 
#include <string.h> 
#include <unistd.h> 
#include <sys/types.h> 

int main(void) 
{
	pid_t pid; 

	pid = fork(); 
	if(pid == 0)
	{
		printf("C:pid = %d ppid = %d\n", getpid(), getppid()); 
	}
	else
	{
		printf("P:pid = %d ppid = %d\n", getpid(), getppid()); 
	}

	exit(0); 
}
