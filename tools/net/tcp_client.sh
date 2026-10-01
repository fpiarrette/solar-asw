#!/bin/sh

# obtain project base dir
script_dir=$(readlink -f $(pwd)/$(dirname "$0"))
project_dir=$(readlink -f $script_dir/../..)

# general environment validation
. $project_dir/config/validate.sh

echo "TCP client $SOLAR_TARGET_IP_ADDRESS:9000"

nc $SOLAR_TARGET_IP_ADDRESS 9000
