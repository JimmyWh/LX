/*
** ��һ���ӱ�׼�����ȡ������ת��Ϊ����.
*/
#include <stdio.h>
#include <ctype.h>

long read_int()
{
	int value;
	int ch;
	value = 0;

	/*
	** ת���ӱ�׼������������,�����ǵõ�һ���������ַ�ʱ��ֹͣ.
	*/
	while ((ch = getchar()) != EOF && isdigit(ch))
	{
		value *= 10;
		value += ch - '0';
	}

	/*
	** �ѷ������ַ��˻ص�����.�������Ͳ��ᶪʧ.
	*/
	ungetc(ch,stdin);
	return value;

}


int main(int argc,char **argv)
{
	printf("value : %ld\n",read_int());
	return 0;
}

