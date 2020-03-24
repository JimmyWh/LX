#include <stdlib.h>

int *frequency(int size)
{
	int *array;
	int i;

	/*
	** 获取足够的内存来容纳计数.
	*/
	array = (int *)malloc(size *sizeof(int));
	if (array == NULL)
	{
		printf("memory malloc err!\n");
		return NULL;
	}
	
	/*
	** 调整指针，让它后退一个整型位置,这样我们就可以使用1-size的下标.
	*/
	array -= 1;

	/*
	** 把各个元素值清零.
	*/
	for (i=1; i <= size;i++)
		array[i] = 0;

	/*
	** 计数每个值出现的次数,然后返回结果.
	*/
	while (scanf("%d",&i) == ) )
		array[i] += 1;

		//free(array);
		return array;

}
