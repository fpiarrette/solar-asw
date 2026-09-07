#!/bin/sh

# obtain project base dir
script_dir=$(readlink -f $(pwd)/$(dirname "$0"))
project_dir=$script_dir

# reset getopts
OPTIND=1

# initialize varaibles
flags="-t"

# create source dir
workspace_dir="/ws"

# create output dir
output_dir=/build

# default platform
platform_xt_atto_lxl=xt_atto_lxl
platform_host=host
platform="${platform_host}"

debug=0

rest_port=8080

kill_port=9090

show_help()
{
    echo "$0 [-i] [-o {/build}] [-p {$platform_xt_atto_lxl/$platform_host}] [-c {\"make clean all\"}] [-d] [-h]"
    echo "\t[-i] interactive"
    echo "\t[-o {/build}] define output directory"
    echo "\t[-p {$platform_xt_atto_lxl/$platform_host}] define platform"
    echo "\t[-c {\"make clean all\"}] define command"
    echo "\t[-d] compile with debug symbols"
    echo "\t[-h] show this help"
}

while getopts "h?io:c:p:d" opt; do
  case "$opt" in
    h|\?)
      show_help
      exit 0
      ;;
    i)
      flags="${flags} -i"
      cmd="bash"
      ;;
    s)
      source_dir="${OPTARG}"
      ;;
    o)
      output_dir="${OPTARG}"
      ;;
    c)
      cmd="${OPTARG}"
      ;;
    p)
      platform="${OPTARG}"
      ;;
    d)
      debug=1
      ;;
  esac
done

shift $((OPTIND-1))

[ "${1:-}" = "--" ] && shift

# command
cmd="${workspace_dir}${output_dir}/${platform}/debug/main -l 2 -u"

# info
echo "--------------------------------------------------------------------------------"
echo "Solar HOST running system"
echo "Command: ${cmd}"
echo "Platform: ${platform}"
echo "--------------------------------------------------------------------------------"

if [ "$platform" != "$platform_xt_atto_lxl" ] && [ "$platform" != "$platform_host" ]
then
  show_help
  exit 0
fi

# source specific platform configuration
. ${project_dir}/platform/${platform}.sh

# launch make process
podman run ${flags} \
  -v "${project_dir}:/ws" \
  -w "${workspace_dir}" \
  -p ${rest_port}:${rest_port} \
  -p ${kill_port}:${kill_port} \
  ${DOCKER_IMAGE_NAME} \
  ${cmd}
