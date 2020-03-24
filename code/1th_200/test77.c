#include <stdio.h>

int main()
{
	int i[10] = {0,1,2,3,4,5,6,7,8,9};
	int *p1 = &i[0];
	int *p2 = &i[0];
	int offset = 3;
	
	p1 = p1 + offset;
	p2 = p2 + 3;

	printf("%d,%d\n",*p1,*p2);
	return 0;
}


