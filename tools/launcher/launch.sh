#!/bin/sh

# obtain project base dir
script_dir=$(readlink -f $(pwd)/$(dirname "$0"))
project_dir=$(readlink -f $script_dir/../..)

# general environment validation
. $project_dir/config/validate.sh

#specific run depending on $PLATFORM
. $project_dir/tools/launcher/$PLATFORM/launch.sh
