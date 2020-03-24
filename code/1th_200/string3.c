#include <stdio.h>

int main()
{
	char a[] = "I am student";
	char  b[20];
	char *p1,*p2;
	int i;
	
	p1 = a;
	p2 = b;

	for (; *p1 != '\0'; p1 ++,p2++)
		*p2 = *p1;

	*p2 = '\0';

	p1 = a;
	p2 = b;

	printf("%s \n",p1);
	printf("%s \n",p2);
	
	return 0;
}
