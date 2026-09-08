#!/bin/sh

# obtain project base dir
script_dir=$(readlink -f $(pwd)/$(dirname "$0"))
project_dir=$script_dir/../..

. $project_dir/tools/launcher/validate.sh

. $project_dir/tools/launcher/$PLATFORM/run.sh
