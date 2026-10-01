#!/bin/sh

# obtain project base dir
script_dir=$(readlink -f $(pwd)/$(dirname "$0"))
project_dir=$(readlink -f $script_dir/../..)

# general environment validation
. $project_dir/config/validate.sh

echo "TCP server $SOLAR_TARGET_IP_ADDRESS:9500"

nc -l $SOLAR_TARGET_IP_ADDRESS 9500
