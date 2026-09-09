#!/bin/sh

# this script shall not be executed direclty, is intendeed to be called from main/parent script

. $PROJECT_DIR/tools/launcher/xt_atto_lxl/config.sh

if [ -f $PROJECT_DIR/$OUTPUT_DIR/$BINARY_NAME ]
then
    echo "copying $BINARY_NAME"
    sshpass -p "$TARGET_SSH_PASSWORD" scp $SOURCE_FILE admin@$SOLAR_TARGET_IP_ADDRESS:$DESTINATION_DIR
else
    echo "$BINARY_NAME not available"
fi

if [ -f $PROJECT_DIR/$OUTPUT_DIR/test_gpio ]
then
    echo "copying test_gpio"
    sshpass -p "$TARGET_SSH_PASSWORD" scp $PROJECT_DIR/$OUTPUT_DIR/test_gpio admin@$SOLAR_TARGET_IP_ADDRESS:$DESTINATION_DIR
else
    echo "test_gpio not available"
fi

if [ -f $PROJECT_DIR/$OUTPUT_DIR/test_spi ]
then
    echo "copying test_spi"
    sshpass -p "$TARGET_SSH_PASSWORD" scp $PROJECT_DIR/$OUTPUT_DIR/test_spi admin@$SOLAR_TARGET_IP_ADDRESS:$DESTINATION_DIR
else
    echo "test_spi not available"
fi
