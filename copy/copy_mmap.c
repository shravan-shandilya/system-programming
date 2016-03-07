#include<fcntl.h>
#include<sys/types.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/mman.h>
int main()
{
	int fin,fout;
	char *src,*dst;
	size_t size;


	//Opening src file
	fin = open("test.txt",O_RDONLY);
	if(fin < 0){
		perror("Opening source file");
	}

	//Getting size of src file using lseek
	size = lseek(fin,0,SEEK_END);

	//Mapping src file to memory
	src = (char *)mmap(NULL,size,PROT_READ|PROT_WRITE,MAP_PRIVATE,fin,0);
	perror("Mapping source file");
	
	//Opening destination file
	fout = open("text.tst",O_RDWR|O_CREAT);
	if(fin<0){
		perror("Opening destinaltion file");
	}

	//Truncating the destination file using hte size of the src file
	if(ftruncate(fout,size)<0){
		perror("Truncating destination file");
	}

	//Mapping dest file
	dst =(char *) mmap(NULL,size,PROT_READ|PROT_WRITE,MAP_SHARED,fout,0);
	perror("Mapping destination file");


	//Copying content in memory
	memcpy(dst,src,size);
	perror("Copying");


	//Syncing content in memory to dst file
	msync(dst,size,MS_SYNC);
	perror("Syncing back to file");

	close(fin);
	close(fout);
	return 0;
}
