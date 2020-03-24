/*
** 接受一个整形值(无符号),把它转换成字符，并打印出来，前导零被去除.
*/

#include <stdio.h>
#define DEBUG_PRINT printf("File %s line %d:" \
					 "x = %d,y = %d,z = %d", \
					 __FILE__,__LINE__,   \
						x,y,z)
#if 0  
void binary_to_ascii(unsigned int value)
{
	unsigned int quotient;
	quotient = value / 10;
	if (quotient != 0)
		binary_to_ascii(quotient);
	putchar(value % 10 + '0');
}
#endif


int main()
{
	int x = 1,y = 2,z = 3;
	x *= 2;
	y += x;
	z = x * y;
	DEBUG_PRINT;
	printf("\n");
	return 0;
}


