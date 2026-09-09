#!/bin/sh

# this script shall not be executed direclty, is intendeed to be called from main/parent script

# Docker flags
FLAGS=-t
WORKSPACE_DIR=/ws

CMD="$WORKSPACE_DIR/$OUTPUT_DIR/$BINARY_NAME"

# launch make process
podman run ${FLAGS} \
  -v "${PROJECT_DIR}:${WORKSPACE_DIR}" \
  -w "${WORKSPACE_DIR}" \
  -p ${SOLAR_TARGET_REST_PORT}:${SOLAR_TARGET_REST_PORT} \
  -p ${SOLAR_TARGET_KILL_PORT}:${SOLAR_TARGET_KILL_PORT} \
  ${DOCKER_IMAGE_NAME} \
  ${CMD} -l 1 -u
