#include <stdio.h>

int main()
{
#if 0
	char *a = "I love you";
	a = a + 8;
	printf("%s \n",a);

	char *a = "I love you";
	a = a + 1;
	printf("%s \n",a);


	char *a = "I am a studnet.";
	char b[] = "123ded.";
	//a[2] = 'r';
	b[2] = 'r';
	printf(" a = %s, b = %s\n",a,b);


	char *format;
	int a = 1;
	float b =3.0;
	format = "a = %d,b =%f\n";
	printf(format,a,b);
#endif
	int   a = 1;
	float b =3.0;
	char format[] = "a = %d,b =%f\n";
	
	printf(format,a,b);
	
	return 0;
}

