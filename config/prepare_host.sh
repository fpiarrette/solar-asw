#!/bin/bash

# obtain project base dir
script_dir=$(readlink -f $(pwd)/$(dirname "$0"))
project_dir=$(readlink -f $script_dir/..)

export PLATFORM="host"

. ${project_dir}/config/prepare_common.sh

export PLATFORM_ID=$PLATFORM_HOST
export SOLAR_TARGET_IP_ADDRESS="127.0.0.1"
export DOCKER_IMAGE_NAME=x86_64-pc-linux-gnu:latest
