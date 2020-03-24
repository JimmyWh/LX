#include <stdlib.h>
#include <stdio.h>
#include <string.h>

size_t my_strlcpy(char *des,const char *src,size_t length)
{
	int i = 0;
	for (i=0;src[i] != '\0' && i < length -1;i++)
	{
		des[i] = src[i];
	}
	des[i] = '\0';
	return strlen(src);
}

void print_buff(char *str,int length)
{
	int i;
	for (i =0; i < length;i++)
	{
		printf("buf[%d] = %c,%d\n",i,str[i],str[i]);
	}
}

int main(int argc,char *argv[])
{
	char buf[11] = {0};
	int ret;
	ret = my_strlcpy(buf, "helloworld", sizeof(buf));
	printf("%s,ret : %d\n",buf,ret);
	print_buff(buf,sizeof(buf));
	printf("---------------------------\n");
	ret = my_strlcpy(buf, "test", ret);
	print_buff(buf, sizeof(buf));
	return 0;
}

