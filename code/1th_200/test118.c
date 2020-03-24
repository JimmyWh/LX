
/*
** 用动态分配内存制作一个字符串的一份拷贝.注意:调用程序应该负责检查这块内
** 存是否成功分配!这样做允许调用程序以任何它希望的方式对错误作出反应.
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char *strdup(char const *string)
{
	char *new_string;

	/*
	**请求足够长度的内存,用于存储字符串和它的结尾NULL字节
	*/
	new_string = malloc(strlen(string) + 1);

	/*
	**如果我们得到内存,就复制字符串.
	*/
	if (new_string != NULL)
		strcpy(new_string,string);

	return new_string;

}

int main()
{
	char *a = "abc333333333";
	char  str[20];
	strcpy(str,a);
	printf("%s\n",str);
	return 0;
}
