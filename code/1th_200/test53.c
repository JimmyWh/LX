#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define N 100

//char *fgets(char *s, int size, FILE *stream);
int main()
{
	FILE *fp;
	
	char str[N+1];

	//printf("[wh] %d\n",__LINE__);
	
	if ((fp = fopen("demo.txt","r")) == NULL)
	{
		printf("demo.txt error!\n");
		exit(0);
	}

	//printf("[wh] %d\n",__LINE__);

	while (fgets(str,N,fp) != NULL)
	{
		//printf("[wh] %d\n",__LINE__);
		printf("%s",str);
	}
	
	//printf("[wh] %d\n",__LINE__);
	printf("\n");
	return 0;
}
