#include <stdio.h>

float *search(float (*pointer)[4])
{
	int i =0;
	float *pt = NULL;
	for (; i <4;i++)
		if(*(*pointer+i) < 60)
			pt = *pointer;
	return pt;
}


int main()
{
	float score[][4] = {{30,70,80,90},{58,78,67,88},{34,78,90,66}};

	float *p;
	int i,j;
	for (i =0;i < 3;i++)
	{
		p = search(score + i);

		if (p == *(score + i))
		{
			printf("No.%d score:",i);
			for (j =0; j <4;j++)
				printf("%5.2f ",*(p + j));
			printf("\n");
			
		}
	}
	return 0;
}


