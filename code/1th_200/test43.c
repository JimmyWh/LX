#include <stdio.h>
#include <stdlib.h>
#define LEN 10

typedef struct student
{
	long num;
	char name[LEN];
	float score[3];

}STUDENT;

int main()
{
	STUDENT *p = NULL;
	int i,j,n;
	scanf("%d",&n);
	p = (STUDENT *)malloc(n*sizeof(STUDENT));
	if (p == NULL)
	{
		printf("No enough memory!\n");
		exit(0);
	}
	printf("Please input this infomations:\n");
	printf("num\\name\\MT\\EN\\PH\n");
	for (i=0;i <n;i++)
	{
		printf("\nthe %d student :\n",i +1);
		scanf("%ld",&p[i].num);
		scanf("%s", p[i].name);
		for (j=0; j <3;j++)
			scanf("%f",&p[i].score[j]);
		
	}

	printf("\n*************************\n");
	for (i=0;i <n;i++)
	{
		
		printf("%ld ",p[i].num);
		printf("%s ", p[i].name);
		for (j=0; j <3;j++)
			printf("%f ",p[i].score[j]);
		
	}
	printf("\n*************************\n");
}
