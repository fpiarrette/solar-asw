#!/bin/sh

# obtain project base dir
project_dir=$(readlink -f $script_dir/../../..)

# general environment validation
. $project_dir/config/validate.sh

# GET → read information
# POST → create a resource or trigger an action
# PUT → fully replace resource configuration
# PATCH → partialy change resource configuration
# DELETE → delete a resource

. $project_dir/tools/net/validate.sh

echo "setting config to $SOLAR_TARGET_IP_ADDRESS:$SOLAR_TARGET_REST_PORT"

curl -X POST http://$SOLAR_TARGET_IP_ADDRESS:$SOLAR_TARGET_REST_PORT/api/config -H "Content-Type: application/json" -d '{"name":"Fernando","role":"Software Architect","active":true}'

echo ""
