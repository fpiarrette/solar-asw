#!/bin/sh

# obtain project base dir
script_dir=$(readlink -f $(pwd)/$(dirname "$0"))
project_dir=$script_dir/../..

if [ ! -n "$PLATFORM" ]
then
  echo "You have to prepare running environment first!"
  exit 1
fi
