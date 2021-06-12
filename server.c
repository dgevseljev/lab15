#include "common.h"

int readfd; 

void alrm(int s){
    close(readfd);
    unlink(FIFO_NAME);
    printf("server timeout\n");
    exit(0);
}



int main(){
    
    int n;
    char buff[MAX_BUFF]; 
    clock_t now, start;

    signal(SIGALRM, alrm);
    alarm(30);
   
    printf("FIFO Server...\n");
    
    if(mknod(FIFO_NAME, S_IFIFO | 0666, 0) < 0){
        fprintf(stderr, "%s: Невозможно создать FIFO (%s)\n", __FILE__, strerror(errno));
        exit(-1);
    }

    if((readfd = open(FIFO_NAME, O_RDONLY)) < 0){
        fprintf(stderr, "%s: Невозможно открыть FIFO (%s)\n", __FILE__, strerror(errno));
        exit(-2);
    }
 
    while(read(readfd, buff, MAX_BUFF) > 0){
        printf("message from: %s\n", buff);
        if(write(1, buff, n) != n){
            fprintf(stderr, "%s: Ошибка вывода (%s)\n", __FILE__, strerror(errno));
            exit(-3);
        } 
    }
    

close(readfd);

    if(unlink(FIFO_NAME) < 0){
        fprintf(stderr, "%s: Невозможно удалить FIFO (%s)\n", __FILE__, strerror(errno));
        exit(-4);
    }
    exit(0);
}