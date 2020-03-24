#include <stdio.h>
#include <malloc.h>
#define MAX 100000000

int main()
{
	int *a[MAX] = {NULL};
	int i;
	for (i=0;i < MAX;i++)
	{
		a[i] = (int *)malloc(MAX* sizeof(int));
	}
	return 0;
}
