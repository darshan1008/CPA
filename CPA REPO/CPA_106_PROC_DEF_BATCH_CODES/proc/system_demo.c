#include <stdio.h> 
#include <stdlib.h> 

int main(void) 
{
	const char *cmd_line1 = "date"; 
	const char *cmd_line2 = "ls -l /";  

	system(cmd_line1); 
	system(cmd_line2); 

	return (0); 	
}
