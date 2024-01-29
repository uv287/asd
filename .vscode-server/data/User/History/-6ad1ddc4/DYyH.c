#include<stdio.h>

#define VIRT_TO_PHYS _IO('q', 1)
#define CHANGE_VALUE _IO('q', 2)

typedef struct data_base
{
    unsigned long val,va,pa;
    int data;
}

int main(int argc, int argv[])
{
    char *f_name = "/dev/query_ioctl";
    int *n = malloc(sizeof(int));

    if(!n)
    {
        printf("Error to allocate memory to the data");
        return -1;
    }

}