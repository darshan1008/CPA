#include <stdio.h> 
#include <stdlib.h>

#define OFFSET_OF(T,x)				((unsigned long long int)(&(((T*)0)->x)))
#define CONTAINER_OF(x, T, name)	((T*)(((char*)x)-OFFSET_OF(T,name)))

#define G_INSERT(beg, mid, end)		do\
									{\
										(mid)->next = (end);\
										(mid)->prev = (beg);\
										(end)->prev = (mid);\
										(beg)->next = (mid);\
									}while(0)

#define G_DELETE(p_link, T, name) 	do\
									{\
										(p_link)->prev->next = (p_link)->next;\
										(p_link)->next->prev = (p_link)->prev;\
										free(CONTAINER_OF((p_link), T, name));\
									}while(0) 


struct list_head
{
	struct list_head* prev; 
	struct list_head* next; 
}; 

struct int_struct
{
	int data; 
	struct list_head links; 	
}; 

struct double_struct
{
	double data; 
	struct list_head links; 
}; 

struct student_struct
{
	char name[128]; 
	int i_roll; 
	float f_marks; 
	struct list_head links; 
}; 

int main()
{
	struct int_struct is1, is2, is3; 
	struct double_struct ds1, ds2, ds3; 
	struct student_struct ss1, ss2, ss3; 

	struct list_head i_list = {&i_list, &i_list}, 
		   			 d_list = {&d_list, &d_list}, 
					 s_list = {&s_list, &s_list}; 

	

	
	G_INSERT(i_list.prev, &is1.links, &i_list); 
	G_INSERT(i_list.prev, &is2.links, &i_list); 
	G_INSERT(i_list.prev, &is3.links, &i_list); 

	return (0); 
}

/* 
int* p = 1000 

p+1
p+1*sizeof(int)

p + k 

p + k * sizeof(int)

T* p; 

sizeof(*p) == sizeof(T)

p + k 
==
Address in p + k * sizeof(*p)

p - k 
== 
Address in p - k * sizeof(*p)

(char*)p + k 
Address in p + k * sizeof(char)
Address in p + k 

(char*)p - k 
Address in p - k * sizeof(char)
Address in p - k 
*/ 

/* 
struct buffer{
	void* buff_data; 
	struct list_head hash_links; 
	struct list_head free_links; 
}; 

struct list_head* p_run_hash; 
struct list_head* p_run_free_list;

struct student{
	char name[128]; 
	int i_roll; 
	float f_marks; 

	struct list_head sorted_name; 
	struct list_head sorted_roll; 
	struct list_head sorted_marks; 
};  

*/ 
