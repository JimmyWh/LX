/*
** �ѱ�׼�����ȡ���ı�������
*/

#include <stdio.h>

//char *fgets(char *s, int size, FILE *stream);

#define MAX_LINE_LENGTH 1024 //�ҿ��Ը��Ƶ����

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

