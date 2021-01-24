#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/select.h>

#define BUF_SIZE	30

int main(int argc, char* argv[])
{
	fd_set reads, temps;
	int ret, str_len;
	char buf[BUF_SIZE];
	struct timeval timeout;

	FD_ZERO(&reads);
	FD_SET(0, &reads);

	while(1)
	{
		temps = reads;
		timeout.tv_sec=5;
		timeout.tv_usec=0;
		ret=select(1, &temps, 0, 0, &timeout);
	
		if(ret == -1)
		{
			printf("select() error! \n");
			break;
		}
		else if(ret == 0)
		{
			puts("timeout!!");
		}
		else
		{
			if(FD_ISSET(0, &temps))
			{
				str_len = read(0, buf, BUF_SIZE);
				buf[str_len] = 0;
				printf("message from console : %s", buf);
			}
		}
	}

	return 0;
}
