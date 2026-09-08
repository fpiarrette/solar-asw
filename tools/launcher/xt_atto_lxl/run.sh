#!/bin/sh

# this script shall not be executed direclty, is intendeed to be called from main/parent script

destination_dir=/home/admin
target_ssh_password=ak-nord

if [ -z "$DEBUG" ]
then
  source_file=$project_dir/build/xt_atto_lxl/release/$BINARY_NAME
else
  source_file=$project_dir/build/xt_atto_lxl/debug/$BINARY_NAME
fi

# send binary
sshpass -p "$target_ssh_password" scp $source_file admin@$SOLAR_TARGET_IP_ADDRESS:$destination_dir

# execute binary
sshpass -p "$target_ssh_password" ssh admin@$SOLAR_TARGET_IP_ADDRESS 'nohup $destination_dir/$BINARY_NAME &'
