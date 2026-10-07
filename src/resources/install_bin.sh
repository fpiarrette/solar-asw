#!/bin/sh

# run level
RL=$1

B=solar-asw
I=/opt/solar
D=/etc/init.d

# copy binary
mkdir $I
cp $B $I
cp $B.json $I

# SysV is assumed
# SOLAR scipt to /etc/init.d
cp $B.sh $D
chmod +x $D/$B.sh

# create simbolic link for desired run level
ln -s $D/$B.sh /etc/rc${RL}.d/S99_$B
