#include <stdio.h>
#include <string.h>

void dollars(register char *dest,char const *src)
{
	int len;

	if (dest == NULL || src == NULL)
		return;

	*dest++ = '$';

	len = strlen(src);

	/*
	** ��������ַ����㹻��,���ƽ�������С������ߵ�����,���ʵ���λ�����
	** ���ţ�����ַ�������3������,��С����ǰ�������һ��'0'.
	*/

	if (len >= 3)
	{
		int i;
		for (i = len -2 ;i > 0;)
		{
			*dest++ = *src++;
			if (--i > 0 && i %3 == 0)
				*dest++ = ',';
		}	
	}else
		*dest++ = '0';

		/*
		** �洢С����,Ȼ��洢��src����ʣ�������,���'src'�е���������2����
		** �֣���'0'���꣬Ȼ����'dest'�����NULL��ֹ��.
		*/

		*dest++ = '.';
		*dest++ = len < 2 ? '0' :*src++;
		*dest++ = len < 1 ? '0' :*src;
		*dest = 0;
	
}


int main()
{
	char const *str = "12";
	char des[20];
	dollars(des,str);
	printf("%s\n",des);
	return 0;
	
}

