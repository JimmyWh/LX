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
	** 读入文本行，直到发现EOF.
	*/

	while (gets(buffer))
	{

	   printf("%s\n",buffer);
	   char *word;

	   /*
	   ** 从缓冲区逐个提取单词,直到缓冲区内不再有单词.
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
