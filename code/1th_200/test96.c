#include <stddef.h>
#include <stdio.h>

size_t strlen(char const *string)
{
	int length;

	for (length = 0; *string++ != '\0';)
		length += 1;

	return length;

}

int main()
{
	int ret = 0;
	char a[] = "12345";
	if (strlen(a) >= 20)
	{
		printf("I am here1\n");
	}
	else if (strlen(a) - 20 >= 0)
	{
		printf("I am here2\n");
	}
	else
	{
		printf("value err!\n");
	}
	
	
	return 0;
}


