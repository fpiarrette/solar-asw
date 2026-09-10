#!/bin/sh

# this script shall not be executed direclty, is intendeed to be called from main/parent script

# create an empty tar
#tar -cf $OUTPUT_DIR/solar.tar -T /dev/null

echo "$PROJECT_DIR/$OUTPUT_DIR"

# add binary
tar -C $OUTPUT_DIR -cvf $OUTPUT_DIR/$PACK_NAME solar-asw

# add test binaries
tar -C $OUTPUT_DIR -rvf $OUTPUT_DIR/$PACK_NAME test_spi
tar -C $OUTPUT_DIR -rvf $OUTPUT_DIR/$PACK_NAME test_gpio
tar -C $OUTPUT_DIR -rvf $OUTPUT_DIR/$PACK_NAME test_gpio_ioctl

# add resources
tar -C $PROJECT_DIR/src/resources -rvf $OUTPUT_DIR/$PACK_NAME 90-gpio.rules
tar -C $PROJECT_DIR/src/resources -rvf $OUTPUT_DIR/$PACK_NAME run.sh
tar -C $PROJECT_DIR/src/resources -rvf $OUTPUT_DIR/$PACK_NAME install.sh
