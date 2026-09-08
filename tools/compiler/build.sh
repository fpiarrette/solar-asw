#!/bin/sh

# obtain project base dir
script_dir=$(readlink -f $(pwd)/$(dirname "$0"))
project_dir=$(readlink -f $script_dir/../..)

# reset getopts
OPTIND=1

# initialize varaibles
flags="-t"
cmd="make clean all"

# create source dir
workspace_dir="/ws"

source_dir=/src

# create output dir
output_dir=/build

optimization=0

hardening=0

show_help()
{
    echo "$0 [-i] [-s {/src}] [-o {/build}] [-c {\"make clean all\"}] [-z] [-e] [-h]"
    echo "\t[-i] interactive"
    echo "\t[-s {/src}] define source directory"
    echo "\t[-o {/build}] define output directory"
    echo "\t[-c {\"make clean all\"}] define command"
    echo "\t[-z] activate optimization"
    echo "\t[-e] include GCC hardening options"
    echo "\t[-h] show this help"
}

while getopts "h?is:o:c:ze" opt; do
  case "$opt" in
    h|\?)
      show_help
      exit 0
      ;;
    i)
      flags="${flags} -i"
      cmd="bash"
      ;;
    s)
      source_dir="${OPTARG}"
      ;;
    o)
      output_dir="${OPTARG}"
      ;;
    c)
      cmd="${OPTARG}"
      ;;
    z)
      optimization=1
      ;;
    e)
      hardening=1
      ;;
  esac
done

shift $((OPTIND-1))

[ "${1:-}" = "--" ] && shift

# info
echo "--------------------------------------------------------------------------------"
echo "Solar build system"
echo "Command: ${cmd}"
echo "Platform: ${PLATFORM}"
echo "Debug: ${DEBUG}"
echo "Docker image: ${DOCKER_IMAGE_NAME}"
echo "--------------------------------------------------------------------------------"

# check basic environment configuration
. ${project_dir}/config/validate.sh

# create output dir just in case make clean is not executed
mkdir -p ${project_dir}${output_dir}

# launch make process
podman run ${flags} \
  -v "${project_dir}:/ws" \
  -w "${workspace_dir}" \
  -e "SRC=${workspace_dir}${source_dir}" \
  -e "OUTPUT=${workspace_dir}${output_dir}" \
  -e "PLATFORM=${PLATFORM}" \
  -e "DEBUG=${DEBUG}" \
  -e "OPTIMIZATION=${optimization}" \
  -e "HARDENING=${hardening}" \
  ${DOCKER_IMAGE_NAME} \
  ${cmd}
