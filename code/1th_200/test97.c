/*
** ���ַ���s1�в����ַ���s2���ұ߳��ֵ�λ�ã�������һ��ָ���λ�õ�ָ��.
*/

#include <string.h>
#include <stdio.h>

char *my_strrstr(char const *s1,char const *s2)
{
	register char *last;
	register char *current;

	/*
	** ��ָ���ʼ��Ϊ�����Ѿ��ҵ��ĵ�ǰһ��ƥ��λ��.
	*/
	last = NULL;

	/*
	** ֻ�ڵ�2���ַ�����Ϊ��ʱ�Ž��в���,���S2Ϊ�գ�����NULL
	*/

	if (*s2 != '\0')
	{
		/*
		** ����s2��s1�е�1�γ��ֵ�λ��.
		*/
		current = strstr(s1,s2);

		/*
		** ����ÿ���ҵ��ַ���ʱ����ָ��ָ��������ʼλ��.Ȼ����Ҹ��ַ�����һ��ƥ��λ��.
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
		/* ����ָ�������ҵ������һ��ƥ�����ʼλ�õ�ָ��. */
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


