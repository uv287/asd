#!/bin/bash

# Compile the ioctl driver
make 

# Load the ioctl driver
sudo insmod query_ioctl.ko

# Compile the user space program
gcc app.c -o app

# Run the user space program
./app

# Remove the ioctl driver
sudo rmmod query_ioctl

# Clean up
make clean
rm app