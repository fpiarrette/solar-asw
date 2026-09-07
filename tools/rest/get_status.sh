#!/bin/sh

# obtain project base dir
script_dir=$(readlink -f $(pwd)/$(dirname "$0"))
project_dir=$script_dir/../..

. $project_dir/tools/rest/validate.sh

echo "getting status from $SOLAR_TARGET_IP_ADDRESS:$SOLAR_TARGET_REST_PORT"

curl -X GET http://$SOLAR_TARGET_IP_ADDRESS:$SOLAR_TARGET_REST_PORT/status

echo ""
