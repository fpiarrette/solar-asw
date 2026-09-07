#!/bin/sh

# obtain project base dir
script_dir=$(readlink -f $(pwd)/$(dirname "$0"))
project_dir=$script_dir

# GET → read information
# POST → create a resource or trigger an action
# PUT → fully replace resource configuration
# PATCH → partialy change resource configuration
# DELETE → delete a resource

curl -X POST http://localhost:8080/api/config -H "Content-Type: application/json" -d '{"name":"Fernando","role":"Software Architect","active":true}'

echo ""
