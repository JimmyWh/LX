
#include <stdio.h>
#include <stdlib.h>

FILE *stream;
int main()
{
	int i = 10;
	double fp = 1.5;
	char s[] = "this is  a string";
	char c = '\n';
	stream = fopen("fprint.out","w");
	fprintf(stream,"%s%c",s,c);
	fprintf(stream,"%d\n",i);
	fprintf(stream,"%f\n",fp);
	fclose(stream);
	return 0;

}
