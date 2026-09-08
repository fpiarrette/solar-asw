#!/bin/sh

# obtain project base dir
script_dir=$(readlink -f $(pwd)/$(dirname "$0"))
project_dir=$script_dir

# info
echo "--------------------------------------------------------------------------------"
echo "Solar test sequence system"
echo "--------------------------------------------------------------------------------"

#             -------------------\            -------------------\
# nc (client) -- localhost:9000 --> Solar ASW -- localhost:9500 --> nc (server)
#             -------------------/            -------------------/

# in case of SIGINT
trap 'kill ${pid_nc_client}; kill ${pid_solar_asw}; kill ${pid_nc_server}' EXIT INT TERM HUP

# nc server listening on port 9500
nc -l 9500 &
pid_nc_server=$!

# SOLAR ASW in the midle
./build/host/debug/main &
pid_solar_asw=$!

# nc client sending a message to port 9000
echo "holi" | nc -q 0 localhost 9000 &
pid_nc_client=$!

# report
echo "--------------------------------------------------------------------------------"
echo "PID NC server ${pid_nc_server}"
echo "PID SOLAR ASW ${pid_solar_asw}"
echo "PID NC client ${pid_nc_client}"
echo "--------------------------------------------------------------------------------"

# wait for all processes to finish
wait
