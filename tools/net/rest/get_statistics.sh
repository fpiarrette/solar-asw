#!/bin/sh

# obtain project base dir
script_dir=$(readlink -f $(pwd)/$(dirname "$0"))
project_dir=$(readlink -f $script_dir/../../..)

# general environment validation
. $project_dir/config/validate.sh

echo "getting statistics from $SOLAR_TARGET_IP_ADDRESS:$SOLAR_TARGET_REST_PORT"

curl -X GET http://$SOLAR_TARGET_IP_ADDRESS:$SOLAR_TARGET_REST_PORT/statistic

echo ""
