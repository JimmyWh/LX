
/*
** �ö�̬�����ڴ�����һ���ַ�����һ�ݿ���.ע��:���ó���Ӧ�ø����������
** ���Ƿ�ɹ�����!������������ó������κ���ϣ���ķ�ʽ�Դ���������Ӧ.
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char *strdup(char const *string)
{
	char *new_string;

	/*
	**�����㹻���ȵ��ڴ�,���ڴ洢�ַ��������Ľ�βNULL�ֽ�
	*/
	new_string = malloc(strlen(string) + 1);

	/*
	**������ǵõ��ڴ�,�͸����ַ���.
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
