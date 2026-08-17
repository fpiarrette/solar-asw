#!/bin/sh

# obtain project base dir
script_dir=$(readlink -f $(pwd)/$(dirname "$0"))
project_dir=$script_dir

# reset getopts
OPTIND=1

# initialize varaibles
flags="-t"
cmd="make clean all"

# create source dir
source_dir=${project_dir}/src

# create output dir
output_dir=${project_dir}/build

show_help()
{
    echo "$0 [-i] [-s {/src}] [-o {/build}] [-h]"
}

while getopts "h?is:o:" opt; do
  case "$opt" in
    h|\?)
      show_help
      exit 0
      ;;
    i)
      flags="${flags} -i"
      cmd=""
      ;;
    s)
      source_dir="${project_dir}${OPTARG}"
      ;;
    o)
      output_dir="${project_dir}${OPTARG}"
      ;;
  esac
done

shift $((OPTIND-1))

[ "${1:-}" = "--" ] && shift

# info
echo "Source: ${source_dir}"
echo "Output: ${output_dir}"
echo "Command: ${cmd}"

# create output dir just in case make clean is not executed
mkdir -p ${output_dir}

# launch make process
podman run ${flags} \
    -v "${project_dir}:/ws" \
    -w "/ws" \
    arm-poky-linux-gnueabi:latest \
    ${cmd}
