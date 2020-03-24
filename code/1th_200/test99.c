#include <stdio.h>
#include <string.h>
#include <stddef.h>

size_t my_strlen(char const *string,int size)
{
	register size_t length;

	for (length =0;length < size;length += 1)
		if (*string++ == '\0')
			break;
		
	return length;
}


int main()
{
	size_t len = 0;
	char str[] = "I love you!";
	len = my_strlen(str,sizeof(str[10])/sizeof(str[0]));
	printf("string len = %zu\n",len);
	return 0;
}

