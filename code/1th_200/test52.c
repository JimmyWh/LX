#include <stdio.h>
#include <stdlib.h>

int main()
{
	int fd;
	long dev;
	long offset;
	long length;
	char ch;
	double ts = 0.00000;
	if ((fd = fopen("data.txt","r")) < 0)
	{
		printf("open the file is error!\n");
		exit(0);
	}
	lseek(fd,0,SEEK_SET);

	while (5 == fscanf(fd,"%ld,%ld,%ld,%c,%lf\n",&dev,&offset,&length,&ch,&ts))
	{
		printf("%ld,%ld,%ld,%c,%lf\n",dev,offset,length,ch,ts);
	}
	close(fd);
	return 0;
}
