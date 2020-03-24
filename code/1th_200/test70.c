#include <stdio.h>

int main(void)
{
	int ch;
	while ((ch = getchar()) != EOF)
	{
		if ((ch >= 'A') && (ch <= 'Z') || (ch >= 'a') && (ch <= 'z'))
		{
			ch += 13;
			getchar();
			putchar(ch);
			putchar('\n');
		}
		else
		{
			putchar(ch);
			getchar();
			putchar('\n');
		}
	}
	return 0;
}
