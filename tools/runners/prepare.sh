#!/bin/bash

# obtain project base dir
script_dir=$(readlink -f $(pwd)/$(dirname "$0"))
project_dir=$script_dir/../..

unset PLATFORM
echo -n "SOLAR target platform: " 
read PLATFORM
export PLATFORM
