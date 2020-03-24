#include <stdio.h>

unsigned int reverse_bits(unsigned int value)
{
	unsigned int answer;
	unsigned int i;

	answer = 0;

	/*
	**只要i 不是0就继续进行.这就使循环与机器的字长无关。从而避免了可移植行问题
	*/

	for (i=1;i !=0;i <<=1)
	{
		/*
		** 把旧的answer左移1位,为下一个位置留下空间
		** 如果value的最后一位是1，answer就与1进行OR操作
		** 然后将value右移至下一个位
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
