#include <stdio.h>


void binary_to_ascii(unsigned int value)
{
	unsigned int quotient;

	quotient = value / 10;

	if (quotient != 0)
		binary_to_ascii(quotient);
	
	putchar(value % 10 + '0');
	putchar(' ');
}

int main(void)
{
	int a = 4789;
	binary_to_ascii(a);
	putchar('\n');
	return 0;
}

