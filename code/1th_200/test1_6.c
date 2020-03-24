#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int ch;
	int brach;
	
	brach = 0;
	
	while((ch = getchar()) != EOF)
	{
		if (ch == '{')
				brach += 1;

		if (ch == '}')
			if (brach == 0)
				printf("Extra closing brace!\n");
			else
				brach -= 1;
	}
	if (brach > 0)
		printf("%d unmatched opening branch\n",brach);
	
	return EXIT_SUCCESS;
}
