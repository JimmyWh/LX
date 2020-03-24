#include <stdio.h>
#include <string.h>

int main(void)
{
	char buf[] = "hello@boy@this@is@heima";
	char *temp = strtok(buf,"@");
	while (temp)
	{
		printf("%s ",temp);
		temp = strtok(NULL,"@");
	}
	printf("\n");
	return 0;
}

