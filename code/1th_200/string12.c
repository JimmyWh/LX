#include <stdio.h>

int max(int x,int y)
{
	printf("max ....\n");
	if (x > y)
		return x;
	else
		return y;
	
}

int min(int x,int y)
{
	printf("min ....\n");
	if (x > y)
		return y;
	else
		return x;
	
}

int add(int x,int y)
{
	
	printf("add ....\n");
	return x + y;
}



int fun(int x,int y,int (*p)(int x,int y))
{
	int result;
	result = (*p)(x,y);
	return result;
}

int main()
{
	int a = -1,b =100,n,max1,min1,add1;
	
	printf("Please choose the number :\n");

	scanf("%d",&n);
	
	if (n == 0) //max 
	{
		max1 = fun(a,b,max);
		printf("max = %d\n",max1);	
	}
	if (n == 1) //min 
	{
		min1 = fun(a,b,min);
		printf("min = %d\n",min1);
	}
	if (n == 2) //add 
	{
		add1 = fun(a,b,add);
		printf("add = %d\n",add1);
	}
	return 0;
}


