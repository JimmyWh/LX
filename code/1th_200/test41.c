#include <stdio.h>
int main()
{
	FILE *in,*out;
	in = fopen("HELLO.TXT","rt");
	printf("[wh]%d\n",__LINE__);
	if (in == NULL)
	{
		fprintf(in,"can not open inputfile.\n");
		return 1;
	}
	out = fopen("a.TXT","wt");
	if (out == NULL)
	{
		fprintf(out,"can not open outputfile.\n");
		return 1;
	}
	printf("[wh]%d\n",__LINE__);
	while (!feof(in))
	{
		printf("[wh]%d\n",__LINE__);
		fputc(fgetc(in),out);
	}	
	fclose(in);
	fclose(out);
	return 0;


}