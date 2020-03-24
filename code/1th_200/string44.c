#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

 struct Student_type
  {
	char name[10];
	int num;
	int age;
	char addr[15];
 }stud[SIZE];


int main()
{
	FILE *fp;
	int i;
	
	if ((fp = fopen("stu.dat","r")) == NULL)
	{
		printf("file open fail\n");
		exit(0);
	}

	for (i=0; i <SIZE;i++)
	{
		fread(&stud[i],sizeof(struct Student_type),1,fp) ;
		printf("%s,%d,%d,%s \n",stud[i].name,stud[i].num,stud[i].age,stud[i].addr);
	}
	
	return 0;
}

