#include<stdio.h>

void s1();
void s2();
void s3();
void * s4();

int main()
{

	//s1();
	//s2();
	//s3();
	int *p = (int *)s4();

	printf("%d\n",   *p );
	return 0;
}


void * s4()
{
	static int i = 10;

	return &i; 
}

void s3()
{
	int n1 = 10,n2=20,n3=30,n4 = 40;
	int *daytab[13] = {&n1,&n2,&n3,&n4};
	int i;

	for(i = 0 ; daytab[i] != NULL ; i++)
		printf("%d\n",*(daytab[i]));


}

void s2()
{
	int arr[13] = {1,2,3,4,5,6};
	int (*daytab)[13];			//s2
	int i;

	daytab = &arr;

	for(i=0;i<13;i++)
		printf("%d\t",(*daytab)[i]);

}

void s1()
{
	char ch = 's';
	char *str = &ch;//"hello";
	char **argv = NULL;			//s1

	argv = &str;
	printf("\n%s\n%c",*argv,**argv);

}