#!/bin/bash

# obtain project base dir
SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
PROJECT_DIR=$(readlink -f $SCRIPT_DIR/..)

export PROJECT_DIR
export PLATFORM="host"

. ${PROJECT_DIR}/config/prepare_common.sh

export PLATFORM_ID=$PLATFORM_HOST
export SOLAR_TARGET_IP_ADDRESS="127.0.0.1"
export DOCKER_IMAGE_NAME=x86_64-pc-linux-gnu:latest
