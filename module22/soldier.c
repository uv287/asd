#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/ioctl.h>

// Include header or define the IOCTL call interface and device name
#include "dr_doom.h"
//**************************************************

int open_driver(const char *driver_name)
{

    int fd_driver = open(driver_name, O_RDWR);
    if (fd_driver == -1)
    {
        perror("ERROR: could not open driver");
    }

    return fd_driver;
}

void close_driver(const char *driver_name, int fd_driver)
{

    int result = close(fd_driver);
    if (result == -1)
    {
        perror("ERROR: could not close driver");
    }
}

int main(int argc, char **argv)
{

    if (argc != 2)
    {
        printf("Usage: %s <parent_pid>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    pid_t p_pid = atoi(argv[1]);
    pid_t slf_pid = getpid();

    // open ioctl driver
    const char *driver_name = "/dev/dr_doom";
    int fd_driver = open_driver(driver_name);

    // call ioctl with parent pid as argument to change the parent
    ioctl_arg_t a;
    a.new_parent_pid = p_pid;
    a.child_pid = slf_pid;

    int result = ioctl(fd_driver, IOCTL_CHANGE_PARENT, &a);
    if (result == -1)
    {
        printf("ERROR: ioctl  failed");
    }

    // close ioctl driver
    close_driver(driver_name, fd_driver);

    return EXIT_SUCCESS;
}