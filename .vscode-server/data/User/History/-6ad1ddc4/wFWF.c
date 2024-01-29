#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/ioctl.h>

#define VIRT_TO_PHYS _IO('q', 1)
#define CHANGE_VALUE _IO('q', 2)

typedef struct
{
    unsigned long val,va,pa;
    int data;
}data_base;

int main(int argc, int argv[])
{
    char *f_name = "/dev/query_ioctl";
    int *n = malloc(sizeof(int));

    if(!n)
    {
        printf("Error to allocate memory to the data");
        return -1;
    }
    *n=6;

    int fd = open(f_name,O_RDWR);
    if(fd<0)
    {
        printf("Error to open the file");
    }
    printf("Your Virtual Address : %lu \n Data : %d", n, *n);

    data_base db;
    db.va=(unsigned long)n;
    
    if(ioctl(fd,VIRT_TO_PHYS,&db) < 0)
    {
        printf("Error to find out the physical address");
        close(fd);
        free((n));
        return -1;
    }

    if(ioctl(fd,CHANGE_VALUE,&db) < 0)
    {
        printf("Error to change the value");
        close(fd);
        free((n));
        return -1;
    }

    printf("Updated value : %d\n",*n);

    free(n);
    clsoe(fd);
    return 0;

}