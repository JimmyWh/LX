
#include <stdio.h>
#define ARRAY_SIZE 5

int main()
{
	int array[ARRAY_SIZE] = {0};
	int *pi;

	for (pi=&array[0];pi < &array[ARRAY_SIZE];)
	{
		printf("%d\n",*pi++);
	}
	return 0;
}

