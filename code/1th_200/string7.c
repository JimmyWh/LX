#include <stdio.h>


#if 1
void copy_string(char *from,char *to)
{
	for (; *from != '\0' ; from++,to++)
	{
		*to = *from;
	}
	*to = '\0';
}
#else
void copy_string(char *from,char *to)
{
	while ((*to  = *from) != '\0')
	{
			to ++;
			from ++;
	}
}

#endif

int main()
{
	char *a = "I am a teacher.";
	
	char b[] = "You are a student.";

	char *p = b;

	//char *a1;

	//printf("%s \n",a1);
	
	printf("string a = %s,string b = %s\n",a,b);	

	printf("\n copy string a to string b:\n");

	copy_string(a,p);

	printf("string a = %s \nstring b = %s\n",a,b);
	
	return 0;

}


