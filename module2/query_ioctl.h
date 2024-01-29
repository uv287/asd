#ifndef QUERY_IOCTL_H
#define QUERY_IOCTL_H
#include <linux/ioctl.h>
 
typedef struct
{
    unsigned long pa,va;
    int data;
} data_base;
 

#define VIRT_TO_PHYS _IO('q', 1)
#define CHANGE_VALUE _IO('q', 2)
 
#endif