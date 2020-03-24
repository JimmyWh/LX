#include <stdio.h>
#define PROCESS_LOOP           \
		for (i=0;i < 10;i++)   \
		{      
			printf("i = %d,sum = %d,prod = %d\n",i,sum,prod);
			sum += i;          \
			if (i > 0)         \
				prod *= i;     \
		}            

int main()
{
	int i = 9;
	int sum = 0,prod = 1;
	PROCESS_LOOP(9,0,1);
	printf("prod = %d\n",prod);
}