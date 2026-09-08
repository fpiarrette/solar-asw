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
export PLATFORM="host"
export DEBUG
export SOLAR_TARGET_IP_ADDRESS="127.0.0.1"
export SOLAR_TARGET_KILL_PORT="9090"
export SOLAR_TARGET_REST_PORT="8080"
export DOCKER_IMAGE_NAME=x86_64-pc-linux-gnu:latest
export BINARY_NAME=solar-asw
