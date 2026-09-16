#!/bin/sh

GROUP_NAME=spi
USER=admin

# create GPIO group
addgroup $GROUP_NAME

# assign group to user
usermod -aG $GROUP_NAME $USER

# update volatile device information
# kernel patched up, following lines are not necesary
# echo spidev > /sys/class/spi_master/spi0/spi0.0/driver_override 
# echo spi0.0 > /sys/bus/spi/drivers/spidev/bind

# copy udev rules
cp 91-spidev.rules /etc/udev/rules.d
