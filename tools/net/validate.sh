#!/bin/sh

# obtain project base dir
script_dir=$(readlink -f $(pwd)/$(dirname "$0"))
project_dir=$script_dir/../..

if [ ! -n "$SOLAR_TARGET_IP_ADDRESS" ]
then
  echo "You have to prepare network environment first!"
  exit -1
fi

if [ ! -n "$SOLAR_TARGET_KILL_PORT" ]
then
  echo "You have to prepare network environment first!"
  exit -1
fi

if [ ! -n "$SOLAR_TARGET_REST_PORT" ]
then
  echo "You have to prepare network environment first!"
  exit -1
fi
