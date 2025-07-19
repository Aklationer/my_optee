#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>

#define IOC_MAGIC '\x66'
#define PLUSONE_IOC_ADDONE _IOWR(IOC_MAGIC, 0, int)

int main(){
    int fd = open("/dev/test", O_RDWR);

    if (fd < 0) {
        perror("open");
        return -1;
    }

    int data = 10;

    printf("data before ioctl %d\n",data);

    if(ioctl(fd,PLUSONE_IOC_ADDONE,&data) == -1){
        perror("ioctl");
        close(fd);
        return -1;
    }

    printf("data after ioctl %d\n",data);
    close(fd);
    return 0;
}