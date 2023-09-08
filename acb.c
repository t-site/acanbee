#include<unistd.h>
#include<fcntl.h>
#include<time.h>
#include<stdlib.h>

int main(void)
{
	int rfd;
	struct timespec ts;
	char *p;
	rfd=open("/dev/urandom",O_RDONLY);
	if ( rfd == -1 )
		return 1;
	nice(-16);
	for(;;)
	{
		unsigned short size;
		unsigned char seconds;
		unsigned int nanosec;
		int i;
		read(rfd,&size,sizeof(unsigned short));
		p=calloc(size,sizeof(unsigned char));
		if( p != NULL )
		{
			for ( i=0;i < size ; i++ )
			{
				p[0]=p[i];
			}
			free(p);
		}
		read(rfd,&seconds,sizeof(unsigned char));
		seconds /= 64;
		nanosec=0;
		read(rfd,&nanosec,3);
		ts.tv_sec=seconds;
		ts.tv_nsec=nanosec;
		nanosleep(&ts,NULL);

	}
	close(rfd);
	return 0;
}
