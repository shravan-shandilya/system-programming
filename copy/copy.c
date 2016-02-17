#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>

#define BUF_SIZE 16*1024
int main(int argc,char **argv)
{
	char *source_file;
	char *destination_file;
	int option,s_fd,d_fd,count;
	opterr = 0;
	char buf[BUF_SIZE];
	while((option = getopt(argc,argv,"s:d:"))!=-1)
	{
		switch(option)
		{
			case 's':
				source_file = optarg;
				break;
			case 'd':
				destination_file = optarg;
				break; 
		}

	}

	s_fd = open(source_file,O_RDONLY);
	perror("Opening source_file");

	d_fd = open(destination_file,O_RDWR|O_CREAT,0644);
	perror("Opening destination_file");

	while((count = read(s_fd,&buf,BUF_SIZE))>0)
		write(d_fd,&buf,count);

	close(s_fd);
	close(d_fd);
}
