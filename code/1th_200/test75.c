#include <stdio.h>

#define TRUE  1
#define FALSE 0

int find_char(char **strings,char value)
{
	/*
	** ���ǵ�ǰ���ڲ��ҵ��ַ���
	*/
	char *string;

	/*
	** �����б��е�ÿ���ַ���
	*/

	while ((string = *strings++) != NULL)
	{
		/*
		** �۲��ַ����е�ÿ���ַ����������ǲ���������Ҫ���ҵ��Ǹ�
		*/

		while (*string != '\0')
		{
			if (*string++ == value)
				return TRUE;
		}
	}

	return FALSE;

}

