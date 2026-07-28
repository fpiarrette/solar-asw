#!/bin/bash

# get positional arguments
iterative=$1

# obtain project base dir
script_dir=$(readlink -f $(pwd)/$(dirname "$0"))
project_dir=$script_dir

# create source dir
source_dir=${project_dir}/src

# create output dir
output_dir=${project_dir}/build
mkdir -p ${output_dir}

# set flags and command depending on execution mode
if [[ "$iterative" == "y" ]]; then
    echo "Iterative"
    flags=-it
    cmd=""
elif [[ "$iterative" == "n" ]]; then
    echo "Non iterative"
    flags=-t
    cmd="make clean all"
else
    echo "Non iterative"
    flags=-t
    cmd="make clean all"
fi

# launch make process
podman run ${flags} \
    -v "${project_dir}:/ws" \
    -w "/ws" \
    arm-poky-linux-gnueabi:latest \
    ${cmd}
