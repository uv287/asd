#!/bin/bash

# Compile the ioctl driver
make 

# Load the ioctl driver
sudo insmod ioctl_driver.ko

# Compile the user space program
gcc app.c -o app

# Run the user space program
./app

# Remove the ioctl driver
sudo rmmod ioctl_driver

# Clean up
make -C /lib/modules/$(uname -r)/build M=$(pwd) clean
rm app