#include <stdio.h>

unsigned int reverse_bits(unsigned int value)
{
	unsigned int answer;
	unsigned int i;

	answer = 0;

	/*
	**ֻҪi ����0�ͼ�������.���ʹѭ����������ֳ��޹ء��Ӷ������˿���ֲ������
	*/

	for (i=1;i !=0;i <<=1)
	{
		/*
		** �Ѿɵ�answer����1λ,Ϊ��һ��λ�����¿ռ�
		** ���value�����һλ��1��answer����1����OR����
		** Ȼ��value��������һ��λ
		*/

		answer <<= 1;
		if (answer & 1)
			answer |= 1;
		value >>= 1;
	}
	return answer;
}

int main(void)
{
	unsigned int a;
	a = reverse_bits(00000000000000000000000000011001);
	printf("%d\n",a);
	return 0;
}
