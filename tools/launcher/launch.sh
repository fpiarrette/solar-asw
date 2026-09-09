#!/bin/sh

# obtain project base dir
SCRIPT_DIR=$(readlink -f $(pwd)/$(dirname "$0"))
PROJECT_DIR=$(readlink -f $SCRIPT_DIR/../..)

# general environment validation
. $PROJECT_DIR/config/validate.sh

# specific deploy depending on $PLATFORM
. $PROJECT_DIR/tools/launcher/$PLATFORM/deploy.sh

# specific run depending on $PLATFORM
. $PROJECT_DIR/tools/launcher/$PLATFORM/launch.sh
