/* poll */
#include <stdio.h>
#include <string.h>
#include <poll.h>
/*
#define POLLIN  0x0001
#define POLLPRI 0x0002
*/
void poll_success(int fd,char *buf){
    int ret;

    memset((void*)buf,0,11);
    ret = read(fd,(void*) buf,10);
    printf("ret = %d\n",ret);

    if(ret!=-1){
        printf("    buf = %s\n",buf);
    }
}

int main (int argc, char *argv[]){
    int fd=0;
    char buf[11];

    struct pollfd pollfds;
    int timeout=5000;
    pollfds.fd = fd;
    pollfds.events = POLLIN|POLLPRI; 
    while(1){
        switch(poll(&pollfds,1,timeout)){
            case -1:
                printf("poll error \n");
                break;
            case 0:
                printf("ret =0 \n");
                printf("time out \n");
                break;
            default:
                poll_success(fd,buf);
                break;
        }
        
    }
    return 0;
}
