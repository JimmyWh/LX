#include <stdio.h>

int main(void)
{
	int a[4][4] = {{1,2},{3,4},{5,6},{8,9}}; 
	int *mp = NULL;
	mp = &a[1][0];
	//printf("mp = %p,*mp = %d\n",mp,*mp);
	printf("First  value  is %d\n",*mp);
	printf("Second value  is %d\n",*++mp);	
	printf("Third  value  is %d\n",*++mp);
	return 0;
}


