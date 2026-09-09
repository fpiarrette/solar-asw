#!/bin/sh

show_error()
{
  echo "Environment shall be prepared first!"
  exit 1
}

if [ ! -n "$PLATFORM" ]
then
  show_error
fi

if [ ! -n "$SOLAR_TARGET_IP_ADDRESS" ]
then
  show_error
fi

if [ ! -n "$SOLAR_TARGET_KILL_PORT" ]
then
  show_error
fi

if [ ! -n "$SOLAR_TARGET_REST_PORT" ]
then
  show_error
fi

if [ ! -n "$DOCKER_IMAGE_NAME" ]
then
  show_error
fi

if [ ! -n "$BINARY_NAME" ]
then
  show_error
fi

if [ ! -n "$OUTPUT_DIR" ]
then
  show_error
fi

if [ ! -n "$PLATFORM_ID" ]
then
  show_error
fi

if [ ! -n "$PLATFORM_HOST" ]
then
  show_error
fi

if [ ! -n "$PLATFORM_TARGET" ]
then
  show_error
fi
