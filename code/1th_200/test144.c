/*
** 把一串从标准输入读取的数字转换为整数.
*/
#include <stdio.h>
#include <ctype.h>

long read_int()
{
	int value;
	int ch;
	value = 0;

	/*
	** 转换从标准输入读入的数字,当我们得到一个非数字字符时就停止.
	*/
	while ((ch = getchar()) != EOF && isdigit(ch))
	{
		value *= 10;
		value += ch - '0';
	}

	/*
	** 把非数字字符退回到流中.这样它就不会丢失.
	*/
	ungetc(ch,stdin);
	return value;

}


int main(int argc,char **argv)
{
	printf("value : %ld\n",read_int());
	return 0;
}

