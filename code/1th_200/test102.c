
#include <stdio.h>
#include <string.h>


char *my_strcpy_end(register char *dst,register char const *src)
{
	while ((*dst++ = *src++) != '\0')
		;
	return dst - 1;
}


int main(void)
{	
	char *p = "I am here!\n";
	char str[20];
	char *s = NULL;
	s = my_strcpy_end(str, p);
	printf("%s\n",s - 5);
	return 0;
}

