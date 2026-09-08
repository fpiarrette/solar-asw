#!/bin/bash

DEBUG=0

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

# obtain project base dir
export PLATFORM="xt_atto_lxl"
export DEBUG
export SOLAR_TARGET_IP_ADDRESS="192.168.1.145"
export SOLAR_TARGET_KILL_PORT="9090"
export SOLAR_TARGET_REST_PORT="8080"
export DOCKER_IMAGE_NAME=arm-poky-linux-gnueabi:latest
export BINARY_NAME=solar-asw
