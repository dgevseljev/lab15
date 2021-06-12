#include "common.h"
#define MESSAGE "Hello Server!!!\n"
int main(){
    int writefd; /* дескриптор для записи в FIFO */
    int msglen;
    char msg[10];
    int pid;

    pid = getpid();
    sprintf(msg,"%d\n",pid);
    
    if((writefd = open(FIFO_NAME, O_WRONLY)) < 0){
        fprintf(stderr, "%s: Невозможно открыть FIFO (%s)\n", __FILE__, strerror(errno));
        exit(-1);
    }
    printf("%d has connect\n", pid);
    
    msglen = strlen(msg);
    while (write(writefd, msg, msglen) == msglen){
        sleep(5);
    }

    close(writefd);
    exit(0);
}