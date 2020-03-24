#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int line =0;
	int ch;
	int at_begining = 1;

	while((ch = getchar()) != EOF)
	{
		if (at_begining)
		{
			at_begining = 0;
			line += 1;
			printf("%d ",line);
		}

		putchar(ch);
		if (ch == '\n')
				at_begining = 1;
	}
	return EXIT_SUCCESS;
	
}

