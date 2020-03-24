#include <stdio.h>
#include <string.h>

int main()
{
	char a[] = ".............abcdefg3333333333333333333.............";
	char b[50];
	memcpy(b,a,sizeof(a)/sizeof(a[0]));
	printf("%s\n",b);
	memset(b,0,50);
	printf("[wh] %s\n",b);
	return 0;
}
