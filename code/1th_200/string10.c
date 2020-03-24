#include <stdio.h>


int max(int x,int y)
{
	if (x > y)
		return x;
	else
		return y;
}



int main()
{
	int a,b,max1 = 0;
	int (*p)(int x,int y);
	scanf("%d,%d",&a,&b);

	p = max;
	max1 = (*p)(a,b);
	printf("max = %d\n",max1);

}

