#include<stdio.h>
#include<stdlib.h>

int main()
{
    int i;

    for(i=1; i<256; i = i<<2)
        printf("i = %d\n",i);
        
    exit(0);
}