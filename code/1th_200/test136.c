/*
** 神秘函数
**
** 参数是一个0 -100的值
*/

#include <stdio.h>

void mystery(int n)
{
	n += 5;
	n /= 10;
	printf("%s\n","************"+10 -n);

}

int main()
{
	mystery(90);
	return 0;
}
