#!/bin/sh

# this script shall not be executed direclty, is intendeed to be called from main/parent script

# source specific platform configuration
. ${project_dir}/config/docker/${PLATFORM}.sh

# Docker flags
flags=-t
workspace_dir=/ws
binary_name=main
cmd=$workspace_dir/build/host/debug/$binary_name

# launch make process
podman run ${flags} \
  -v "${project_dir}:${workspace_dir}" \
  -w "${workspace_dir}" \
  -p ${SOLAR_TARGET_REST_PORT}:${SOLAR_TARGET_REST_PORT} \
  -p ${SOLAR_TARGET_KILL_PORT}:${SOLAR_TARGET_KILL_PORT} \
  ${DOCKER_IMAGE_NAME} \
  ${cmd} -l 1 -u
