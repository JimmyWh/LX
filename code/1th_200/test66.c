#include <stdio.h>

int main(void)
{
	char  a1[] = "1234";  /* �����ַ�����˵sizeof ������ַ����м����ֽ�char����(1���ֽ�)                   */
	int   a2[4]; /* ��Ӧ������˵sizeof��int����(4�ֽ�) * 4��Ԫ�� = 16�ֽ�                	 */
	char *pc = "abc"; /* ����pcָ����˵sizeofΪ4���ֽ�  */
	printf("a1 = %d , a2 = %d, pc = %d\n",sizeof(a1),sizeof(a2),sizeof(pc));
}
