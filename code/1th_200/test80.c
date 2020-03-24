#include <stdio.h>

int *find_int(int key,int array[],int array_len)
{

	int i;

	/*
	** 对于数组中的每个位置....
	*/

	for (i=0; i < array_len; i += 1)

		/*
		** 检查这个位置的值是否为需要查找的值.
		*/

	if (array[i] == key)
		return &array[i];

	printf("%d,%s\n",__LINE__,__FUNCTION__);

	return NULL;

}

int main(void)
{
	int *ret = NULL;
	int a[] = {411,14,3,3,45,3345};
	ret = find_int(3,a,6);
	printf("%d,%s\n",__LINE__,__FUNCTION__);
	printf("%d\n",*ret);
	return 0;
}



