#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main()
{
	char *a = NULL;
	a = (char *)malloc(sizeof(a)*-100);
	if (!a)
	{
		printf("failed: %s \n",strerror(errno));
		return -1;
	}
	
	sprintf(a,"%s","HelloWorld\n");//
	printf("%s",a);
	free(a);
	a =  NULL;
	return 0;

}

