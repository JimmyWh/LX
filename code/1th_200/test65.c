#include <stdio.h>
#include <stdlib.h>

int count_one_bit(unsigned value)
{
	int ones;
	for (ones =0;value != 0;value = value >> 1)
	{
		if ((value & 1) != 0)
			ones ++;
	}
	return ones;
}

int main(void)
{
	int count = 0;
	count = count_one_bit(0x111);
	printf("%d\n",count);
	return EXIT_SUCCESS;
}

