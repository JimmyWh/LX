#include <stdio.h>

void reverse_string(char *str)
{
	char *last_char;

	/*
	** ��last_char����Ϊָ���ַ��������һ���ַ�.
	*/

	printf("%s,%d\n",__FUNCTION__,__LINE__);
	
	for (last_char = str; *last_char != '\0';last_char++)
		;

	last_char--;
	
	printf("%s,%d\n",__FUNCTION__,__LINE__);	

	/*
	** ����str��last_char ָ����ַ���Ȼ��strǰ��һ����last_char ����һ����
	** ������ָ��������������֮ǰ�ظ��������.
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
