/*
** 把标准输入读取的文本行逐行
*/

#include <stdio.h>

//char *fgets(char *s, int size, FILE *stream);

#define MAX_LINE_LENGTH 1024 //我可以复制的最长行

void copylines(FILE *input,FILE *output)
{
	char buffer[MAX_LINE_LENGTH];

	printf("%s,%d\n",__FUNCTION__,__LINE__);
	while (fgets(buffer,MAX_LINE_LENGTH,input) != NULL)
	{	
			
			printf("%s,%d\n",__FUNCTION__,__LINE__);
			fputs(buffer,output);
	}
	
	printf("%s,%d\n",__FUNCTION__,__LINE__);
}

int main()
{
	FILE *file_input,*file_output;
	copylines(file_input, file_output);
	printf("%s,%d\n",__FUNCTION__,__LINE__);
	return 0;
}

