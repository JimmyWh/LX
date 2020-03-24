#include <stdio.h>

int main(int argc,char *argv[])
{
	while(argc > 1)
	{
		++argv;
		printf("%s\n",argv);
		--argv;
	}
	return 0;
}