#ifndef DR_DOOM_H
#define DR_DOOM_H

#include <linux/ioctl.h>

typedef struct
{
    pid_t child_pid;
    pid_t new_parent_pid;
} ioctl_arg_t;

#define IOCTL_CHANGE_PARENT _IOW('i', 1, ioctl_arg_t *)

#endif