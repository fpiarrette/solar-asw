#!/bin/sh

# this script shall not be executed direclty, is intendeed to be called from main/parent script

export TARGET_SSH_PASSWORD=ak-nord
export INSTALLATION_DIR=/home/admin
export INSTALLATION_NAME=solar-asw
export SOURCE_FILE="$PROJECT_DIR/$OUTPUT_DIR/$PACK_NAME"
export DESTINATION_DIR=$INSTALLATION_DIR/$INSTALLATION_NAME
