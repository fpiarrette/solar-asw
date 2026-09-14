#!/bin/sh

# general environment validation
. $PROJECT_DIR/config/validate.sh

# specific packaging depending on $PLATFORM
. $PROJECT_DIR/tools/builder/$PLATFORM/pack.sh
