/*
** ����ÿ���ļ��������������е��ļ�
*/
#include <stdlib.h>
#include <stdio.h>

int main(int arc,char **argv)
{
	int exit_status = EXIT_SUCCESS;
	FILE *input;

	/*
	** �����и�����ļ���ʱ....
	*/
	while (*++argv != NULL)
	{
		/*
		** ��ͼ������ļ�.
		*/
		input = fopen(*argv,"r");
		if (input == NULL)
		{
			perror(*argv);
			exit_status = EXIT_FAILURE;
			continue;
		}

		/*
		** �����ﴦ������ļ�...
		*/

		/*
		** �ر��ļ�(�������ﲻ�ᷢ��ʲô����.)
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

