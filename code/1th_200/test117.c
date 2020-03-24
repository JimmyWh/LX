/*
** ��ȡ����ʹ�ӡһ������ֵ.
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
** �ú�����'qsort'����,���ڱȽ�����ֵ.
*/
int compare_integers(void const *a,void const *b)
{
	register int const *pa = a;
	register int const *pb = b;

	return *pa > *pb ?1:*pa < *pb ?-1:0;

}

int main()
{
	int *array;
	int n_values = 0;
	int i;

	/*
	** �۲칲�ж��ٸ�ֵ.
	*/
	printf("How many values are there?\n");

	if (scanf("%d",&n_values) != 1 || n_values <= 0)
	{
		printf("Illegal number of values.\n");
		exit(EXIT_FAILURE);
	}
	printf("%s,%d\n",__FUNCTION__,__LINE__);
	/*
	** �����ڴ�,���ڴ洢��Щֵ
	*/
	array = malloc(n_values*sizeof(int));
	if (array == NULL)
	{
		printf("can't get memory for that many values.\n");
		exit(EXIT_FAILURE);
	}
	printf("%s,%d\n",__FUNCTION__,__LINE__);
	memset(array,0,n_values);
	/*
	** ��ȡ��Щ��ֵ.
	*/
	for (i =0; i < n_values;i++)
	{
		printf("array = %d,n_values = %d\n",*(array + i),n_values);
		if (scanf("%d",array + i) != 1)
		{
			printf("Error reading value # %d\n",i);
			free(array);
			exit(EXIT_FAILURE);
		}
	}
	
	/*
	** ����Щֵ����.
	*/
	qsort(array,n_values,sizeof(int),compare_integers);
	printf("%s,%d\n",__FUNCTION__,__LINE__);
	/*
	** ��ӡ��Щֵ.
	*/
	for (i=0;i < n_values;i++)
			printf("%d\n",array[i]);

	/*
	**�ͷ��ڴ沢�˳�
	*/
	printf("%s,%d\n",__FUNCTION__,__LINE__);
	free(array);
	return EXIT_SUCCESS;
}

