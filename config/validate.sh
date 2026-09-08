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
