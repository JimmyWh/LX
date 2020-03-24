#include <stdio.h>
#if 0
int main()
{
	char ch1,ch2;
	scanf("%c",&ch1);
	scanf("%c",&ch2);
	printf("%d %d\n",ch1,ch2);
	return 0;	
}
#else
int main()
{
	char ch1,ch2;
	ch1 = getchar();
	ch2 = getchar();
	printf("%d %d\n",ch1,ch2);
	return 0;	
}
#endif

