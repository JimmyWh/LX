/*
** �ӱ�׼�����ȡһ����EOF��β������������һ��������Щֵ�Ķ�̬���������.
*/

#include <stdio.h>
#include <malloc.h>

#define DELTA 100

int *readints()
{
	int *array;
	int size;
	int count;
	int value;

	/*
	** ��ȡ���������,��С��������DELTA��ֵ.
	*/

	size = DELTA;
	array = malloc((size + 1) * sizeof(int));
	if (array == NULL)
		return NULL;

	/*
	** �ӱ�׼������ֵ.
	*/
	count = 0;
	
	while (scanf("%d",&value) == 1)
	{
		/*
		** �����Ҫ��ʹ������,Ȼ��洢���ֵ.
		*/
		count += 1;
		if (count > size)
		{
			size += DELTA;
			array = realloc(array,(size + 1)* sizeof(int));
			if (array == NULL)
				return NULL;
		}
		array[count] = value;
	}

	/*
	** �ı�����ĳ��ȣ�ʹ��պã�Ȼ��洢����ֵ�������������.
	** ������������ʹ�����������������Ӧ��ʧ��(����Ӧ�ý��м��!).
	*/

	if (count < size)
	{
		array = realloc(array,(count + 1)*sizeof(int));
		if (array == NULL)
			return NULL;

	}
	array[0] = count;
	return array;
	
}
