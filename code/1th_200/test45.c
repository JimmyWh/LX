#include <stdio.h>
#include <stdlib.h>

short gStr1[15];
int   gStr2[15];


void ReadStr1(short *buf,int size)
{
	int i;
	for (i =0;i < size;i++)
		 gStr1[i] = buf[i];
	
	printf("%s\n",gStr1);
	printf("%c\n",gStr1[0]);
	printf("%c\n",gStr1[1]);
	printf("%s\n",gStr1 + 1);
	
}

void ReadStr2(int *buf,int size)
{
	int i;
	for (i =0;i < size;i++)
		gStr2[i] = buf[i];

	
	printf("%s\n",gStr2);
	printf("%c\n",gStr2[0]);
	printf("%c\n",gStr2[1]);
	printf("%s\n",gStr2+ 1);

}



int main()
{
	char s1[] = {"ABCDEFHIJK"};
	char s2[] = {"abcdefhijk"};
	printf("gStr1 shuzude qingkuang fenxi:\n");
	ReadStr1((short *)s1,5);
	printf("\n");
	printf("gStr2 shuzude qingkuang fenxi:\n");
	ReadStr2((int *)s2,3);
	
	
	return 0;

}

