
/*
** ���������в���
*/
#include <stdio.h>
#define TRUE 1

/*
** ִ��ʵ������ĺ�����ԭ��.
*/

void process_standard_input(void);
void process_file(char *file_name);

/*
** ѡ���־,ȱʡ��ʼ��ΪFALSE.
*/

int option_a,option_b; //etc

void main(int argc,char **argv)
{
	/*
	** ����ѡ�����:������һ����������������Ƿ�һ����˿�ͷ
	*/
	while (*++argv != NULL && **argv == '-')
	{
		/*
		** ����˺������ĸ.
		*/

		switch (*++*argv)
		{
			case 'a':
				option_a = TRUE;
				break;
			
			case 'b':
				option_b = TRUE;
				break;
			
			//etc
		}
	}
	
	/*
	** �����ļ�������.
	*/

	if (*argv == NULL)
		process_standard_input();
	else
		{
			do{
				process_file(*argv);
			}while(*++argv != NULL);
		}

}

