#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student{
	int sid;
	int age;
};


struct Student *CreateStudent(void)
{
	struct Student *p = (struct Student *)malloc(sizeof(struct Student));
	p->sid = 99;
	p->age = 77;
	return p;

}

void ShowStudent(struct Student *pst)
{
	printf("%d %d\n",pst->sid,pst->age);
}

int main()
{
	struct Student *ps;

	ps = CreateStudent();
	ShowStudent(ps);
	return 0;

}