#include <stdio.h>
#include <stdlib.h>

int main()
{
	int *pi = NULL;
	pi = (int *)malloc(10 * sizeof(int));
	/*
	** Free only the last 5 integers;keep the first 5
	*/
	free(pi);
	return 0;
}

