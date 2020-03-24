

#include <stdio.h>

class person{
public:
	char *name;
	int   age;
	char *work;
	void printInfo(void)
	{
		
	 printf("name = %s,age = %d,work = %s \n",name,age,work);

	}
};


int main(int argc,char **argv)
{

	struct person pers[] = 
	{
			{"zhangsan",10,"teacher"},
			{"lisi",16,"doctor"},
	};

	pers[0].printInfo();
	pers[1].printInfo();
	return 0;
}


