#include <stdio.h>

int max(int x,int y)
{
	if (x > y)
		return  x;
	else
		return  y;
}	


int min(int x,int y)
{
	if (x > y)
		return  y;
	else
		return  x;
}	

int main()
{

	int a,b,n,min1,max1;
	int (*p)(int ,int );
	printf("Please enter the number a,b:\n");
	scanf("%d,%d",&a,&b);
	printf("Please enter the number n:\n");
	scanf("%d",&n);
	if (n == 0) //min
	{
		p = min;	
		min1 = (*p)(a,b);
		printf("min = %d\n",min1);
		
	}
	if (n ==1) //max
	{
		p = max;
		max1 = (*p)(a,b);
		printf("max = %d\n",max1);
	}
	
	
	return 0;
}

