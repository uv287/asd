#!/bin/bash

# Compile the ioctl driver
make 

# Load the driver
sudo insmod query_ioctl.ko

# Compile the user program
gcc app.c -o app

# Run the user program
sudo ./app

# Remove the driver
sudo rmmod query_ioctl
