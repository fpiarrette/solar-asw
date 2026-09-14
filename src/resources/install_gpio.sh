#!/bin/sh

GROUP_NAME=gpio
USER=admin

# create GPIO group
addgroup $GROUP_NAME

# assign group to user
usermod -aG $GROUP_NAME $USER

# copy udev rules
cp 90-gpio.rules /etc/udev/rules.d

