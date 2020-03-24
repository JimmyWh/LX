/*
** 处理每个文件名出现于命令行的文件
*/
#include <stdlib.h>
#include <stdio.h>

int main(int arc,char **argv)
{
	int exit_status = EXIT_SUCCESS;
	FILE *input;

	/*
	** 当还有更多的文件名时....
	*/
	while (*++argv != NULL)
	{
		/*
		** 试图打开这个文件.
		*/
		input = fopen(*argv,"r");
		if (input == NULL)
		{
			perror(*argv);
			exit_status = EXIT_FAILURE;
			continue;
		}

		/*
		** 在这里处理这个文件...
		*/

		/*
		** 关闭文件(期望这里不会发生什么错误.)
		*/
		if (fclose(input) != 0)
		{
			perror("fclose");
			exit(EXIT_FAILURE);
		}
		printf("%s,%d\n",__FUNCTION__,__LINE__);
	}
	
	return exit_status;


}

