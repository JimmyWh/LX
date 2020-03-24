
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <poll.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char **argv)
{	
	int fd;
	int val = 1;
	
	fd = open("/dev/led", O_RDWR);
	if (fd < 0)
	{
		printf("can't open!\n");
		return -1; 
	}
	if (argc !=2)
	{
		printf("Usage :\n");
		printf("%s <on|off>\n",argv[0]);
		return 0;
	}
	
	if (strcmp(argv[1],"on") == 0)
	{
		printf("%s,%d\n",__FUNCTION__,__LINE__);
		val =1;
	}
	else
	{
		printf("%s,%d\n",__FUNCTION__,__LINE__);
		val = 0;
	}
	write(fd,&val,4);
	return 0;
}

