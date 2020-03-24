#include <stdio.h>
#include <stdlib.h>

int main()
{
	char *ptr;
	if ((ptr = (char *)malloc(0)) == NULL)
		puts("Gotanullpointer");
	else
		puts("Gotavalidpointer");
	return 0;
}
