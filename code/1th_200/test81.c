
#include <stdio.h>

/*
** 对值进行偶校验
*/

int event_parity(int value,int n_bits)
{
	int parity = 0;

	/*
	** 计数值钟值为1的位的个数
	*/

	while (n_bits > 0)
	{
		parity += value & 1;
		value >>= 1;
		n_bits -= 1;
	}

	/*
	** 如果计数器的最低位为0,返回TRUE
	*/

	return (parity % 2) == 0;

}

int main(void)
{



}

