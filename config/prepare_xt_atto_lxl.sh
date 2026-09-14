#!/bin/bash

# obtain project base dir
SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
PROJECT_DIR=$(readlink -f $SCRIPT_DIR/..)

export PROJECT_DIR
export PLATFORM="xt_atto_lxl"

. ${PROJECT_DIR}/config/prepare_common.sh

export PLATFORM_ID=$PLATFORM_TARGET
export SOLAR_TARGET_IP_ADDRESS="192.168.1.145"
export DOCKER_IMAGE_NAME=arm-poky-linux-gnueabi:latest
