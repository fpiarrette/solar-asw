#!/bin/sh

if [ ! -n "$PLATFORM" ]
then
  echo "You have to prepare environment first!"
  exit 1
fi

if [ ! -n "$SOLAR_TARGET_IP_ADDRESS" ]
then
  echo "You have to prepare environment first!"
  exit 1
fi

if [ ! -n "$SOLAR_TARGET_KILL_PORT" ]
then
  echo "You have to prepare environment first!"
  exit 1
fi

if [ ! -n "$SOLAR_TARGET_REST_PORT" ]
then
  echo "You have to prepare environment first!"
  exit 1
fi

if [ ! -n "$DOCKER_IMAGE_NAME" ]
then
  echo "You have to prepare environment first!"
  exit 1
fi

if [ ! -n "$BINARY_NAME" ]
then
  echo "You have to prepare environment first!"
  exit 1
fi

if [ ! -n "$OUTPUT_DIR" ]
then
  echo "You have to prepare environment first!"
  exit 1
fi

if [ ! -n "$PLATFORM_ID" ]
then
  echo "You have to prepare environment first!"
  exit 1
fi

if [ ! -n "$PLATFORM_HOST" ]
then
  echo "You have to prepare environment first!"
  exit 1
fi

if [ ! -n "$PLATFORM_TARGET" ]
then
  echo "You have to prepare environment first!"
  exit 1
fi
