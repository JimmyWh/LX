#include <stdio.h>

int main(void)
{
	char  a1[] = "1234";  /* 对于字符串来说sizeof 会计算字符串有几个字节char类型(1个字节)                   */
	int   a2[4]; /* 对应数组来说sizeof把int类型(4字节) * 4个元素 = 16字节                	 */
	char *pc = "abc"; /* 对于pc指针来说sizeof为4个字节  */
	printf("a1 = %d , a2 = %d, pc = %d\n",sizeof(a1),sizeof(a2),sizeof(pc));
}
