#include <sys/select.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void select_success(int fd,char *buf){
    int ret;
    memset((void*)buf,0,11); 
    ret = read(fd,(void*)buf,10);
    printf("ret = %d\n",ret);

    if(ret!=-1){
        printf("    buf = %s\n",buf);
    }
}

int main (int argc,char *argv[]){
    int fd=0,result;
    char buf[11];
    fd_set fds,fds_test;
    struct timeval timeout;

    FD_ZERO(&fds);
    FD_SET(fd,&fds);

    while(1){
        fds_test=fds;
        timeout.tv_sec = 2;
        timeout.tv_usec = 500000;
        result = select(FD_SETSIZE,&fds_test,(fd_set *)0,(fd_set *)0,&timeout);
        switch(result){
            case 0:
                printf("ret = 0 \n");
                printf("time out \n");
                break;
            case -1:
                printf("select");
                exit(1);
            default:
                if(FD_ISSET(0,&fds_test)){
                    select_success(fd,buf);
                }
        }
    }

    return 0;
}
