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
	** 如果数字字符串足够长,复制将出现在小数点左边的数字,在适当的位置添加
	** 逗号，如果字符串短于3个数字,在小数点前面再添加一个'0'.
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
		** 存储小数字,然后存储‘src’中剩余的数字,如果'src'中的数字少于2个数
		** 字，用'0'填完，然后在'dest'中添加NULL终止符.
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

