#include <stdlib.h>

int *frequency(int size)
{
	int *array;
	int i;

	/*
	** ��ȡ�㹻���ڴ������ɼ���.
	*/
	array = (int *)malloc(size *sizeof(int));
	if (array == NULL)
	{
		printf("memory malloc err!\n");
		return NULL;
	}
	
	/*
	** ����ָ�룬��������һ������λ��,�������ǾͿ���ʹ��1-size���±�.
	*/
	array -= 1;

	/*
	** �Ѹ���Ԫ��ֵ����.
	*/
	for (i=1; i <= size;i++)
		array[i] = 0;

	/*
	** ����ÿ��ֵ���ֵĴ���,Ȼ�󷵻ؽ��.
	*/
	while (scanf("%d",&i) == ) )
		array[i] += 1;

		//free(array);
		return array;

}
