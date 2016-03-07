#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>

#define BUF_SIZE 16*1024
int main()
{
	int file,res;
	char buf[BUF_SIZE];	
	ssize_t size;
	//Opening file
	file = open("test.txt",O_RDONLY);
	if(file<0){perror("Opening file");}
	
	//File descriptors:
	// 0 --> stdin
	// 1 --> stdout
	// 2 --> stderr

	while((size = read(file,&buf,BUF_SIZE))>0)
		write(1,&buf,size);

	return 0;

}
