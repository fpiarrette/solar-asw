#!/bin/sh

# obtain project base dir
script_dir=$(readlink -f $(pwd)/$(dirname "$0"))
project_dir=$script_dir

curl -X GET http://localhost:8080/statistic

echo ""
