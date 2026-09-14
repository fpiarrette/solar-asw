#!/bin/sh

# general environment validation
. $PROJECT_DIR/config/validate.sh

# specific deploy depending on $PLATFORM
. $PROJECT_DIR/tools/launcher/$PLATFORM/deploy.sh

# specific run depending on $PLATFORM
. $PROJECT_DIR/tools/launcher/$PLATFORM/launch.sh
