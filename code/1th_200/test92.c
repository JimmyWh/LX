
#include <stdio.h>

int ascii_to_integer(char *string)
{
	int value = 0;

	while (*string >= '0' && *string <= '9')
	{
		value *= 10;
		value += *string - '0';
		string ++;
		printf("%d ",value);
	}

	if (*string != '\0')
		value = 0;

	return value;
}

int main(void)
{
	char a[] = "9090";
	printf("%d\n",ascii_to_integer(a));
	return 0;
}

