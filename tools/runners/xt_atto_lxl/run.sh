#!/bin/sh

# obtain project base dir
script_dir=$(readlink -f $(pwd)/$(dirname "$0"))
project_dir=$script_dir/../..

. $project_dir/tools/net/validate.sh
. $project_dir/tools/runners/validate.sh

binary_name=main
source_file=$project_dir/build/xt_atto_lxl/debug/$binary_name
destination_dir=/home/admin
target_ssh_password=ak-nord

sshpass -p "$target_ssh_password" scp $source_file admin@$SOLAR_TARGET_IP_ADDRESS:$destination_dir

sshpass -p "$target_ssh_password" ssh admin@$SOLAR_TARGET_IP_ADDRESS 'nohup $destination_dir/$binary_name &'
