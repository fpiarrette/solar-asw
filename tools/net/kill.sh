#!/bin/sh

# obtain project base dir
script_dir=$(readlink -f $(pwd)/$(dirname "$0"))
project_dir=$(readlink -f $script_dir/../..)

# general environment validation
. $project_dir/config/validate.sh

echo "sending kill $SOLAR_TARGET_IP_ADDRESS:$SOLAR_TARGET_KILL_PORT"

echo "kill" | nc -q 0 $SOLAR_TARGET_IP_ADDRESS $SOLAR_TARGET_KILL_PORT
