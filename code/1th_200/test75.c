#include <stdio.h>

#define TRUE  1
#define FALSE 0

int find_char(char **strings,char value)
{
	/*
	** 我们当前正在查找的字符串
	*/
	char *string;

	/*
	** 对于列表中的每个字符串
	*/

	while ((string = *strings++) != NULL)
	{
		/*
		** 观察字符串中的每个字符，看看它是不是我们需要查找的那个
		*/

		while (*string != '\0')
		{
			if (*string++ == value)
				return TRUE;
		}
	}

	return FALSE;

}

