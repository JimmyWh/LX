
#include <stdio.h>

/*
** ��ֵ����żУ��
*/

int event_parity(int value,int n_bits)
{
	int parity = 0;

	/*
	** ����ֵ��ֵΪ1��λ�ĸ���
	*/

	while (n_bits > 0)
	{
		parity += value & 1;
		value >>= 1;
		n_bits -= 1;
	}

	/*
	** ��������������λΪ0,����TRUE
	*/

	return (parity % 2) == 0;

}

int main(void)
{



}

