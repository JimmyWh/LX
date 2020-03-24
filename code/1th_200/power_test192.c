
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/time.h>
#include <stdlib.h>

//int system(const char *command);

#define KEY_L			38
#define KEY_S			31
#define KEY_ENTER		28
#define KEY_LEFTSHIFT	42
#define EV_KEY			0x01


struct input_event {
	struct timeval time;
	unsigned short type;
	unsigned short code;
	int value;
};

int main(int argc,char **argv)
{
	int fd;	
	int ret;
	
	struct input_event event;

	if (argc != 2)
	{
		printf("Usage:\n");		
		printf("%s <dev>\n",argv[0]);
		return -1;
	}

	fd = open(argv[1],O_RDONLY);
	if (fd < 0)
	{
		printf("cannot open %s",argv[1]);
		return -1;
	}

	
	while (1)
	{
		ret = read(fd,&event,sizeof(event));
		if (ret != sizeof(event))
		{
			printf("cannot read! ret = %d\n",ret);
			return -1;
		}

		//L¼üËÉ¿ª
		if ( (event.type == EV_KEY) && (event.code == KEY_L) && (event.value == 0))
		{
			system("echo mem > /sys/power/state");
		}
		
	}
	
	return 0;
}

