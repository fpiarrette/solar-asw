#!/bin/sh

# reset getopts
OPTIND=1

# Docker flags
WORKSPACE_DIR=/ws
CMD="$WORKSPACE_DIR/$OUTPUT_DIR/$BINARY_NAME -l 1 -u"
FLAGS="-t"

# this script shall not be executed direclty, is intendeed to be called from main/parent script
show_help()
{
    echo "$0 [-i] [-h]"
    echo "\t[-i] interactive"
    echo "\t[-h] show this help"
}

while getopts "h?i" opt; do
  case "$opt" in
    h|\?)
      show_help
      exit 0
      ;;
    i)
      FLAGS="${FLAGS} -i"
      CMD="bash"
      ;;
  esac
done

shift $((OPTIND-1))

[ "${1:-}" = "--" ] && shift

# launch make process
podman run ${FLAGS} \
  -v "${PROJECT_DIR}:${WORKSPACE_DIR}" \
  -w "${WORKSPACE_DIR}" \
  -p ${SOLAR_TARGET_REST_PORT}:${SOLAR_TARGET_REST_PORT} \
  -p ${SOLAR_TARGET_KILL_PORT}:${SOLAR_TARGET_KILL_PORT} \
  ${DOCKER_IMAGE_NAME} \
  ${CMD}
