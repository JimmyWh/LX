
#include <stdio.h>

/*
** ��һ�������ַ���ת��Ϊһ������
*/

int ascii_to_integer(char *string)
{
	int value;

	value = 0;

	/*
	** ������ַ������ַ�ת��Ϊ����
	*/
	
	while (*string >= '0' && *string <= '9')
	{
		value *= 10;
		value += *string - '0';
		string ++;
	}

	/*
	** ������:�����������һ���������ַ�����ֹ���ѽ������Ϊ0.
	*/

	if (*string != '\0')
		value = 0;

	return value;
	
}


int main(void)
{
	char a[] = "23333334";
	printf("%d\n",ascii_to_integer(a));
}


