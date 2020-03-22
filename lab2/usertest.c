#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#define DEVFILE "/dev/testdevice"

int open_file(void){
	int fd ;
	fd = open(DEVFILE, O_RDWR);
	if(fd == -1){
		perror("open");
	}
	return (fd);
}

void close_file(int fd ){
	if(close(fd) != 0){
		perror("close");
	}
}

void read_file(int fd){
	char buf[100],*p;
	ssize_t ret;
	ret = read(fd,buf,sizeof(buf));
	
	if(ret!=-1){
		p=buf;
		while(*p){
			printf("%c",*p++);
		}
	}else{
		perror("read");
	}
	printf("\n");
}

void write_file(int fd, const char *val){
	ssize_t ret;
	ret = write(fd,val,9);
	if(ret==-1){
		perror("write");
	}
}

void menu(void){
	printf("\n");
	printf("r = read from device\n");
	printf("w = write to device\n");	
	printf("q = quit\n");
	printf("enter to command:\n");
}

void write_menu(int fd){
	char buf[100];
	printf("device:\n");	
	scanf("%s",buf);
	write_file(fd,buf);
}
	
int main(void){
	int fd = open_file(); 
	char cmd;
	int exit =1;	
	while(exit){
		menu();
		scanf(" %c",&cmd);
		switch (cmd){
			case 'w':
				write_menu(fd);
				break;
			case 'r': 
				read_file(fd);
				break;
			case 'q':
				exit=0;
				break;
		}
	}
	close_file(fd);
	return 0;
}

