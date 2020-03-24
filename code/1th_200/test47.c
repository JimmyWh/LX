#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int a[5] = {4,110,20,30,45};
	int len,i;
	len = sizeof(a)/sizeof(a[0]);
	int *p = (int *)malloc(sizeof(int) * len);

	for (i =0;i<len;i++)
		scanf("%d",&p[i]);	

	#if 0
	for (i =0;i<len;i++)
		printf("%d ",p[i]);	
	#else
	for (i =0;i<len;i++)
			printf("%d ",*(p+i));
	#endif
	
	printf("\n");

	free(p);
	
	return 0;

}

