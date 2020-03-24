/*
** 一个打印其命令行参数的程序.
*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc,char **argv)
{
	/*
	** 打印参数,直到遇到NULL指针(未使用argc),程序名被跳过.
	*/

	while (*++argv != NULL)
		printf("%s\n",*argv);
	
	return EXIT_SUCCESS;
}
