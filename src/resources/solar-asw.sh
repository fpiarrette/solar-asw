#!/bin/sh

A=solar-asw
D=/opt/solar
# provide as argument JSON configuration file
F="-c $D/$A.json"

# full execution path
P="$D/$A $F"

case "$1" in
    start)
        $P &
        ;;
    stop)
        killall $A
        ;;
    restart)
        killall $A
        $P &
        ;;
esac

exit 0
