#!/bin/bash

DEBUG=0

# reset getopts
OPTIND=1

show_help()
{
    echo "$0 [-d] [-h]"
    echo "\t[-d] debug version"
    echo "\t[-h] show this help"
}

while getopts "h?d" opt; do
  case "$opt" in
    h|\?)
      show_help
      exit 0
      ;;
    d)
      DEBUG=1
      ;;
  esac
done

export PLATFORM_HOST=1
export PLATFORM_TARGET=2
export SOLAR_TARGET_KILL_PORT="9090"
export SOLAR_TARGET_REST_PORT="8080"
export BINARY_NAME=solar-asw
export PACK_NAME=solar-asw.tar

if [ $DEBUG -eq 0 ]
then
  OUTPUT_DIR="build/$PLATFORM/release"
else
  OUTPUT_DIR="build/$PLATFORM/debug"
fi

export OUTPUT_DIR
export DEBUG