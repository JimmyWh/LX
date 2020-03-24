#include <stdio.h>

void mocpy_from(char form[],char to[])
{
	int i;
	while (form[i]  != '\0')
	{
		to[i] = form[i];	
		i++;
	}
	
	to[i] = '\0';
}

int main()
{
	char a[] = "I am a student.";
	char b[] = "You are a student.";
	char *from = a;
	char *to = b;
	printf("a = %s\b = %s\n",a,b);
	printf("\nmocpy from a to b \n:");

	mocpy_from(from,to);

	printf("a = %s\nb = %s\n",a,b);
	
	return 0;
}


