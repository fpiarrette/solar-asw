#!/bin/sh

# this script shall not be executed direclty, is intendeed to be called from main/parent script

target_ssh_password=ak-nord

source_file="$project_dir/$OUTPUT_DIR/$BINARY_NAME"
destination_dir=/home/admin

# send binary
sshpass -p "$target_ssh_password" scp $source_file admin@$SOLAR_TARGET_IP_ADDRESS:$destination_dir

# execute binary
sshpass -p "$target_ssh_password" ssh admin@$SOLAR_TARGET_IP_ADDRESS 'nohup $destination_dir/$BINARY_NAME &'
