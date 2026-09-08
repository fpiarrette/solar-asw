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

optimization=0

hardening=0

show_help()
{
    echo "$0 [-i] [-c {\"make clean all\"}] [-z] [-e] [-h]"
    echo "\t[-i] interactive"
    echo "\t[-c {\"make clean all\"}] define command"
    echo "\t[-z] activate optimization"
    echo "\t[-e] include GCC hardening options"
    echo "\t[-h] show this help"
}

while getopts "h?ic:ze" opt; do
  case "$opt" in
    h|\?)
      show_help
      exit 0
      ;;
    i)
      flags="${flags} -i"
      cmd="bash"
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
echo "Output dir: ${OUTPUT_DIR}"
echo "--------------------------------------------------------------------------------"

# check basic environment configuration
. ${project_dir}/config/validate.sh

# create output dir just in case make clean is not executed
mkdir -p "${project_dir}/${OUTPUT_DIR}"

# launch make process
podman run ${flags} \
  -v "${project_dir}:/ws" \
  -w "${workspace_dir}" \
  -e "SRC_DIR=${workspace_dir}/src" \
  -e "OUTPUT_DIR=${workspace_dir}/${OUTPUT_DIR}" \
  -e "BINARY_NAME=${BINARY_NAME}" \
  -e "PLATFORM=${PLATFORM}" \
  -e "DEBUG=${DEBUG}" \
  -e "OPTIMIZATION=${optimization}" \
  -e "HARDENING=${hardening}" \
  ${DOCKER_IMAGE_NAME} \
  ${cmd}
