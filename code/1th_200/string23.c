#include <stdio.h>

struct Person{
		char name[20];
		int  count;
}leadr[3] = {"zhang",0,"san",0,"li",0};
	
int main()
{
	int i,j;
	char leadr_name[20];
	
	for(i =1;i <10;i++)
	{
		scanf("%s",leadr_name);
		for (j =0;j <3;j++)
			if (strcmp(leadr_name,leadr[j].name) == 0)
				leadr[j].count ++;
			
	}
	printf("\nResult:\n");
	for (i=0;i <3;i++)
		printf("%5s:%d\n",leadr[i].name,leadr[i].count);
	printf("\n");
	return 0;

}

