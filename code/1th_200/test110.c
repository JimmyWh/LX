#if 0
#include <stdio.h>

int main()
{
	char buffer[10];
	char *a = "1234";
	char *b = "5678";
	sprintf(buffer,"%s%s",a,b);
	printf("%s\n",buffer);
	return 0;
}
#else
#include <stdio.h>

int main()
{
	char a[] = {'1','2','3','4'};
	char b[] = {'5','6','7','8'};
	char buffer[10];
	sprintf(buffer,"%4s%4s",a,b);
	printf("%s\n",buffer);
	return 0;
}

#endif