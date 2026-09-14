#!/bin/sh

# obtain project base dir
SCRIPT_DIR=$(readlink -f $(pwd)/$(dirname "$0"))
PROJECT_DIR=$(readlink -f $SCRIPT_DIR/../..)

# general environment validation
. $PROJECT_DIR/config/validate.sh

# specific packaging depending on $PLATFORM
. $PROJECT_DIR/tools/builder/$PLATFORM/pack.sh
