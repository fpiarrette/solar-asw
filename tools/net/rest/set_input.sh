#!/bin/sh

# obtain project base dir
script_dir=$(readlink -f $(pwd)/$(dirname "$0"))
project_dir=$(readlink -f $script_dir/../../..)

# general environment validation
. $project_dir/config/validate.sh

# GET → read information
# POST → create a resource or trigger an action
# PUT → fully replace resource configuration
# PATCH → partialy change resource configuration
# DELETE → delete a resource

echo "setting config to $SOLAR_TARGET_IP_ADDRESS:$SOLAR_TARGET_REST_PORT"

CHANNEL=$1

BODY='{"channel":'${CHANNEL}'}'

curl -i -X PATCH http://$SOLAR_TARGET_IP_ADDRESS:$SOLAR_TARGET_REST_PORT/api/input -H "Content-Type: application/json" -d ${BODY} --output -

echo ""
