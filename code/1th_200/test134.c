/*
** һ����ӡ�������в����ĳ���.
*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc,char **argv)
{
	/*
	** ��ӡ����,ֱ������NULLָ��(δʹ��argc),������������.
	*/

	while (*++argv != NULL)
		printf("%s\n",*argv);
	
	return EXIT_SUCCESS;
}
