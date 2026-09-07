#!/bin/bash

# obtain project base dir
script_dir=$(readlink -f $(pwd)/$(dirname "$0"))
project_dir=$script_dir

unset SOLAR_TARGET_IP_ADDRESS
echo -n "SOLAR target IP address: " 
read SOLAR_TARGET_IP_ADDRESS
export SOLAR_TARGET_IP_ADDRESS

unset SOLAR_TARGET_KILL_PORT
echo -n "SOLAR target kill port: "
read SOLAR_TARGET_KILL_PORT
export SOLAR_TARGET_KILL_PORT

unset SOLAR_TARGET_REST_PORT
echo -n "SOLAR target REST port: " 
read SOLAR_TARGET_REST_PORT
export SOLAR_TARGET_REST_PORT
