#!/bin/sh

# this script shall not be executed direclty, is intendeed to be called from main/parent script

. $PROJECT_DIR/tools/launcher/xt_atto_lxl/config.sh

# this step is temporarely ommited
# the idea is to launch solar-asw in second plane and use sys log as logging
#
# sshpass -p "$target_ssh_password" ssh admin@$SOLAR_TARGET_IP_ADDRESS 'nohup $destination_dir/$BINARY_NAME &'
