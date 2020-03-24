#include <stdio.h>

void reverse_string(char *str)
{
	char *last_char;

	/*
	** 把last_char设置为指向字符串的最后一个字符.
	*/

	printf("%s,%d\n",__FUNCTION__,__LINE__);
	
	for (last_char = str; *last_char != '\0';last_char++)
		;

	last_char--;
	
	printf("%s,%d\n",__FUNCTION__,__LINE__);	

	/*
	** 交换str和last_char 指向的字符，然后str前进一步，last_char 后退一步，
	** 在两个指针相遇或擦肩而过之前重复这个过程.
	*/

	
	printf("%s,%d,str = %s\n",__FUNCTION__,__LINE__,str);
	#if 1
	while (str < last_char)
	{
		char temp;
		temp = *str;
		*str++ = *last_char;
		*last_char-- = temp;
	}
	#endif
	printf("%s,%d\n",__FUNCTION__,__LINE__);
}


int main(void)
{
	//char *mystr  = "I love you.";
	char  mystr[] = "wo ai ni da wei.";
	reverse_string(mystr);
	printf("mystr = %s\n",mystr);
	
	return 0;
}
