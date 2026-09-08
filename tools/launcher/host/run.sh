#!/bin/sh

# this script shall not be executed direclty, is intendeed to be called from main/parent script

# Docker flags
flags=-t
workspace_dir=/ws

if [ -z "$DEBUG" ]
then
  cmd=$workspace_dir/build/host/release/$BINARY_NAME
else
  cmd=$workspace_dir/build/host/debug/$BINARY_NAME
fi

# launch make process
podman run ${flags} \
  -v "${project_dir}:${workspace_dir}" \
  -w "${workspace_dir}" \
  -p ${SOLAR_TARGET_REST_PORT}:${SOLAR_TARGET_REST_PORT} \
  -p ${SOLAR_TARGET_KILL_PORT}:${SOLAR_TARGET_KILL_PORT} \
  ${DOCKER_IMAGE_NAME} \
  ${cmd} -l 1 -u
