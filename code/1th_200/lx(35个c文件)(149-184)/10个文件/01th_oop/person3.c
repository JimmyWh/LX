

#include <stdio.h>

struct person{
	char *name;
	int   age;
	char *work;
	void (*printInfo)(struct person *per);
};


void printInfo(struct person *pers)
{
	printf("name = %s,age = %d,work = %s \n",pers->name,pers->age,pers->work);

}


int main(int argc,char **argv)
{

	struct person pers[] = 
	{
			{"zhangsan",10,"teacher",printInfo},
			{"lisi",16,"doctor",printInfo},
	};

	pers[0].printInfo(&pers[0]);
	pers[1].printInfo(&pers[1]);
	return 0;
}


