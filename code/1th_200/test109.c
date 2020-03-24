#include <stdio.h>

typedef struct{
	char ch[5];
}qAp;

typedef union{
	int i;
	char ch[sizeof(int)];
}CHI;

int main(int argc,char const *argv[])
{
	qAp h = {"abc"};
	CHI c;
	int i;
	c.i = 10000;
	for (i=0;i <sizeof(int);i++)
	{
		printf("%02hhX",c.ch[i]);
	}
	printf("\n");

	c.ch[1] = 'a';
	printf("%d\n",c.i);
	return 0;
	

}

