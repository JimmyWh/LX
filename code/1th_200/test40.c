#include <stdio.h>
int main(void)
{
	FILE *FSPOINTER;
	char STRBUFF[16] = "Hello world.";
	FSPOINTER = fopen("HELLO.TXT","w+");
	fprintf(FSPOINTER,"%s",STRBUFF);
	return 0;
	
}