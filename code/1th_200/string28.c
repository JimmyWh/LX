#include <stdio.h>
#include <string.h>


struct Student
{
	int num;
	char name[20];
	struct Student *next;
};

int main()
{
	
	struct Student a,b,c,*p,*head;
	a.num = 10101;	strcpy(a.name,"wuhai");
	b.num = 10102;	strcpy(b.name,"liwei");
	c.num = 10103;	strcpy(c.name,"wulong");
	head   = &a;
	a.next = &b;
	b.next = &c;
	c.next = NULL;
	p = head;

	do 
	{
		printf("%d %s \n",p->num,p->name);
		p = p ->next;
		
	}while(p != NULL);
	
	return 0;
}

