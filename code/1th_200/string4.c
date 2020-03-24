#include <stdio.h>

void copy_string(char from[],char to[])
{
	int i =0;
	while (from[i] != '\0')
	{
		to[i] = from[i];
		i++;
	}
	
	to[i] = '\0';
}


int main()
{

	char a[] = "I am teacher .";
	
	char b[] = "You ara a student.";

	printf("String a= %s\nString b = %s\n",a,b);

	printf("copy string a to string b \n");
	
	copy_string(a, b);

	printf("String a = %s\nString b = %s\n",a,b);

	
	return 0;

}

