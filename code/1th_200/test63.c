#include <stdio.h>
#include <stdlib.h>

void copy_n(char dst[],char src[],int n)
{
	int dst_index,src_index;
	src_index = 0;
	printf("[wh] %d\n",__LINE__);
	for (dst_index =0; dst_index < n;dst_index ++,src_index++)
	{	
		dst[dst_index] = src[src_index];
		printf("[wh] %d ,dst_index = %d,src_index = %d\n",__LINE__,dst_index,src_index);
	}
	if (src[src_index] != 0)
		src_index += 1;
}

int main(void)
{
	char dst[40] = "I love you.";
	char src[20] = "China";
	printf("[wh] %d\n",__LINE__);
	copy_n(dst,src,12);
	printf("%s\n",dst);
	return 0;
}

