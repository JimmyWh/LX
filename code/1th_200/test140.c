#include <stdio.h>
#define PRINT(FORMAT,VALUE)  \
		printf("The values is " FORMAT "\n",VALUE)


int main()
{
	int vale = 3;
	PRINT("%d", vale);
	return 0;
}
