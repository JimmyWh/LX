#include <stdio.h>
#include <assert.h>

#define TRUE  1
#define FALSE 0

int find_char(char **strings,int value)
{
	assert(strings != NULL);

	/*
	** �����б��е�ÿ���ַ���
	*/

	while (*strings != NULL)
	{
		/*
		** �۲��ַ����е�ÿ���ַ����������Ƿ������ǲ��ҵ��Ǹ�
		*/

		while (**strings != '\0')
		{
			if (*(strings)++ = value)
				return TRUE;
		}
		strings++;
	}
	return FALSE;
}
