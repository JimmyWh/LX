#include <stdio.h>

size_t strlen(char *string)
{
	int length = 0;

	/*
	** 依次访问字符串的内容计数字符，知道遇见NULL终止符 .
	*/

	while (*string ++ != '\0')
	{
		length += 1;
	}
	return length;

}

int main(void)
{
	int num;
	char *a = "I love you wh.";
	num = strlen(a);
	printf("num = %d\n",num);
	return 0;
}
