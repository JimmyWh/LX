#include <stdio.h>
#define CH 20
int main(void)
{
	char ch[CH];
	printf("请输入你的名字:\n");
	gets_s(ch,CH - 1);
	printf("这是你的名字: %s\n",ch);
	return 0;

}