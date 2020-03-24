#include <stdio.h>
#include <string.h>

//char *strtok(char *str, const char *delim);

void main()
{
	char s[] = "192.168.0.26";
	char *delim = ".";
	char *p = NULL;

	printf("%s ",strtok(s,delim));
	//printf(" %s %d\n",__FUNCTION__,__LINE__);

	while ((p = strtok(NULL,delim)))
	{
		printf("%s %d\n",__FUNCTION__,__LINE__);
		printf("%s ",p);
	}	
	
	printf("\n");
	printf("%s %d\n",__FUNCTION__,__LINE__);
	printf("\n");

}

