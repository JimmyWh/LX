#include <stdio.h>

#include "test114.h"

#undef malloc

void *alloc(size_t size)
{
	void *new_mem;
	/*
	** ����������ڴ�,�����ȷʵ����ɹ�
	*/

	new_mem = malloc(size);

	if (new_mem == NULL)
	{
		printf("Out of memory!\n");
		exit(1);
	}
	return new_mem;
}

int main()
{
	char *str = NULL;
	str = alloc(sizeof(int));
	printf("%p\n",str);
	return 0;
}

