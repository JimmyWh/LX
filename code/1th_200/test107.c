#include <stdio.h>
#define CH 20
int main(void)
{
	char ch[CH];
	printf("�������������:\n");
	gets_s(ch,CH - 1);
	printf("�����������: %s\n",ch);
	return 0;

}