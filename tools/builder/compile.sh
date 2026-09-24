#!/bin/sh

# reset getopts
OPTIND=1

# initialize varaibles
flags="-t"
cmd="make clean all"

# create source dir
workspace_dir="/ws"

optimization=0

hardening=0

test=0

show_help()
{
    echo "$0 [-i] [-c {\"make clean all\"}] [-z] [-e] [-t] [-h]"
    echo "\t[-i] interactive"
    echo "\t[-c {\"make clean all\"}] define command"
    echo "\t[-z] activate optimization"
    echo "\t[-e] include GCC hardening options"
    echo "\t[-t] also compile test software"
    echo "\t[-h] show this help"
}

while getopts "h?ic:zet" opt; do
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
    t)
      test=1
      ;;
    e)
      hardening=1
      ;;
  esac
done

shift $((OPTIND-1))

[ "${1:-}" = "--" ] && shift

# check basic environment configuration
. ${PROJECT_DIR}/config/validate.sh

# include test software only for target platform
if [ "$test" -eq "1" ]
then
  cmd="$cmd tests"
fi

# info
echo "--------------------------------------------------------------------------------"
echo "Solar build system"
echo "Command: ${cmd}"
echo "Platform: ${PLATFORM}"
echo "Debug: ${DEBUG}"
echo "Docker image: ${DOCKER_IMAGE_NAME}"
echo "Output dir: ${OUTPUT_DIR}"
echo "--------------------------------------------------------------------------------"

# create output dir just in case make clean is not executed
mkdir -p "${PROJECT_DIR}/${OUTPUT_DIR}"

# launch make process
podman run ${flags} \
  -v "${PROJECT_DIR}:${workspace_dir}" \
  -w "${workspace_dir}" \
  -e "SRC_DIR=${workspace_dir}/src" \
  -e "OUTPUT_DIR=${workspace_dir}/${OUTPUT_DIR}" \
  -e "BINARY_NAME=${BINARY_NAME}" \
  -e "PLATFORM=${PLATFORM}" \
  -e "PLATFORM_ID=${PLATFORM_ID}" \
  -e "PLATFORM_HOST=${PLATFORM_HOST}" \
  -e "PLATFORM_TARGET=${PLATFORM_TARGET}" \
  -e "DEBUG=${DEBUG}" \
  -e "OPTIMIZATION=${optimization}" \
  -e "HARDENING=${hardening}" \
  ${DOCKER_IMAGE_NAME} \
  ${cmd}
