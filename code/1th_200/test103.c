#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char const whitespace[] = "\f\t\v";

int main()
{
	char buffer[101];
	int count;
	printf("%s,%d\n",__FUNCTION__,__LINE__);
	
	count = 0;

	/*
	** �����ı��У�ֱ������EOF.
	*/

	while (gets(buffer))
	{

	   printf("%s\n",buffer);
	   char *word;

	   /*
	   ** �ӻ����������ȡ����,ֱ���������ڲ����е���.
	   */

	   for (word = strtok(buffer,whitespace);
	   			word != NULL;
				word = strtok(NULL,whitespace))
	   	{
			if (strcmp(word,"the") == 0)
				count += 1;
			
			printf("%s,%d,count = %d\n",__FUNCTION__,__LINE__,count);
		}
		printf("%s,%d\n",__FUNCTION__,__LINE__);
	}

	printf("%d\n",count);
			
	return EXIT_SUCCESS;

}
