
#include <stdio.h>
#include <string.h>

char *my_strcpy_end(char *dst,char const *src)
{
	strcpy(dst,src);

	return dst + strlen(dst);
}


int main()
{
	char *str = "I love you!";
	char s[20];
	char *pst = NULL;
	pst = my_strcpy_end(s,str);
	printf("%s,%d,%s\n",__FUNCTION__,__LINE__,pst - 5);
	return 0;
}

