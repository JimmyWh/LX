#include <stdio.h>
#include <stdlib.h>

#define DEUBG 1

#if DEUBG
void swap(int *pt1,int *pt2)
{
	int temp;
	temp = *pt1;
	*pt1 = *pt2;
	*pt2 = temp;
	printf("%d,%d\n",*pt1,*pt2);
	
}
#else
void swap(int *pt1,int *pt2)
{
	int temp;
	temp = pt1;
	pt1 = pt2;
	pt2 = pt1;
	printf("%d,%d\n",*pt1,*pt2);
	
}

#endif


int main()
{
	int a,b,*p1,*p2;
	a = 3;
	b = 4;
	p1 = &a;
	p2 = &b;
	#if DEUBG
	swap(p1,p2);
	#else
	swap(p1,p2);
	#endif
	printf("p1 = %d,p2 = %d\n",*p1,*p2);
}

