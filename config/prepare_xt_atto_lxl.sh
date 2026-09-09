#!/bin/bash

# obtain project base dir
script_dir=$(readlink -f $(pwd)/$(dirname "$0"))
project_dir=$(readlink -f $script_dir/..)

export PLATFORM="xt_atto_lxl"

. ${project_dir}/config/prepare_common.sh

export PLATFORM_ID=$PLATFORM_TARGET
export SOLAR_TARGET_IP_ADDRESS="192.168.1.145"
export DOCKER_IMAGE_NAME=arm-poky-linux-gnueabi:latest
