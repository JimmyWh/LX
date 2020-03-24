
/*
** 判断参数是否与一个关键字列表中的任何单词匹配，并返回匹配的索引值,如果没有找到匹配，函数返回-1
*/

#include <string.h>
#include <stdio.h>

int lookup_keyword(char const *const desired_word,char const *keyword_table[],int const size)
{
	char const **kwp;

	/*
	** 对于表中的每个单词
	*/

	for (kwp = keyword_table;*kwp != NULL;kwp ++)
	{
		/*
		** 如果这个单词与我们所查找的单词匹配，返回它在表中的位置.
		*/
		
		if (strcmp(desired_word,*kwp) == 0)
			return kwp - keyword_table;
		
			//printf("%s,%d\n",__FUNCTION__,__LINE__);
	}
		/*
		** 没有找到
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



