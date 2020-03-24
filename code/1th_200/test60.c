#include <stdio.h>

void print(void)
{
	int i;
	for (i =1;i <=4;i++)
	{
		printf("%d \n",i %2);
		switch (i%2)
		{
			case 0:
				printf("event\n");
				
			case 1:
				printf("odd\n");	
		}
	}
}


int main(void)
{
	print();
	return 0;
}

