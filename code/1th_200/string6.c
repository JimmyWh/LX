#include <stdio.h>

void copy_string(char from[],char to[])
{
	int i =0;
	
	while(from[i] != '\0')
	{
		to[i] = from[i];
		i++;
	}
	to[i] = '\0';
}


int main()
{
	char a[] = "I am teacher";
	char b[] = "You are a student.";
	char *from = a;
	char *to   = b;
	
	printf("string a = %s\nstring b = %s\n",a,b);

	printf("\n copy string a to string b:\n");

	copy_string(from,to);

	printf("string a = %s\n string b =%s\n",a,b);
	
	return 0;

}

