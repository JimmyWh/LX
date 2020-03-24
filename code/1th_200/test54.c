#include <stdio.h>
#include <string.h>

//int strcmp(const char *s1, const char *s2);

int main()
{
	char sr1[15] ;
	char sr2[15] ;

	strcpy(sr1,"zzzzzz");
	strcpy(sr2,"zzzzzz");
	if (strcmp(sr1,sr2) <0)
	{
		printf("sr1 smaller sr2 \n");
	}
	else if (strcmp(sr1,sr2) == 0)
	{
		printf("sr1 eq sr2 \n");
	}
	if (strcmp(sr1,sr2) > 0)
	{
		printf("sr1 biger sr2 \n");
	}
	
}

