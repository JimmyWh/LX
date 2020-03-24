/*
** 在字符串s1中查找字符串s2最右边出现的位置，并返回一个指向该位置的指针.
*/

#include <string.h>
#include <stdio.h>

char *my_strrstr(char const *s1,char const *s2)
{
	register char *last;
	register char *current;

	/*
	** 把指针初始化为我们已经找到的当前一次匹配位置.
	*/
	last = NULL;

	/*
	** 只在第2个字符串不为空时才进行查找,如果S2为空，返回NULL
	*/

	if (*s2 != '\0')
	{
		/*
		** 查找s2在s1中第1次出现的位置.
		*/
		current = strstr(s1,s2);

		/*
		** 我们每次找到字符串时，让指针指向它的起始位置.然后查找该字符串下一个匹配位置.
		*/

		while (current != NULL)
		{
			last = current;
			current = strstr(last + 1,s2);
			printf("%s,%d,%s,%s\n",__FUNCTION__,__LINE__,current,last);
		}
		printf("%s,%d\n",__FUNCTION__,__LINE__);
	}

		printf("%s,%d\n",__FUNCTION__,__LINE__);
		/* 返回指向我们找到的最后一次匹配的起始位置的指针. */
		return last;
}


int main(void)
{
	char *plocation = NULL;
	char s1[] = "abcdefg";
	char *s2 = "def";
	plocation = my_strrstr(s1,s2);
	
	printf("%s,%d\n",__FUNCTION__,__LINE__);
	printf("%s\n",plocation);
	return 0;
}


