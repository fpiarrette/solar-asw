#!/bin/sh

# this script shall not be executed direclty, is intendeed to be called from main/parent script

. $PROJECT_DIR/tools/launcher/xt_atto_lxl/config.sh

# create destination
ssh_command="cd $INSTALLATION_DIR; mkdir -p $INSTALLATION_NAME"
sshpass -p "$TARGET_SSH_PASSWORD" ssh -t admin@$SOLAR_TARGET_IP_ADDRESS $ssh_command

if [ -f $SOURCE_FILE ]
then
    echo "copying $SOURCE_FILE"
    sshpass -p "$TARGET_SSH_PASSWORD" scp $SOURCE_FILE admin@$SOLAR_TARGET_IP_ADDRESS:$DESTINATION_DIR
else
    echo "$SOURCE_FILE not available"
fi

# untar installation
ssh_command="cd $INSTALLATION_DIR/$INSTALLATION_NAME; tar -xvf $PACK_NAME"
sshpass -p "$TARGET_SSH_PASSWORD" ssh -t admin@$SOLAR_TARGET_IP_ADDRESS $ssh_command

# run installation
#ssh_command="cd $INSTALLATION_DIR/$INSTALLATION_NAME; ./install.sh"
#sshpass -p "$TARGET_SSH_PASSWORD" ssh -t admin@$SOLAR_TARGET_IP_ADDRESS $
