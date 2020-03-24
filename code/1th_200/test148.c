#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>


//int sprintf(char *str, const char *format, ...);

static int write_file(char *path,unsigned char *buf,int buf_size)
{
	int ret_size = 0;
	int dumpfd = open(path,O_CREAT|O_RDWR|O_TRUNC,0777);
	
	printf("%s %d\n",__FUNCTION__,__LINE__);
	if (dumpfd < 0)
	{
		printf("open file %s failed: %s ",path,strerror(errno));
		return dumpfd;
	}
	do{
		ret_size = write(dumpfd,buf,buf_size);
	}while (ret_size != buf_size);

	close(dumpfd);
	
	printf("%s %d\n",__FUNCTION__,__LINE__);
	
	return ret_size;

}

int main()
{
	int ret;
	int i;
	char file_name[50] = {0};
	
	printf("%s %d\n",__FUNCTION__,__LINE__);
	for (i =0; i < 5; i++)
	{	
		printf("%s %d,i = %d\n",__FUNCTION__,__LINE__,i);
		//sprintf(file_name,"/home/liangzq/wu_lx/%d_bin",i);
		ret = write_file("/home/liangzq/wu_lx/bin", (unsigned char *)4, sizeof(int));
		if (ret < 0)
		{
			printf("write_file error!\n");
			return ret;
		}
	}
	
	printf("%s %d\n",__FUNCTION__,__LINE__);
	return 0;
}

