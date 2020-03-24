#include <stdio.h>
#include <stdlib.h>
 #include <string.h>
 
typedef struct date_type{
	int age;
	char name[20];
}data;


int main()
{
	data *bob = (data *)malloc(sizeof(data));
	if (bob != NULL)
	{
		printf("%p\n",bob);
		bob->age = 29;
		strcpy(bob->name,"wuhai");
		printf("%s age is %d\n",bob->name,bob->age);
	}
	else
	{
		printf("malloc memry err!\n");
		return -1;
	}
	free(bob);
	bob = NULL;
	return 0;
}

