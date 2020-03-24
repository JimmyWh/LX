#include <stdio.h>
#define MAX(a,b) ((a) > (b) ? (a):(b))

int main()
{
	int x = 5,y = 8,z;
	z = MAX(x++, y++);
	printf("x = %d,y = %d,z = %d\n",x,y,z);
}
