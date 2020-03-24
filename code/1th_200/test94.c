
/*
** �жϲ����Ƿ���һ���ؼ����б��е��κε���ƥ�䣬������ƥ�������ֵ,���û���ҵ�ƥ�䣬��������-1
*/

#include <string.h>
#include <stdio.h>

int lookup_keyword(char const *const desired_word,char const *keyword_table[],int const size)
{
	char const **kwp;

	/*
	** ���ڱ��е�ÿ������
	*/

	for (kwp = keyword_table;*kwp != NULL;kwp ++)
	{
		/*
		** ���������������������ҵĵ���ƥ�䣬�������ڱ��е�λ��.
		*/
		
		if (strcmp(desired_word,*kwp) == 0)
			return kwp - keyword_table;
		
			//printf("%s,%d\n",__FUNCTION__,__LINE__);
	}
		/*
		** û���ҵ�
		*/
		//printf("%s,%d\n",__FUNCTION__,__LINE__);
		return -1;
}

int main(void)
{
	int ret;
	char const const words[10] = "while";
	char const *keyword_table[9] ={
			"do",
			"for",
			"if",
			"register",
			"return",
			"switch",
			"while",
		};
			
	ret = lookup_keyword(words,keyword_table, 100);
	printf("ret = %d\n",ret);
	return 0;
}



